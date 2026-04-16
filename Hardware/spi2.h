
#ifndef STM32_SPI2_H
#define STM32_SPI2_H

#include "stm32f10x.h"
#include "Sensor.h"

/******************************************************************************/
void SPI2_Init_(MagnetSensor_Para *p);
void SPI2_Init_MT6835(void);
void SPI2_Init_ICMU(void);

unsigned short SPIx_ReadWriteByte(unsigned short byte);
uint16_t SPIx_ReadWriteByte_MT6835(uint16_t byte);
uint16_t SPIx_ReadWriteByte_ICMU(uint16_t byte);
/******************************************************************************/


#endif
