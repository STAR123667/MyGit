#ifndef DRV_AI_H
#define DRV_AI_H
#include "stm32f4xx_hal.h"
#include "m_acm.h"

#define AI_UART_RX_BUF_SIZE	256
#define AI_UART_TX_BUF_SIZE	256

#define AI_UART_QUEUE_SIZE	5

#define POSTRUE_LIE			1
//latericumbent
#define POSTRUE_LAT			2
#define POSTRUE_INVALAID	0xFF

#define STATE_IN_BED			1
#define STATE_LEFT_BED		0xFF

#define AI_CMD_AUTO_TUNE		0xF1
#define AI_CMD_AUTO_RPT_STATE	0xF0

#define POSTURE_SUPINE		0x01		/*Ñö×Å*/
#define POSTURE_LEFT		0x02
#define POSTURE_RIGHT		0x03
#define POSTURE_NO_PERSON	0xFF
#define POSTURE_INVALAID	0x04

typedef struct
{
	float apr[MAX_ACL_NUM];
	uint8_t posture;
}tune_cfg_t;

typedef struct
{
	uint8_t posture;
	uint8_t knee_pos;
	uint32_t haunch_mask[4];
	uint32_t knee_mask[4];
}sensor_status_t;

void drv_ai_init(void);

void drv_ai_query_state( void );

void drv_ai_process_frame( uint8_t *frame, uint16_t length );

uint8_t drv_ai_load_cfg(void);

uint8_t drv_ai_save_cfg( void);

void m_build_and_send_frame_to_ai(uint8_t cmd, uint8_t *payload, uint8_t length);

uint8_t drv_ai_is_frame_valaid(uint8_t *frame, uint16_t length );

sensor_status_t *m_get_ai_sensor_status( uint8_t partion );

void m_reset_posture(uint8_t partion);

uint8_t m_is_tunning_queue_empty(void);

#endif


