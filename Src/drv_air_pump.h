#ifndef DRV_AIR_PUMP_H
#define DRV_AIR_PUMP_H
#include "stm32f4xx_hal.h"


#define M_PUMP_PWM_DRV	1

#define M_PUMP_ON	GPIO_PIN_RESET
#define M_PUMP_OFF	GPIO_PIN_SET

#define LEFT_AIR_PUM_PORT		GPIOD
#define LEFT_AIR_PUM_PIN		GPIO_PIN_13

#define RIGHT_AIR_PUM_PORT	GPIOD
#define RIGHT_AIR_PUM_PIN 		GPIO_PIN_12

#if(M_PUMP_PWM_DRV)
#define LEFT_AIR_PUM_CHANNEL	TIM_CHANNEL_2
#define RIGHT_AIR_PUM_CHANNEL	TIM_CHANNEL_1
#endif

void drv_air_pump_init(void);

void drv_air_pump_control(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState io_level );


#endif




