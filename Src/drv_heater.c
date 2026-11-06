#include "drv_heater.h"
#include "m_micro.h"
#include "cmsis_os.h"
#include "m_acm.h"

ht_item_t g_ht_item[]=
{
	{ HEATER_1_PORT, HEATER_1_PIN, 0, 0 },
	{ HEATER_2_PORT, HEATER_2_PIN, 0, 0 },
};

static TimerHandle_t m_timer_ht;
static uint8_t b_ht_timer_running=false;
static void m_ht_timer_callback(TimerHandle_t xTimer) ;

void drv_heater_init(void)
{
	uint16_t pin_mask=0;
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOG_CLK_ENABLE();

	pin_mask = HEATER_1_PIN|HEATER_2_PIN;
	GPIO_InitStruct.Pin = pin_mask;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(HEATER_1_PORT, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(HEATER_1_PORT, HEATER_1_PIN, M_HEATER_OFF); 
	HAL_GPIO_WritePin(HEATER_2_PORT, HEATER_2_PIN, M_HEATER_OFF); 

    //创建加热器定时任务10毫秒执行//
	m_timer_ht = xTimerCreate("ht",            
						pdMS_TO_TICKS(10),    //10ms
						pdTRUE,               //Auto reload 
						NULL,                 //callback function   
						m_ht_timer_callback); //callback function
	xTimerStop( m_timer_ht, pdMS_TO_TICKS(1));//stop timer
	b_ht_timer_running = false;

	//drv_heater_ctrl(0,2);
	//drv_heater_ctrl(0,2);
}


void drv_heater_ctrl( uint8_t ht_id, uint8_t dutyfactor )// ht_id: 1-2, dutyfactor: 0-100
{
//	if(( ht_id > 2)||(dutyfactor>100))
//	{
//		return;
//	}

	if(( 0 == ht_id)||
		(ht_id > ARRAY_SIZE(g_ht_item))||
		(dutyfactor>100))
	{
		return;
	}
	
//	g_ht_item[ht_id].on_cnt=0;
// 	g_ht_item[ht_id].dutyfactor = dutyfactor;
//	if(0==dutyfactor)
//	{
//		HAL_GPIO_WritePin( g_ht_item[ht_id].port, g_ht_item[ht_id].pin, M_HEATER_OFF); 
//	}

	g_ht_item[ht_id-1].on_cnt=0;
 	g_ht_item[ht_id-1].dutyfactor = dutyfactor;
	if(0==dutyfactor)
	{
		HAL_GPIO_WritePin( g_ht_item[ht_id-1].port, g_ht_item[ht_id-1].pin, M_HEATER_OFF); 
	}
	
	
	if((0==g_ht_item[0].dutyfactor)&&(0==g_ht_item[1].dutyfactor)) //两个加热器都关
	{
		xTimerStop( m_timer_ht, pdMS_TO_TICKS(1));
		b_ht_timer_running = false;
	}
	else
	{
		if(false==b_ht_timer_running)
		{
			xTimerStart( m_timer_ht, pdMS_TO_TICKS(1));
			b_ht_timer_running = true;
		}
	}
}


void m_ht_timer_callback(TimerHandle_t xTimer) //定时器回调函数
{
	ht_item_t *p_item;

	for(uint8_t i=0;i<2;i++)
	{
		p_item = &g_ht_item[i];

		if( 0 == p_item->dutyfactor )
		{
			HAL_GPIO_WritePin( p_item->port, p_item->pin, M_HEATER_OFF);   
		}
		else if( 100 == p_item->dutyfactor )
		{
			HAL_GPIO_WritePin( p_item->port, p_item->pin, M_HEATER_ON); 
		}
		else
		{
			if( 0 == p_item->on_cnt )
			{
				HAL_GPIO_WritePin( p_item->port, p_item->pin, M_HEATER_ON); 
			}
			
			if( p_item->on_cnt == p_item->dutyfactor )
			{
				HAL_GPIO_WritePin( p_item->port, p_item->pin, M_HEATER_OFF); 
			}
			if( 100 == p_item->on_cnt )
			{
				p_item->on_cnt =0;
			}
			else
			{
				p_item->on_cnt++;
			}
		}
	}
	
}

ht_item_t *m_get_heater_ctrl_instance(uint8_t partion )
{
	if(  ( PARTION_LEFT != partion )&&
	      ( PARTION_RIGHT != partion ))
	{
		return NULL;
	}
	
	return &g_ht_item[partion-1];
}

