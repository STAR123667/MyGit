#ifndef DRV_SV_H
#define DRV_SV_H

#include "stm32f4xx_hal.h"

#define M_SV_ON			GPIO_PIN_RESET
#define M_SV_OFF			GPIO_PIN_SET


#define PUMP_SV_POWER_EN_PORT		GPIOA
#define PUMP_SV_POWER_EN_PIN		GPIO_PIN_12

#define SV_POWER_EN_PORT				GPIOG
#define SV_POWER_EN_PIN				GPIO_PIN_2

#define SV_ON_STATE_DUTY				95
#define SV_ON_STATE_KEEP_DUTY		30

#define TURN_ON_SV_HOLD_TICK			50000	//5000		//50ms

typedef enum
{
	SV_ID_01=0,
	SV_ID_02,
	SV_ID_03,
	SV_ID_04,
	SV_ID_05,
	SV_ID_06,
	SV_ID_07,
	SV_ID_08,
	
	SV_ID_09,
	SV_ID_10,
	SV_ID_11,
	SV_ID_12,
	SV_ID_13,
	SV_ID_14,
	SV_ID_15,
	SV_ID_16,
	
	VV_ID_01,
	VV_ID_02,
	VV_ID_03,
}sv_id_t;

typedef struct
{
	GPIO_TypeDef *port;
	uint16_t pin;
	uint8_t dutyfactor;
	uint8_t pulse_wide_cnt;
	uint8_t state;
	uint32_t on_cnt;
}sv_item_t;




void drv_solenoid_valve_init(void);

void drv_solenoid_valve_control( uint8_t sv_id, GPIO_PinState io_level );

uint32_t m_get_sv_state_mask(void);

void m_timer6_ms_irq_callback(void);

#endif
