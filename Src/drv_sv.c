#include "drv_sv.h"
#include "m_micro.h"
#include "cmsis_os.h"


extern TIM_HandleTypeDef htim6;


uint32_t g_sv_state_mask;

sv_item_t g_sv_item[]=
{
	{ GPIOF, GPIO_PIN_11, 0, 0, 0, 2 },//电磁阀_左头
	{ GPIOF, GPIO_PIN_12, 0, 0, 0, 2 },//电磁阀_左肩
	{ GPIOF, GPIO_PIN_13, 0, 0, 0, 2 },//电磁阀_左腰
	{ GPIOF, GPIO_PIN_14, 0, 0, 0, 2 },//电磁阀_左臂-1
	{ GPIOF, GPIO_PIN_15, 0, 0, 0, 2 },//电磁阀_右头
	{ GPIOG, GPIO_PIN_0,  0, 0, 0, 2 },//电磁阀_右肩
	{ GPIOG, GPIO_PIN_1,  0, 0, 0, 2 },//电磁阀_右腰
	{ GPIOE, GPIO_PIN_11, 0, 0, 0, 2 },//电磁阀_右臂1

	{ GPIOE, GPIO_PIN_7,  0, 0, 0, 2 },//电磁阀_左臂2
	{ GPIOE, GPIO_PIN_8,  0, 0, 0, 2 },//电磁阀_左臂3
	{ GPIOE, GPIO_PIN_9,  0, 0, 0, 2 },//电磁阀_左臂4
	{ GPIOE, GPIO_PIN_10, 0, 0, 0, 2 },//电磁阀_左小腿
	{ GPIOE, GPIO_PIN_12, 0, 0, 0, 2 },//电磁阀_右臂-2
	{ GPIOE, GPIO_PIN_13, 0, 0, 0, 2 },//电磁阀_右臂-3
	{ GPIOD, GPIO_PIN_9,  0, 0, 0, 2 },//电磁阀_右臂-4
	{ GPIOD, GPIO_PIN_10, 0, 0, 0, 2 },//电磁阀_右小腿

	{ GPIOE, GPIO_PIN_14, 0, 0, 0, 2 },//电磁阀_放气1
	{ GPIOD, GPIO_PIN_8,  0, 0, 0, 2 },//电磁阀_放气2
	{ GPIOD, GPIO_PIN_11, 0, 0, 0, 2 },//电磁阀_放气3


//    { GPIOF, GPIO_PIN_11 },//电磁阀_左头
//	{ GPIOF, GPIO_PIN_12 },//电磁阀_左肩
//	{ GPIOF, GPIO_PIN_13 },//电磁阀_左腰
//	{ GPIOF, GPIO_PIN_14 },//电磁阀_左臂-1
//	{ GPIOE, GPIO_PIN_7 },//电磁阀_左臂-2
//	{ GPIOE, GPIO_PIN_8 },//电磁阀_左臂-3
//	{ GPIOE, GPIO_PIN_9 },//电磁阀_左臂-4
//	{ GPIOE, GPIO_PIN_10 },//电磁阀_左小腿

//	{ GPIOF, GPIO_PIN_15 },//电磁阀_右头
//	{ GPIOG, GPIO_PIN_0 }, //电磁阀_右肩
//	{ GPIOG, GPIO_PIN_1 }, //电磁阀_右腰
//	{ GPIOE, GPIO_PIN_11 },//电磁阀_右臂1
//	{ GPIOE, GPIO_PIN_12 },//电磁阀_右臂-2    
//	{ GPIOE, GPIO_PIN_13 },//电磁阀_右臂-3
//	{ GPIOD, GPIO_PIN_9 }, //电磁阀_右臂-4
//	{ GPIOD, GPIO_PIN_10 },//电磁阀_右小腿 

//	{ GPIOE, GPIO_PIN_14 },//电磁阀_放气1
//	{ GPIOD, GPIO_PIN_8 }, //电磁阀_放气2
//	{ GPIOD, GPIO_PIN_11 },//电磁阀_放气3

};


void drv_solenoid_valve_init(void)
{
	uint16_t pin_mask=0;
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	pin_mask = PUMP_SV_POWER_EN_PIN;
	GPIO_InitStruct.Pin = pin_mask;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA, pin_mask, GPIO_PIN_RESET); 
	//enale the air pum and sv power
	HAL_GPIO_WritePin(PUMP_SV_POWER_EN_PORT, PUMP_SV_POWER_EN_PIN, GPIO_PIN_RESET); 

	__HAL_RCC_GPIOD_CLK_ENABLE();
	pin_mask =GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
	GPIO_InitStruct.Pin = pin_mask;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	__HAL_RCC_GPIOE_CLK_ENABLE();
	pin_mask = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|
			    GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
	GPIO_InitStruct.Pin = pin_mask;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	

	__HAL_RCC_GPIOF_CLK_ENABLE();
	pin_mask = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStruct.Pin = pin_mask;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);


	__HAL_RCC_GPIOG_CLK_ENABLE();
	pin_mask = GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Pin = pin_mask;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);


	for(uint8_t i=0;i<ARRAY_SIZE(g_sv_item);i++)//初始化所有电磁阀
	{
		drv_solenoid_valve_control( i, M_SV_OFF );
	}
	
	HAL_TIM_Base_Start(&htim6);
	__HAL_TIM_ENABLE_IT(&htim6, TIM_IT_UPDATE);
	

}

void drv_solenoid_valve_control( uint8_t sv_id, GPIO_PinState io_level )
{
	if( sv_id > ARRAY_SIZE(g_sv_item))
	{
		return;
	}

	if( M_SV_ON == io_level )
	{
		if(g_sv_item[sv_id].state !=1)
		{
			g_sv_state_mask |= BIT(sv_id);

			g_sv_item[sv_id].on_cnt=0;
			g_sv_item[sv_id].pulse_wide_cnt=0;
	 		g_sv_item[sv_id].dutyfactor = SV_ON_STATE_DUTY;
			g_sv_item[sv_id].state=1;

			HAL_GPIO_WritePin( g_sv_item[sv_id].port, g_sv_item[sv_id].pin, io_level);
		}
	}
	else
	{
		if(g_sv_item[sv_id].state !=0)
		{
			g_sv_state_mask &= ~BIT(sv_id);

			g_sv_item[sv_id].on_cnt=0;
			g_sv_item[sv_id].pulse_wide_cnt=0;
	 		g_sv_item[sv_id].dutyfactor = 0;
			g_sv_item[sv_id].state=0;

			HAL_GPIO_WritePin( g_sv_item[sv_id].port, g_sv_item[sv_id].pin, io_level);
		}
	}

}

uint32_t m_get_sv_state_mask(void)
{
	return g_sv_state_mask;
}

/* 1ms执行 */
void m_timer6_ms_irq_callback(void)
{
	sv_item_t *p_item;

	for(uint8_t i=0;i<ARRAY_SIZE(g_sv_item);i++)
	{
		p_item = &g_sv_item[i];

		if( 0 == p_item->dutyfactor )
		{
			HAL_GPIO_WritePin( p_item->port, p_item->pin, M_SV_OFF); 
		}
		else if( 100 == p_item->dutyfactor )
		{
			HAL_GPIO_WritePin( p_item->port, p_item->pin, M_SV_ON); 
		}
		else
		{
			if( 0 == p_item->pulse_wide_cnt )
			{
				HAL_GPIO_WritePin( p_item->port, p_item->pin, M_SV_ON); 
			}
			
			if( p_item->pulse_wide_cnt == p_item->dutyfactor )
			{
				HAL_GPIO_WritePin( p_item->port, p_item->pin, M_SV_OFF); 
			}
			
			if( 100 == p_item->pulse_wide_cnt)
			{
				p_item->pulse_wide_cnt =0;
			}
			else
			{
				p_item->pulse_wide_cnt++;
			}

			if(SV_ON_STATE_DUTY == p_item->dutyfactor )
			{
				if( p_item->on_cnt < TURN_ON_SV_HOLD_TICK)
				{
					p_item->on_cnt++;
					if( TURN_ON_SV_HOLD_TICK == p_item->on_cnt )
					{
						 p_item->pulse_wide_cnt  = 0;
						p_item->dutyfactor =SV_ON_STATE_KEEP_DUTY;
					}
				}
			}
		}
	}
}
	

