#include "drv_led.h"

void drv_led_init(void)
{
	uint16_t pin_mask=0;
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if(RUN_LED_PORT==GPIOB)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
	}
	else if(RUN_LED_PORT==GPIOC)
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
	}

	pin_mask = RUN_LED_PIN;
	GPIO_InitStruct.Pin = pin_mask;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(RUN_LED_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(RUN_LED_PORT, pin_mask, GPIO_PIN_SET); 
}

