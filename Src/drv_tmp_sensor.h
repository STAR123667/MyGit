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

/* 定时加热: 以 tmp 为目标温度开始加热, seconds 秒后自动关闭 */
void m_set_target_temperature_with_timer(uint8_t partion, uint8_t tmp, uint32_t seconds);

/* 1 秒节拍: 递减定时加热剩余时间, 到点后关闭对应加热器 */
void m_heater_timer_tick_1s(void);


#endif
