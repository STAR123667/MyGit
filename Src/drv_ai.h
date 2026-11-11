#ifndef DRV_AI_H
#define DRV_AI_H
#include "stm32f4xx_hal.h"
#include "m_acm.h"

#define AI_UART_RX_BUF_SIZE	256 // UART RX buffer size
#define AI_UART_TX_BUF_SIZE	256 // UART TX buffer size

#define AI_UART_QUEUE_SIZE	5

#define POSTRUE_LIE			1    // posture true
//latericumbent
#define POSTRUE_LAT			2    // lateralumbent
#define POSTRUE_INVALAID	0xFF // posture invalid  

#define STATE_IN_BED		1    // state in bed
#define STATE_LEFT_BED		0xFF // state left bed

#define AI_CMD_AUTO_TUNE		0xF1
#define AI_CMD_AUTO_RPT_STATE	0xF0

#define POSTURE_SUPINE		0x01    /*仰睡*/   
#define POSTURE_LEFT		0x02    /*左侧睡*/ 
#define POSTURE_RIGHT		0x03    /*右侧睡*/
#define POSTURE_NO_PERSON	0xFF    /*无效*/
#define POSTURE_INVALAID	0x04    /*坐起*/
#define POSTURE_LEAVE       0X05    /*离床*/

typedef struct
{
	float apr[MAX_ACL_NUM];
	uint8_t posture;
}tune_cfg_t;

typedef struct
{
	uint8_t posture;          /*人体姿态*/ 
	uint8_t knee_pos;         /*膝盖姿态*/
	uint32_t haunch_mask[4];  /*人体掩码*/
	uint32_t knee_mask[4];    /*膝盖掩码*/
}sensor_status_t;//人体状态

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


