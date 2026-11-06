#include "m_uart_traffic.h"
#include "m_protocol.h"
#include "m_micro.h"
#include "m_protocol.h"
#include "cmsis_os.h"
#include "m_log.h"
#include <stdio.h>
#include <string.h>
#include "drv_ai.h"
#include "drv_tmp_sensor.h"
/**
 * @file    m_uart_traffic.c
 * @brief   UART串口通信流量管理模块
 * @note    负责多个串口的DMA接收、消息分发与协议处理
 *          使用FreeRTOS队列实现中断与任务间的通信
 */
static void m_uart_traffic_thread(void const *argument);              // UART消息处理线程
static void m_uart_ble_port_rx_handle(uart_msg_content_t *content);   // BLE蓝牙端口接收数据处理
static void m_uart_ai_port_rx_handle(uart_msg_content_t *content);    // AI模块端口接收处理
//static void m_uart_forward_port_rx_handle(uart_msg_content_t *content);
static BaseType_t m_uart_post_msg( uart_msg_type_t type, uart_msg_content_t *content, uint8_t b_from_isr );// 发送消息到队列
static  void m_check_role_timer_callback(TimerHandle_t xTimer) ;      // 角色检测定时器回调
void m_uart_tmp_sensor_port_rx_handle(uart_msg_content_t *content);   // 温度传感器端口接收数据处理

//-------------------------------------------------------------------------------------

/* ==================== 外部UART句柄声明 ==================== */
extern UART_HandleTypeDef huart4;   // UART4 - AI模块端口
extern UART_HandleTypeDef huart5;   // UART5 - 温度传感器端口
extern UART_HandleTypeDef huart1;   // UART1 - 保留/其他用途
extern UART_HandleTypeDef huart2;   // UART2 - 日志输出端口
extern UART_HandleTypeDef huart3;   // UART3 - BLE蓝牙端口

extern m_role_t g_role;             // 设备角色（主/从）

/* ==================== 模块内部静态变量 ==================== */
static QueueHandle_t g_uart_msg_queue;       // UART消息队列句柄
static TimerHandle_t m_timer_check_role;     // 角色检测定时器句柄
static uint8_t g_check_role_cnt = 0;         // 角色检测发送计数器

m_uart_buf_t g_uart_buf[]=
{
	{.uart=&huart5, NULL, MAX_TMP_SENSOR_FRAME_SIZE},  // UART5: 温度传感器端口
	{.uart=&huart3, NULL, MAX_BLE_FRAME_SIZE},         // UART3: BLE蓝牙端口
	{.uart=&huart4, NULL, MAX_BLE_FRAME_SIZE},         // UART4: AI模块端口
};

static const uart_msg_handle_entry_t g_uart_msg_handle_tbl[]=
{
	{ &huart5, UART_MSG_TYPE_RX_DONE, m_uart_tmp_sensor_port_rx_handle },//温度传感器端口接收处理    
	{ &huart3, UART_MSG_TYPE_RX_DONE, m_uart_ble_port_rx_handle },//蓝牙端口接收处理
	{ &huart4, UART_MSG_TYPE_RX_DONE, m_uart_ai_port_rx_handle },//AI端口接收处理

};

uart_msg_content_t g_uart_rx_cache;   // 接收中断使用的临时消息缓存

//*****************************************************************************************

void m_uart_traffic_init( void )  // 初始化UART流量管理模块
{
	uint16_t pin_mask=0;
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOD_CLK_ENABLE();
    //通讯接口电源使能引脚//
	pin_mask = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_7;
	GPIO_InitStruct.Pin = pin_mask;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOD, pin_mask, GPIO_PIN_SET); 

	__HAL_RCC_GPIOA_CLK_ENABLE();
    //通讯接口电源使能引脚//
	pin_mask = GPIO_PIN_11;
	GPIO_InitStruct.Pin = pin_mask;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA, pin_mask, GPIO_PIN_SET); 
	
	g_uart_msg_queue = xQueueCreate( UART_RX_QUEUE_SIZE, sizeof(uart_msg_content_t)); //创建UART消息队列
	if( NULL == g_uart_msg_queue )
	{
		LOG("uart thread init fail");

		return;
	}

	mp_init();//初始化OTA模块
	
	osThreadDef(uart, m_uart_traffic_thread, osPriorityNormal, 0, 1024);//创建UART消息处理线程
	osThreadCreate(osThread(uart), NULL);//启动UART消息处理线程
}


void m_uart_traffic_thread(void const *argument)//UART消息处理线程
{
	uart_msg_t msg;
	uint16_t i;
	uint16_t cnt;
	m_uart_buf_t *p;
	//uint8_t uart_rx_buf[UART_RX_BUBF_SIZE];
	
	cnt = ARRAY_SIZE(g_uart_msg_handle_tbl);// UART端口数量

	p = g_uart_buf;
	
	for(uint8_t i=0; i<ARRAY_SIZE(g_uart_buf); i++,p++)
	{
		p->dma_cache = pvPortMalloc( p->cache_size );// 分配DMA缓存空间

		if(NULL == p->dma_cache)
		{
			LOG("uart %d buf init fail", i);

			return;
		}
		
		HAL_UARTEx_ReceiveToIdle_DMA( p->uart, p->dma_cache, p->cache_size );// 启动DMA接收
	}

	m_timer_check_role = xTimerCreate("role",
								pdMS_TO_TICKS(200),  
								pdTRUE, 
								NULL,
								m_check_role_timer_callback);		
	//xTimerStart( m_timer_check_role, pdMS_TO_TICKS(1));
		
	for(;;) 
	{
		if(pdPASS == xQueueReceive( g_uart_msg_queue,  &msg, portMAX_DELAY))//从队列接收消息 
		{
			for( i=0; i< cnt; i++ )
			{
				if( (msg.uart == g_uart_msg_handle_tbl[i].uart)&&(msg.type == g_uart_msg_handle_tbl[i].type ) ) //匹配端口和消息类型
				{
					g_uart_msg_handle_tbl[i].handle( &(msg.content) );//调用相应的处理函数

					break;
				}
			}
		}
	}

//	vTaskDelete(NULL);
}




void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)//接收事件回调
{
	m_uart_buf_t *p;
	p = g_uart_buf;
	
	for(uint8_t i=0; i<ARRAY_SIZE(g_uart_buf); i++,p++)
	{
		if( p->uart == huart )
		{
			__HAL_UNLOCK( huart );

			if( ( HAL_UART_RXEVENT_TC == huart->RxEventType ) || ( HAL_UART_RXEVENT_IDLE == huart->RxEventType ) )//接收完成或空闲
			{
				if( Size <= p->cache_size )
				{
					g_uart_rx_cache.pkt.uart = huart;
					g_uart_rx_cache.pkt.data_len = Size;
					memcpy( g_uart_rx_cache.pkt.data, p->dma_cache, Size );

					m_uart_post_msg( UART_MSG_TYPE_RX_DONE, &g_uart_rx_cache, true );//发送接收完成消息
				}	
			}

			HAL_UARTEx_ReceiveToIdle_DMA( p->uart, p->dma_cache, p->cache_size );
		}
	}

}


BaseType_t m_uart_post_msg( uart_msg_type_t type, uart_msg_content_t *content, uint8_t b_from_isr )//发送消息
{
	uart_msg_t msg;     // 消息结构体
	BaseType_t xReturn; // 返回值

	msg.type = type;   // 消息类型
	msg.uart = content->pkt.uart;//UART端口
	memcpy( (uint8_t *)&(msg.content), ( uint8_t *)content, sizeof(uart_msg_content_t));//复制消息内容

	if(true == b_from_isr)
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE; //是否有更高优先级的任务被唤醒

		xQueueSendToBackFromISR( g_uart_msg_queue, &msg, &xHigherPriorityTaskWoken );//发送消息到队列尾部

		if( xHigherPriorityTaskWoken == pdTRUE )//如果有更高优先级的任务被唤醒
		{
			portYIELD_FROM_ISR( xHigherPriorityTaskWoken );//切换到更高优先级的任务
		}
	}
	else
	{
		xReturn = xQueueSend( g_uart_msg_queue,  &msg, pdMS_TO_TICKS(20));//发送消息到队列
		if(xReturn!=pdTRUE)
		{
		}

	}

	return xReturn;
}
      

void m_uart_ble_port_rx_handle(uart_msg_content_t *content)//BLE蓝牙端口接收数据处理
{	
	mp_rx_downlink_data_handle( content->pkt.data, content->pkt.data_len );
}

void m_uart_ai_port_rx_handle(uart_msg_content_t *content)//AI模块端口接收处理
{
	drv_ai_process_frame( content->pkt.data, content->pkt.data_len );
}

void m_uart_tmp_sensor_port_rx_handle(uart_msg_content_t *content)//温度传感器端口接收数据处理
{	
	drv_tmp_sensor_process_frame( content->pkt.data, content->pkt.data_len );
}

 void m_check_role_timer_callback(TimerHandle_t xTimer)// 检查角色定时器回调
{
	if(g_check_role_cnt<10)
	{
		uint8_t get_mac_frame[]={0xB5, 0xB5, 0x7F, 0x00, 0x7F, 0x5E};                        // 检查角色帧
		HAL_UART_Transmit(&huart3,  get_mac_frame, sizeof(get_mac_frame), pdMS_TO_TICKS(5));//发送检查角色帧
		g_check_role_cnt++;

		if(g_check_role_cnt==10)
		{
			xTimerStop( m_timer_check_role, pdMS_TO_TICKS(1));//停止定时器
			//xTimerChangePeriod( m_timer_check_role, pdMS_TO_TICKS(10000), pdMS_TO_TICKS(1) );
		}
	}
}      
 

void m_stop_checking_role(void)//停止检查角色
{
	g_check_role_cnt = 0;                             //重置检查角色计数器
	xTimerStop( m_timer_check_role, pdMS_TO_TICKS(1));//停止定时器
}
 
 
#pragma import(__use_no_semihosting)//关闭半主机模式                     
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       

void _sys_exit(int x)     //退出函数
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)//发送字符
{
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 1);

	return ch; 
}

 
 
