#include "m_collector.h"
#include "m_micro.h"
#include "main.h"
#include "m_acm.h"
#include "cmsis_os.h"
#include "m_log.h"
#include <string.h>
#include <stdio.h>
#include "drv_led.h"
//***********************************************************************************************

static void m_collector_thread(void const *argument);


//-----------------------------------------------------------------------------------------------

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern TIM_HandleTypeDef htim3;

static EventGroupHandle_t collector_events=NULL;

static m_adc_cache_t m_adc_cache;
	
static __IO uint32_t adc1_raw_result_a[ADC_CH_NUM*ADC_TIMES_PER_ROUND] = {0};

//===============================================================================

void m_collector_init(void)// 初始化ADC采集线程
{
	uint16_t pin_mask=0;
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	if (collector_events == NULL) 
	{
		collector_events = xEventGroupCreate();
	}

	xEventGroupClearBits(collector_events, 0x00FFFFFF);

	m_adc_cache.adc_handle = &hadc1;
	m_adc_cache.cache = (uint32_t *)pvPortMalloc( sizeof(uint32_t )*ARRAY_SIZE(adc1_raw_result_a));
	if( NULL == m_adc_cache.cache )
	{
		LOG("cltr init fail");
		return;
	}
	m_adc_cache.size = ARRAY_SIZE(adc1_raw_result_a);
	m_adc_cache.mis_cnt=0;
	m_adc_cache.b_new=false;

	__HAL_RCC_GPIOD_CLK_ENABLE();
	pin_mask = ADC_POWER_EN_PIN;
	GPIO_InitStruct.Pin = pin_mask;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOD, pin_mask, GPIO_PIN_SET); 
	
	osThreadDef(cltr, m_collector_thread, osPriorityNormal, 0, 1024);//创建ADC采集线程
	osThreadCreate(osThread(cltr), NULL);
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)// ADC转换完成回调函数
{
	BaseType_t xHigherPriorityTaskWoken, xResult;
	
	if (( collector_events )&&( &hadc1 == AdcHandle )) // ADC转换完成
	{		
		memcpy((uint8_t *)m_adc_cache.cache, (uint8_t *)adc1_raw_result_a, sizeof(uint32_t)*m_adc_cache.size );// 复制ADC转换结果到缓存区
		if( true == m_adc_cache.b_new )    
		{
			m_adc_cache.mis_cnt++;
			
			return;
		}
		m_adc_cache.b_new = true;

	    xHigherPriorityTaskWoken = pdFALSE; // 获取更高优先级任务的唤醒状态

	    xResult = xEventGroupSetBitsFromISR(collector_events, CLTR_EVENT_ADC_DONE, &xHigherPriorityTaskWoken );// 设置事件标志

	    if( xResult == pdPASS )// 中断唤醒更高优先级任务
	    {
	        portYIELD_FROM_ISR( xHigherPriorityTaskWoken );// 从中断中唤醒更高优先级任务
	    }
	}
}



void m_collector_thread(void const *argument)// ADC采集线程
{
	HAL_TIM_Base_Start(&htim3);
	__HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);
	if(HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc1_raw_result_a, ADC_CH_NUM*ADC_TIMES_PER_ROUND) != HAL_OK)
	{
		/* Start Conversation Error */
		Error_Handler(); 
	}
	__HAL_DMA_ENABLE_IT(&hdma_adc1, DMA_IT_TC);
	

	for(;;) 
	{
		xEventGroupWaitBits( collector_events, CLTR_EVENT_ADC_DONE , 1, 0, portMAX_DELAY );// 等待ADC转换完成事件
		{
			float volt[ADC_CH_NUM];
			acm_msg_update_apr_t update_apr;
//			acm_msg_update_current_t update_curnt;
			
			if( true == m_is_acm_ready())// 检查ACM是否准备好
			{
				uint8_t i;
				uint32_t temp;
				float f_temmp;
				
				for( uint8_t ch=0;ch<ADC_CH_NUM;ch++)
				{
					for( i=0;i<ADC_TIMES_PER_ROUND;i++ )
					{
						temp = m_adc_cache.cache[ADC_CH_NUM*i+ch];
						f_temmp = (float)temp;
						volt[ch] += f_temmp * REFER_VOLTAGE / CONVERT_BITS;
					}

					volt[ch] /= ADC_TIMES_PER_ROUND;
				}

//				update_apr.cap_mv[0] = volt[9];  //ADC_左头
//				update_apr.cap_mv[1] = volt[15]; //ADC_左肩
//				update_apr.cap_mv[2] = volt[7];  //ADC_左腰
//				update_apr.cap_mv[3] = volt[5];  //ADC_左臂1
//				update_apr.cap_mv[4] = volt[8];  //ADC_右头  
//				update_apr.cap_mv[5] = volt[14]; //ADC_右肩 
//				update_apr.cap_mv[6] = volt[6];  //ADC_右腰 
//				
//				update_apr.cap_mv[7] =  volt[4]; //ADC_右臂1  
//				update_apr.cap_mv[8] =  volt[3]; //ADC_左臂2
//				update_apr.cap_mv[9] =  volt[1]; //ADC_左臂3
//				update_apr.cap_mv[10] = volt[13];//ADC_左臂4
//				update_apr.cap_mv[11] = volt[11];//ADC_左小腿
//				update_apr.cap_mv[12] = volt[2]; //ADC_右臂2
//				update_apr.cap_mv[13] = volt[0]; //ADC_右臂3
//				update_apr.cap_mv[14] = volt[12];//ADC_右臂4
//				update_apr.cap_mv[15] = volt[10];//ADC_右小腿

				update_apr.cap_mv[0] = volt[9]; //电磁阀_左头
				update_apr.cap_mv[1] = volt[15];//电磁阀_左肩
				update_apr.cap_mv[2] = volt[7]; //电磁阀_左腰
				update_apr.cap_mv[3] = volt[5]; //电磁阀_左臂-1
				update_apr.cap_mv[4] = volt[3]; //电磁阀_左臂-2
				update_apr.cap_mv[5] = volt[1]; //电磁阀_左臂-3
				update_apr.cap_mv[6] = volt[13];//电磁阀_左臂-4
				
				update_apr.cap_mv[7] = volt[11];//电磁阀_左小腿
				update_apr.cap_mv[8] = volt[8]; //电磁阀_右头
				update_apr.cap_mv[9] = volt[14];//电磁阀_右肩
				update_apr.cap_mv[10] = volt[6];//电磁阀_右腰
				update_apr.cap_mv[11] = volt[4];//电磁阀_右臂-1
				update_apr.cap_mv[12] = volt[2];//电磁阀_右臂-2
				update_apr.cap_mv[13] = volt[0];//电磁阀_右臂-3
				update_apr.cap_mv[14] = volt[12];//电磁阀_右臂-4
				update_apr.cap_mv[15] = volt[10];//电磁阀_右小腿 
				
				for(uint8_t i=0; i<ADC_CH_NUM; i++)
        {
      	  if(update_apr.cap_mv[i] >= 3.3)
                  update_apr.cap_mv[i] = 3.3;
        }
				
				m_acm_air_pressure_update( &update_apr );
			}
			m_adc_cache.b_new = false;
		}
		xEventGroupClearBits( collector_events, CLTR_EVENT_ADC_DONE );
	}

}



