#include "drv_air_pump.h"

extern TIM_HandleTypeDef htim4;

void drv_air_pump_init(void)
{
#if (M_PUMP_PWM_DRV)
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
#else
	uint16_t pin_mask=0;
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOD_CLK_ENABLE();
	pin_mask = LEFT_AIR_PUM_PIN|RIGHT_AIR_PUM_PIN;
	GPIO_InitStruct.Pin = pin_mask;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOB, pin_mask, GPIO_PIN_SET); 

#endif	
}


void drv_air_pump_control(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState io_level )
{
#if (M_PUMP_PWM_DRV)
	uint32_t tim_channel=0xFFFFFFFF;

	if( (RIGHT_AIR_PUM_PORT == port)&&(RIGHT_AIR_PUM_PIN==pin))
	{
		tim_channel = RIGHT_AIR_PUM_CHANNEL;
	}
	else if( (LEFT_AIR_PUM_PORT == port)&&(LEFT_AIR_PUM_PIN==pin))
	{
		tim_channel = LEFT_AIR_PUM_CHANNEL;
	}
	else
	{
		return;
	}

	if( M_PUMP_ON == io_level )
	{
		HAL_TIM_PWM_Start(&htim4, tim_channel);
	}
	else
	{
		HAL_TIM_PWM_Stop(&htim4, tim_channel);
	}

#else
	HAL_GPIO_WritePin( port, pin, io_level);
#endif
}
