#ifndef M_PROTOCOL_H
#define M_PROTOCOL_H
#include "stm32f4xx_hal.h"

#ifndef true
#define true	1
#endif

#ifndef false
#define false	0
#endif

#define DL_SOF	0xA5A5
#define UL_SOF	0xB5B5
#define MJ_EOF 		0x5E

#define MP_SUCCESS		0
#define MP_FAIL			1


#define MAX_BLE_FRAME_SIZE	255
#define MIN_BLE_FRAME_SIZE	6

#define M_CMD_GET_TUNE_MODE		0xE0
#define M_CMD_GET_TUNE_MODE_RSP	0xE0

#define M_CMD_SET_TUNE_MODE		0xE1
#define M_CMD_SET_TUNE_MODE_RSP	0xE1

#define M_CMD_RPT_TUNNING_STATE	0xE2

#define M_CMD_GET_STRENGTH		0xE3
#define M_CMD_GET_STRENGTH_RSP	0xE3

#define M_CMD_SET_STRENGTH		0xE4
#define M_CMD_SET_STRENGTH_RSP	0xE4

#define M_CMD_AI_REPOT				0xE7

#define M_CMD_DEV_INFO				0xE8
#define M_CMD_DEV_INFO_RRSP		0xE8

#define M_CMD_HEATER_CTRL				0xEA
#define M_CMD_HEATER_CTRL_RRSP		0xEA

#define M_CMD_GET_HEATER_CTRL		0xEB
#define M_CMD_GET_HEATER_CTRL_RRSP	0xEB

#define M_CMD_SET_SIP					0xEC
#define M_CMD_SET_SIP_RSP				0xEC

#define M_CMD_GET_SIP					0xED
#define M_CMD_GET_SIP_RSP				0xED

#define M_CMD_GET_APR_PCT			0xF6
#define M_CMD_GET_APR_PCT_RSP		0xF6

#define M_CMD_MENUAL_CFG_APR		0xF7

#define M_CMD_GET_WIFI_MAC		0x7F
#define M_CMD_GET_WIFI_MAC_RSP	0x7F

#define M_CMD_NOTIFY_SNORING		0xC0
#define M_CMD_STOP_SNORING		0xC1


/*******  自行添加宏定义 *******/
#define MJ_SOF_DL 0xA5A5   // 下行帧头
#define MJ_SOF_UL 0xB5B5   // 上行帧头   
   
// 命令码
#define M_CMD_VERSION_QUERY     0xE0
#define M_CMD_VERSION_RSP       0xE1

// 目标对象
#define OBJ_COMM_MODULE   0x01
#define OBJ_MAIN_BOARD    0x02   // 主控板
#define OBJ_AI_MODULE     0x03
#define OBJ_SENSOR        0x04

// ===== 主板固件版本（按需修改） =====
#define MB_FW_VERSION_MAJOR   2
#define MB_FW_VERSION_MINOR   1
#define MB_FW_VERSION_PATCH   3

// ===== 主板硬件版本 =====
#define MB_HW_VERSION_J    1
#define MB_HW_VERSION_N    0
#define MB_HW_VERSION_T    0

typedef enum
{
	M_ROLE_MASTER = 0,
	M_ROLE_SLAVE,	
}m_role_t;

typedef void(*m_cmd_handle_t)( uint8_t *data, uint16_t length);

typedef struct
{
	uint8_t cmd;
	m_cmd_handle_t handle;
}m_cmd_entry_t;

void mp_init( void );

void mp_rx_downlink_data_handle( uint8_t *data, uint16_t length );

void mp_process_frame( uint8_t *data, uint16_t length );

uint8_t mp_calc_cs( uint8_t *data, uint16_t length );

void mp_build_and_send_frame( uint8_t cmd, uint8_t *payload, uint8_t len );

void mp_report_apr_percent_handle( uint8_t partion );

void m_report_tunning_state(uint8_t partion);

m_role_t mp_get_role(void);

void mp_forward_frame_to_slave_board( uint8_t *data, uint16_t length );

void mp_slave_process_foward_data_handle( uint8_t *data, uint16_t length );



#endif


