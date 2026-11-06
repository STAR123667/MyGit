#ifndef M_OTA_H
#define M_OTA_H

#include "stm32f4xx_hal.h"
#include "m_micro.h"

#define MAX_BLOCK_SIZE		220

#define OTA_STATUS_SUCCESS		0x00
#define OTA_STATUS_VERIFY_FAIL	0x96
#define OTA_STATUS_TERMINATE	0x95

#define BUILD_UINT16(loByte, hiByte) \
          ((uint16_t)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))

#define LOW_BYTE(n)		((uint8_t)(n&0xFF))

#define HIGH_BYTE(n)	((uint8_t)((n>>8)&0xFF))

#define BREAK_UINT32( var, ByteNum ) \
          (uint8_t)((uint32_t)(((var) >>((ByteNum) * 8)) & 0x00FF))

#define BUILD_UINT32(Byte0, Byte1, Byte2, Byte3) \
          ((uint32_t)((uint32_t)((Byte0) & 0x00FF) \
          + ((uint32_t)((Byte1) & 0x00FF) << 8) \
          + ((uint32_t)((Byte2) & 0x00FF) << 16) \
          + ((uint32_t)((Byte3) & 0x00FF) << 24)))
#define OTA_CMD_MIN					0xA1
#define OTA_CMD_VER_QUERY			0xA1
#define OTA_CMD_VER_RSP			0xA2
#define OTA_CMD_FW_NOTIFY			0xA3
#define OTA_CMD_FW_QUERY			0xA4
#define OTA_CMD_FW_QUERY_V2		0xAD
#define OTA_CMD_FW_RSP			0xA5
#define OTA_CMD_FW_RSP_V2			0xAC
#define OTA_CMD_FW_BLOCK_REQ		0xA6
#define OTA_CMD_FW_BLOCK_RESP		0xA7
#define OTA_CMD_FW_END_UPG_REQ	0xA8
#define OTA_CMD_FW_END_UPG_RSP	0xA9
#define OTA_CMD_MAX				0xAD

#define OTA_PENDING_FLAG			0xBEEFBEEF
typedef struct
{
	uint32_t	ota_pending_flag;
	uint32_t 	img_size;
}ota_info_t;

void m_ota_init(void);

uint32_t m_ota_save_fw_block(uint32_t file_offset, uint8_t *data, uint16_t length );

void m_ota_start_update_fw(void);

void m_ota_process_frame( uint8_t *data, uint16_t length );

#endif

