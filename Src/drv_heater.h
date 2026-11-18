#ifndef DRV_HEATER_H
#define DRV_HEATER_H
#include "stm32f4xx_hal.h"
#include "m_config.h"


#define HEATER_1_PORT		GPIOG
#define HEATER_1_PIN		GPIO_PIN_3   //加热左
#define HEATER_2_PORT		GPIOG
#define HEATER_2_PIN		GPIO_PIN_4   //加热右

#define M_HEATER_ON		GPIO_PIN_RESET   
#define M_HEATER_OFF		GPIO_PIN_SET    

typedef struct
{
	GPIO_TypeDef *port;
	uint16_t pin;            //gpio port
	uint8_t dutyfactor;      //dutyfactor 0-100
	uint8_t on_cnt;          //on_cnt 0-100
}ht_item_t;


void drv_heater_init(void);

void drv_heater_ctrl( uint8_t ht_id, uint8_t dutyfactors);

ht_item_t *m_get_heater_ctrl_instance(uint8_t partion );

#endif
