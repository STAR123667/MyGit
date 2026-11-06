#include "m_ota.h"
#include "m_flash_if.h"
#include "m_protocol.h"
#include "m_log.h"
#include "m_config.h"
#include "m_misc.h"

extern UART_HandleTypeDef huart3;

static uint32_t g_fw_size=0;
static uint32_t g_fw_offset=0;
static uint32_t g_new_fw_ver=0;
static uint16_t g_fw_crc_calc=0xFFFF;
static uint16_t g_fw_crc_notify=0xFFFF;
static TimerHandle_t m_timer_ota=NULL;

static uint32_t m_ota_save_fw_block(uint32_t offset, uint8_t *data, uint16_t length );

static void m_ota_start_update_fw(void);

static void m_ota_report_version( void );

static void m_ota_query_new_fw( void );

static void m_ota_img_block_request( uint32_t file_offset, uint8_t req_size );

static void m_ota_end_upgrade_request( uint8_t status );

//static void m_ota_build_and_send_frame( uint8_t cmd, uint8_t *payload, uint16_t len );

static void m_ota_query_version_handle( uint8_t *frame, uint8_t length );

static void m_ota_notify_new_fw_handle( uint8_t *frame, uint8_t length );

static void m_ota_query_new_fw_rsp_handle( uint8_t *frame, uint8_t length );

static void m_ota_img_block_rsp_handle( uint8_t *frame, uint8_t length );

static void m_ota_end_upgrade_rsp_handle( uint8_t *frame, uint8_t length );

static void m_ota_timer_callback(TimerHandle_t xTimer) ;

//================================================================

void m_ota_init(void)
{
	m_timer_ota = xTimerCreate("ota",
								pdMS_TO_TICKS(1000),  
								pdFALSE, 
								NULL,
								m_ota_timer_callback);
	xTimerStop( m_timer_ota, pdMS_TO_TICKS(1));

	#if 0
	{
		uint32_t addr=OTA_FW_ADDRESS;
		uint32_t ret=0;
		uint32_t fail_cnt=0;

		uint8_t value=0xAB;

		while(addr<OTA_FW_END_ADDRESS)
		{
			ret = FLASH_If_Write( addr, &value, 1 );
			addr++;

			if(ret != 0)
			{
				fail_cnt++;
			}
		}

		fail_cnt =0;
	}
	#endif

}

void m_ota_process_frame( uint8_t *data, uint16_t length )
{
	uint8_t cmd;

	cmd = data[2];

	LOG("ota cmd: %d", cmd);
	
	switch (cmd)
	{
		case OTA_CMD_VER_QUERY:
			m_ota_query_version_handle( data, length );			
		break;

		case OTA_CMD_FW_NOTIFY:
			m_ota_notify_new_fw_handle( data, length );			
		break;

		case OTA_CMD_FW_RSP_V2:
			m_ota_query_new_fw_rsp_handle( data, length );			
		break;
		
		case OTA_CMD_FW_BLOCK_RESP:
			m_ota_img_block_rsp_handle( data, length );			
		break;

		case OTA_CMD_FW_END_UPG_RSP:
			m_ota_end_upgrade_rsp_handle( data, length );			
		break;
		
		default :

		break;
	}

}


uint32_t m_ota_save_fw_block(uint32_t file_offset, uint8_t *data, uint16_t length )
{
	return FLASH_If_Write( OTA_FW_ADDRESS+file_offset, data, length );
}

void m_ota_start_update_fw(void)
{
	ota_info_t ota_info;

	ota_info.ota_pending_flag = OTA_PENDING_FLAG;
	ota_info.img_size = g_fw_size;

	FLASH_If_Erase_Area( OTA_INFO_ADDRESS, OTA_INFO_END_ADDRESS );

	if( 0 == FLASH_If_Write( OTA_INFO_ADDRESS, (uint8_t *)&ota_info, sizeof(ota_info_t)))
	{
		LOG("update img afte reboot...");
		__NVIC_SystemReset();
	}
	else
	{
		LOG("write img info fail");
	}
}


void m_ota_report_version( void )
{
	uint8_t payload[10];
	uint8_t *offset;

	offset = payload;

	*offset++ = HIGH_BYTE(MF_CODE);
	*offset++ = LOW_BYTE(MF_CODE);

	*offset++ = HIGH_BYTE(IMG_TYPE);
	*offset++ = LOW_BYTE(IMG_TYPE);

	*offset++ = BREAK_UINT32(SW_VER_VALUE, 3);
	*offset++ = BREAK_UINT32(SW_VER_VALUE, 2);
	*offset++ = BREAK_UINT32(SW_VER_VALUE, 1);
	*offset++ = BREAK_UINT32(SW_VER_VALUE, 0);

	*offset++ = HIGH_BYTE(HW_VER_VALUE);
	*offset++ = LOW_BYTE(HW_VER_VALUE);

	mp_build_and_send_frame( OTA_CMD_VER_RSP, payload, offset-payload);
}

void m_ota_query_new_fw( void )
{
	uint8_t payload[10];
	uint8_t *offset;

	offset = payload;

	*offset++ = HIGH_BYTE(MF_CODE);
	*offset++ = LOW_BYTE(MF_CODE);

	*offset++ = HIGH_BYTE(IMG_TYPE);
	*offset++ = LOW_BYTE(IMG_TYPE);

	*offset++ = BREAK_UINT32(SW_VER_VALUE, 3);
	*offset++ = BREAK_UINT32(SW_VER_VALUE, 2);
	*offset++ = BREAK_UINT32(SW_VER_VALUE, 1);
	*offset++ = BREAK_UINT32(SW_VER_VALUE, 0);

	*offset++ = HIGH_BYTE(HW_VER_VALUE);
	*offset++ = LOW_BYTE(HW_VER_VALUE);

	mp_build_and_send_frame( OTA_CMD_FW_QUERY_V2, payload, offset-payload);
}


void m_ota_img_block_request( uint32_t file_offset, uint8_t req_size )
{
	uint8_t payload[13];
	uint8_t *offset;

	offset = payload;

	*offset++ = HIGH_BYTE(MF_CODE);
	*offset++ = LOW_BYTE(MF_CODE);

	*offset++ = HIGH_BYTE(IMG_TYPE);
	*offset++ = LOW_BYTE(IMG_TYPE);

	*offset++ = BREAK_UINT32(g_new_fw_ver, 3);
	*offset++ = BREAK_UINT32(g_new_fw_ver, 2);
	*offset++ = BREAK_UINT32(g_new_fw_ver, 1);
	*offset++ = BREAK_UINT32(g_new_fw_ver, 0);

	*offset++ = BREAK_UINT32(g_fw_offset, 3);
	*offset++ = BREAK_UINT32(g_fw_offset, 2);
	*offset++ = BREAK_UINT32(g_fw_offset, 1);
	*offset++ = BREAK_UINT32(g_fw_offset, 0);

	*offset++ = req_size;

	mp_build_and_send_frame( OTA_CMD_FW_BLOCK_REQ, payload, offset-payload);

	LOG("req block, offset: %d, %d bytes", file_offset, req_size );
}

void m_ota_end_upgrade_request( uint8_t status )
{
	uint8_t payload[13];
	uint8_t *offset;

	offset = payload;

	*offset++ = status;

	*offset++ = HIGH_BYTE(MF_CODE);
	*offset++ = LOW_BYTE(MF_CODE);

	*offset++ = HIGH_BYTE(IMG_TYPE);
	*offset++ = LOW_BYTE(IMG_TYPE);

	*offset++ = BREAK_UINT32(g_fw_offset, 3);
	*offset++ = BREAK_UINT32(g_fw_offset, 2);
	*offset++ = BREAK_UINT32(g_fw_offset, 1);
	*offset++ = BREAK_UINT32(g_fw_offset, 0);

	*offset++ = MAX_BLOCK_SIZE;

	mp_build_and_send_frame( OTA_CMD_FW_END_UPG_REQ, payload, offset-payload);
}

#if 0
void m_ota_build_and_send_frame( uint8_t cmd, uint8_t *payload, uint16_t len )
{
	static uint8_t tx_frame[ MAX_BLE_FRAME_SIZE ];
	uint8_t *offset;

	offset = tx_frame;

	*offset++ = 0xB5;
	*offset++ = 0xB5;
	*offset++ = cmd;
	*offset++ = length;
	if( length > 0 )
	{
		for( uint8_t i=0;i<length;i++)
		{	
			*offset++ = payload[i];
		}
	}

	*offset++ = ble_calc_cs( tx_frame+2, 2+length );
	*offset++ = EOF;

	//HAL_UART_Transmit_DMA( &huart3, tx_frame, offset - tx_frame );
	HAL_UART_Transmit(&huart3,  tx_frame, offset - tx_frame, HAL_MAX_DELAY);

	LOG("tx ble data:");

}
#endif

void m_ota_query_version_handle( uint8_t *frame, uint8_t length )
{
	uint16_t mf_cod=0;
	uint8_t *offset;

	offset = frame+4;

	mf_cod = BUILD_UINT16(offset[1], offset[0]);

	if( MF_CODE == mf_cod )
	{
		m_ota_report_version();
	}
}

void m_ota_notify_new_fw_handle( uint8_t *frame, uint8_t length )
{
	uint16_t mf_cod=0;
	uint16_t img_type=0;
	uint8_t *offset;

	offset = frame+4;

	mf_cod = BUILD_UINT16(offset[1], offset[0]);
	offset += 2;

	img_type = BUILD_UINT16(offset[1], offset[0]);
	offset += 2;

	g_new_fw_ver = BUILD_UINT32(offset[3], offset[2], offset[1], offset[0]);
	offset += 4;

	if( ( MF_CODE == mf_cod )&&( IMG_TYPE == img_type ))
	{
		m_ota_query_new_fw();
	}
	else
	{
		g_new_fw_ver=0;
		g_fw_size=0;
		g_fw_offset=0;
	}

}

void m_ota_query_new_fw_rsp_handle( uint8_t *frame, uint8_t length )
{
	uint16_t mf_cod=0;
	uint16_t img_type=0;
	uint8_t *offset;
//	uint8_t status;

	offset = frame+4;
	
//	status = offset[0];
	offset++;

	mf_cod = BUILD_UINT16(offset[1], offset[0]);
	offset += 2;

	img_type = BUILD_UINT16(offset[1], offset[0]);
	offset += 2;

	g_new_fw_ver = BUILD_UINT32(offset[3], offset[2], offset[1], offset[0]);
	offset += 4;

	g_fw_size =  BUILD_UINT32(offset[3], offset[2], offset[1], offset[0]);
	offset += 4;

	g_fw_crc_notify =  BUILD_UINT16(offset[1], offset[0]);
	offset += 2;
	
	if(  ( MF_CODE == mf_cod )&&( IMG_TYPE == img_type )&&
		( 0 < g_fw_size )&&(g_fw_size<=(APPLICATION_END_ADDRESS-APPLICATION_ADDRESS)))
	{
		g_fw_offset=0;
		g_fw_crc_calc=0xFFFF;

		FLASH_If_Init();

		FLASH_If_Erase_Area(OTA_FW_ADDRESS, OTA_FW_END_ADDRESS);

		xTimerStart( m_timer_ota, pdMS_TO_TICKS(1));
		
		m_ota_img_block_request( g_fw_offset, MAX_BLOCK_SIZE );
	}
	else
	{
		g_new_fw_ver=0;
		g_fw_size=0;
		g_fw_offset=0;
	}
}

void m_ota_img_block_rsp_handle( uint8_t *frame, uint8_t length )
{
	uint16_t mf_cod=0;
	uint16_t img_type=0;
	uint8_t *offset;
	uint32_t file_offset;
	uint32_t data_size;
	uint8_t status;
	uint32_t sw_ver;
	
	offset = frame+4;

	status = offset[0];
	offset++;

	if( 0 == status )
	{
		mf_cod = BUILD_UINT16(offset[1], offset[0]);
		offset += 2;

		img_type = BUILD_UINT16(offset[1], offset[0]);
		offset += 2;

		sw_ver = BUILD_UINT32(offset[3], offset[2], offset[1], offset[0]);
		offset += 4;
		sw_ver=sw_ver;

		file_offset =  BUILD_UINT32(offset[3], offset[2], offset[1], offset[0]);
		offset += 4;

		data_size =  BUILD_UINT32(offset[3], offset[2], offset[1], offset[0]);
		offset += 4;
		

		if(  ( MF_CODE == mf_cod )&&( IMG_TYPE == img_type )&&
			(file_offset == g_fw_offset)&&
			( 0 < g_fw_size )&&(g_fw_size<=(APPLICATION_END_ADDRESS-APPLICATION_ADDRESS)))
		{
			uint32_t ret=0;
			
			ret = m_ota_save_fw_block(g_fw_offset, offset, data_size );

			g_fw_crc_calc = modbus_crc_update( g_fw_crc_calc, offset, data_size );

			if( 0 == ret )
			{
				g_fw_offset += data_size;

				LOG("file size: %d, file offset: %d, percent: %d%%", 
					g_fw_size, g_fw_offset, g_fw_offset*100/g_fw_size);
				
				if(g_fw_offset >= g_fw_size)
				{
					LOG("file check: crc_calc: 0x%04x, crc_notify: 0x%04x", 
						g_fw_crc_calc, g_fw_crc_notify );
									
					if(g_fw_crc_calc ==  g_fw_crc_notify)
					{
						m_ota_end_upgrade_request(OTA_STATUS_SUCCESS);

						LOG("img crc ckeck ok!");
					}
					else
					{
						m_ota_end_upgrade_request(OTA_STATUS_VERIFY_FAIL);
						LOG("img crc fail!");

						xTimerStop( m_timer_ota, pdMS_TO_TICKS(1));
					}
				}
				else
				{
					if( g_fw_size-g_fw_offset < MAX_BLOCK_SIZE)
					{
						m_ota_img_block_request(g_fw_offset,g_fw_size-g_fw_offset );
					}
					else
					{
						m_ota_img_block_request(g_fw_offset, MAX_BLOCK_SIZE );
					}

					xTimerStop( m_timer_ota, pdMS_TO_TICKS(1));
				}
			}
			else
			{
				m_ota_end_upgrade_request(OTA_STATUS_VERIFY_FAIL);
				LOG("img block write fail!");
			}
		}
		else
		{
			g_new_fw_ver=0;
			g_fw_size=0;
			g_fw_offset=0;
			xTimerStop( m_timer_ota, pdMS_TO_TICKS(1));
			LOG("ota abort!, file_offset: %d", file_offset);
		}
	}
	
}

void m_ota_end_upgrade_rsp_handle( uint8_t *frame, uint8_t length )
{
	xTimerStop( m_timer_ota, pdMS_TO_TICKS(1));
	m_ota_start_update_fw();
}

void m_ota_timer_callback(TimerHandle_t xTimer)
{
	if(g_fw_offset>0)
	{
		if( g_fw_size-g_fw_offset < MAX_BLOCK_SIZE)
		{
			m_ota_img_block_request(g_fw_offset,g_fw_size-g_fw_offset );
		}
		else
		{
			m_ota_img_block_request(g_fw_offset, MAX_BLOCK_SIZE );
		}
	}
}


