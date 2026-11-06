#ifndef M_STABLE_H
#define M_STABLE_H
#include "stm32f4xx_hal.h"
#include "arm_math.h"

#define M_STABLE_THRESHOLD		0.2f

/*
	return: 1:stable, 0: not stable
*/
uint8_t m_is_stable( const float32_t * sample, uint32_t length );

#endif

