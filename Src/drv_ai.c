#include "drv_ai.h"
#include "m_micro.h"
#include "m_acm.h"
#include "m_protocol.h"
#include "m_log.h"
#include "m_protocol.h"
#include "m_misc.h"
//const static char * nv_tune_cfg_nspc="nspc_tune_cfg";
//const static char * nv_tune_cfg_key="key_tune_cfg";

//static void drv_ai_uart_rx_task(void * argument);

//static uint16_t modbus_crc_table(const uint8_t *data, uint16_t len);
static uint16_t ai_calc_check_sum(uint8_t *data, uint16_t length);

extern UART_HandleTypeDef huart1;
//static uint8_t ai_uart_rx_buf[128];
//static uint8_t ai_uart_rx_length=0;

tune_cfg_t g_tune_cfg[2]=
{
	{
		 .posture=POSTRUE_LIE,
		.apr={2.0, 2.0, 2.0, 2.0, 2.0, 2.0, },
	},
	{
		 .posture=POSTRUE_LAT,
		.apr={8.0, 8.0, 8.0, 8.0, 8.0, 8.0, },
	},
};

uint8_t g_active=false;

sensor_status_t g_sensor_status[2]=
{
	{
		.posture = POSTURE_INVALAID,
	},
	{
		.posture = POSTURE_INVALAID,
	},		
};

void drv_ai_init(void)
{

}

void drv_ai_process_frame( uint8_t *frame, uint16_t length )
{
	static uint8_t leave_bed_cnt[2]={0,0};
	#if 1
	uint8_t status=0;
	uint8_t *left_apr_list;
	uint8_t *right_apr_list;
	uint8_t posture_old[2];
	acm_msg_set_apr_seq_t  apr_seq;

	posture_old[0] = g_sensor_status[0].posture;
	posture_old[1] = g_sensor_status[1].posture;
	
	if(drv_ai_is_frame_valaid(frame, length) == true)
	{
		if( ( 58 == length )&&(0x02 == frame[12])&&(0x10 == frame[13]))
		{
			if((true == m_is_ai_action_doing())&&
			    (false == m_is_tunning_queue_empty()))
			{
				LOG("@@@@@ doing ai ctrl, ignore");
			}
			else
			{
				
				acm_msg_ai_ctrl_t ai_ctrl;
			
				left_apr_list = &frame[36];
				right_apr_list = &frame[45];
			
				ai_ctrl.mask = 0;

				g_sensor_status[0].posture= frame[16];
				g_sensor_status[0].knee_pos = frame[17];

				for(uint8_t i=0;i<4;i++)
				{
					g_sensor_status[0].haunch_mask[i] = frame[18+i];
				}
				for(uint8_t i=0;i<4;i++)
				{
					g_sensor_status[0].knee_mask[i] = frame[22+i];
				}


				g_sensor_status[1].posture= frame[26];
				g_sensor_status[1].knee_pos = frame[27];

				for(uint8_t i=0;i<4;i++)
				{
					g_sensor_status[1].haunch_mask[i] = frame[28+i];
				}
				for(uint8_t i=0;i<4;i++)
				{
					g_sensor_status[1].knee_mask[i] = frame[32+i];
				}

				apr_seq.mask = 0;
				
				for(uint8_t i=0;i<2;i++)
				{
					if( POSTURE_NO_PERSON == g_sensor_status[i].posture )
					{
						if(leave_bed_cnt[i]<5)
						{
							leave_bed_cnt[i]++;
							if(5==leave_bed_cnt[i])
							{
								if(0==i)	
								{
									for(uint8_t n=1;n<8;n++)
									{
										apr_seq.mask  |= BIT(n);
										apr_seq.target_apr[n] = MAX_APR*0.5f;
									}
								}
								
								if(1==i)	
								{
									for(uint8_t n=9;n<16;n++)
									{
										apr_seq.mask  |= BIT(n);
										apr_seq.target_apr[n] = MAX_APR*0.5f;
									}
								}
								
							}
						}
					}
					else
					{
						leave_bed_cnt[i] = 0;
					}
				}

				if(apr_seq.mask !=0)
				{
					m_acm_set_target_apr_seq( &apr_seq );
				}
				else
				{
					if( (g_sensor_status[0].posture!=POSTURE_INVALAID)&&
						(g_sensor_status[0].posture != posture_old[0] )&&
						(TUNE_MODE_AUTO == m_get_run_para_instance(PARTION_LEFT)->tune_mode))
					{
						LOG("^^^^^ left posture %d change to %d", posture_old[0], g_sensor_status[0].posture );
						for(uint8_t i=0;i<MAX_ACL_NUM/2;i++)
						{
							if((left_apr_list[i] != 0xFF)&&(left_apr_list[i] != 0xFE))
							{
								if( MAX_ACL_NUM/2 - 1 == i )
								{
									ai_ctrl.target_apr[i] = left_apr_list[i+1]*MAX_APR/100;
									ai_ctrl.mask|=BIT(i);
								}
								else
								{
									ai_ctrl.target_apr[i] = left_apr_list[i]*MAX_APR/100;
									ai_ctrl.mask|=BIT(i);
								}
							}
						}
					}

					if( (g_sensor_status[1].posture!=POSTURE_INVALAID)&&
						(g_sensor_status[1].posture != posture_old[1] )&&
						(TUNE_MODE_AUTO == m_get_run_para_instance(PARTION_RIGHT)->tune_mode))	
					{
						LOG("^^^^^ right posture %d change to %d", posture_old[1], g_sensor_status[1].posture );
						
						for(uint8_t i=0;i<MAX_ACL_NUM/2;i++)
						{
							if((right_apr_list[i] != 0xFF)&&(right_apr_list[i] != 0xFF))
							{
								if( MAX_ACL_NUM/2 - 1 == i )
								{
									ai_ctrl.target_apr[MAX_ACL_NUM/2+i] = right_apr_list[i+1]*MAX_APR/100;
									ai_ctrl.mask|=BIT(MAX_ACL_NUM/2+i);
								}
								else
								{
									ai_ctrl.target_apr[MAX_ACL_NUM/2+i] = right_apr_list[i]*MAX_APR/100;
									ai_ctrl.mask|=BIT(MAX_ACL_NUM/2+i);
								}
							}
						}
					}
					
					if(ai_ctrl.mask != 0)
					{
						m_acm_ai_ctrl( &ai_ctrl );
					}
				}
			}
		}

		m_build_and_send_frame_to_ai(frame[2], &status, 1 );
	}
	else
	{
		LOG("XXX ai frame invalaid");
	}
	
	#endif
}

uint8_t drv_ai_is_frame_valaid(uint8_t *frame, uint16_t length )
{
	uint8_t fctrl;
	uint16_t len_value=0;
	uint8_t crc_len=0;

	fctrl = frame[3];

	if(fctrl&BIT(7))
	{
		crc_len = 2;
	}
	
	if(
	    (0xA5==frame[0])&&
	    (0xA5==frame[1])&&
	    (0x0A==frame[length-1])&&
	    (0x0D==frame[length-2]))
	{
		uint16_t cs;
		uint16_t cs_calc;

		len_value = BUILD_UINT16(frame[10], frame[11]);

		if( len_value + 14+ crc_len != length )
		{
			return false;
		}

		cs = BUILD_UINT16(frame[length-4], frame[length-3]);
		cs_calc = ai_calc_check_sum(frame, length-4);
		
		if( cs == cs_calc )
		{
			return true;
		}

		#if 0
		uint16_t crc;
		uint16_t calc_crc;

		crc = frame[length-4]<<8|frame[length-3];
		calc_crc = modbus_crc_table(frame+2, length-6);

		if( crc == calc_crc )
		{
			return true;
		}
		#endif
	}

	return false;
}
	
void drv_ai_query_state( void )
{
	uint8_t frame[]={ 0xB5, 0xB5, 0xFA, 0x01, 0xFF, 0x21, 0x10, 0x0D, 0x0A};

	g_active = true;

	HAL_UART_Transmit(&huart1,  frame, sizeof(frame), pdMS_TO_TICKS(5));
}

tune_cfg_t *m_get_tune_cfg_instance(uint8_t posture )
{
	for(uint8_t i=0;i<ARRAY_SIZE(g_tune_cfg);i++)
	{
		if(g_tune_cfg[i].posture == posture)
		{
			return &g_tune_cfg[i];
		}
	}

	return NULL;
}


uint8_t drv_ai_load_cfg(void)
{
	uint8_t ret=0;

	#if 0
	tune_cfg_t tune_cfg[2];
	nvs_handle_t handle;
	
	size_t length;
	
	ret = nvs_open(nv_tune_cfg_nspc, NVS_READONLY, &handle);
	if(ESP_OK == ret )
	{
		ret = nvs_get_blob( handle, nv_tune_cfg_key, (void *)(tune_cfg), &length);

		if(ESP_OK == ret )
		{
			ESP_LOGI(TAG,"load tun cfg success, length: %d", length);

			for(uint8_t i=0;i<ARRAY_SIZE(tune_cfg);i++)
			{
				if(tune_cfg[i].acl_mask&0xE0)
				{
					ret = ESP_FAIL;
				}

				if((tune_cfg[i].posture !=POSTRUE_LIE)&&
					(tune_cfg[i].posture !=POSTRUE_LAT))
				{
					ret = ESP_FAIL;
				}

				if((tune_cfg[i].posture !=STATE_IN_BED)&&
					(tune_cfg[i].posture !=STATE_LEFT_BED))
				{
					ret = ESP_FAIL;
				}

				if(tune_cfg[i].apr > MAX_APR )
				{
					ret = ESP_FAIL;
				}
			}

			if(ESP_OK == ret )
			{
				memcpy((uint8_t *)g_tune_cfg, (uint8_t *)tune_cfg, sizeof(tune_cfg));

				for(uint8_t i=0;i<ARRAY_SIZE(tune_cfg);i++)
				{
					printf("tune cfg %d, posture: %d, alc_mask: 0x%02x, apr: %f\r\n",
						i,g_tune_cfg[i].posture, g_tune_cfg[i].acl_mask, g_tune_cfg[i].apr);
				}
			}

		}

		nvs_close(handle);
	}

	if(ESP_OK != ret )
	{
		ESP_LOGI( TAG, "load ai cfg fail!");
	}
	#endif

	return ret;
}

uint8_t drv_ai_save_cfg( void)
{
	uint8_t ret=0;

	#if 0
	nvs_handle_t handle;
	
	
	ret = nvs_open(nv_tune_cfg_nspc, NVS_READWRITE, &handle);
	if(ESP_OK == ret )
	{
		ret = nvs_set_blob( handle, nv_tune_cfg_key, (void *)(g_tune_cfg), sizeof(g_tune_cfg));

		if(ESP_OK == ret )
		{
			ESP_LOGI(TAG,"save tune cfg success:");
			for(uint8_t i=0;i<ARRAY_SIZE(g_tune_cfg);i++)
			{
				printf("tune cfg %d, posture: %d, alc_mask: 0x%02x, apr: %f\r\n",
					i,g_tune_cfg[i].posture, g_tune_cfg[i].acl_mask, g_tune_cfg[i].apr);
			}
		}

		nvs_close(handle);
	}

	if(ESP_OK != ret )
	{
		ESP_LOGI( TAG, "save ai cfg fail!");
	}
	#endif

	return ret;
}

void m_build_and_send_frame_to_ai(uint8_t cmd, uint8_t *payload, uint8_t length)
{
	static uint8_t mp_upd_frame[ MAX_BLE_FRAME_SIZE ];
	uint8_t *offset;
	uint16_t crc=0;

	if( length + 6 > sizeof(mp_upd_frame))
	{
		return;
	}
	
	offset = mp_upd_frame;

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

	crc = modbus_crc_table( mp_upd_frame+2, 2+length );
	*offset++ = HIGH_BYTE(crc);
	*offset++ = LOW_BYTE(crc);
	*offset++ = 0x0D;
	*offset++ = 0x0A;

	
	HAL_UART_Transmit(&huart1,  mp_upd_frame, offset - mp_upd_frame, pdMS_TO_TICKS(5));
}


uint16_t ai_calc_check_sum(uint8_t *data, uint16_t length)
{
	uint16_t sum=0;

	for(uint16_t i=0;i<length;i++)
	{
		sum += data[i];
	}

	return sum;
}


sensor_status_t *m_get_ai_sensor_status( uint8_t partion )
{
	if(( PARTION_LEFT != partion )&&(PARTION_RIGHT != partion))
	{
		return NULL;
	}

	return &g_sensor_status[partion-1];
}
	

void m_reset_posture(uint8_t partion)
{
	if( ( PARTION_LEFT != partion )&&
	     ( PARTION_RIGHT != partion ))
		
	{
		return;
	}

	LOG("^^^^^ reset posture of %s",(PARTION_LEFT == partion)?"left":"right");
	g_sensor_status[partion-1].posture = POSTURE_INVALAID;
}
	


