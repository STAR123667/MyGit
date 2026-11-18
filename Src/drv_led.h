#ifndef DRV_LED_H
#define DRV_LED_H
#include "stm32f4xx_hal.h"
#include "m_config.h"

#if(TARGET_BOARD==MJ_BOARD)
#define RUN_LED_PORT		GPIOB
#define RUN_LED_PIN			GPIO_PIN_6
#else
#define RUN_LED_PORT		GPIOC
#define RUN_LED_PIN			GPIO_PIN_0
#endif

void drv_led_init(void);

#endif
