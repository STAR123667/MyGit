#ifndef DRV_TMP_SENSOR_H
#define DRV_TMP_SENSOR_H

#include "stm32f4xx_hal.h"

#define MAX_TMP_SENSOR_FRAME_SIZE	32

#define MODBUS_FUNC_READ			0x03
#define MODBUS_FUNC_WRITE		0x06

void drv_tmp_sensor_init(void);

void drv_tmp_sensor_process_frame( uint8_t *frame, uint16_t length );

void drv_tmp_sensor_query_current_value( void );

void m_set_target_temperature(uint8_t partion, uint8_t tmp );


#endif
