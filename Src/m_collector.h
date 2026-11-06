#ifndef M_COLLECTOR_H
#define M_COLLECTOR_H
#include "stm32f4xx_hal.h"

#define REFER_VOLTAGE       3.3		//can't define as 3.3f!!!!,or will cause ADC result invalaid
#define CONVERT_BITS        (1 << 12)


#define ADC_CH_NUM				16
#define ADC_TIMES_PER_ROUND	5

#define CLTR_EVENT_ADC_DONE			0x00000001

typedef struct
{
	ADC_HandleTypeDef* adc_handle;
	uint32_t *cache;
	uint32_t size;
	uint32_t mis_cnt;
	uint8_t b_new;
}m_adc_cache_t;

void m_collector_init(void);

#endif
