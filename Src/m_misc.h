#ifndef M_MISC_H
#define M_MISC_H
#include "stm32f4xx_hal.h"

uint16_t modbus_crc_table(const uint8_t *data, uint32_t len) ;

uint16_t modbus_crc_update(uint16_t crc, const uint8_t *data, uint32_t len);

#endif
