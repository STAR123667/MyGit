#include "m_protocol.h"
#include "m_log.h"
#include "m_ota.h"
#include "m_micro.h"
#include "m_acm.h"
#include "m_config.h"
#include "drv_ai.h"
#include "m_uart_traffic.h"
#include "drv_heater.h"
#include "m_misc.h"
#include "drv_tmp_sensor.h"

extern UART_HandleTypeDef huart3;  /* UART3 - BLE蓝牙模块 (下行接收/上行发送) */
extern UART_HandleTypeDef huart4;  /* UART4 - AI视觉模块 */
extern UART_HandleTypeDef huart5;  /* UART5 - 温度传感器 */

static uint8_t mp_is_frame_valaid( uint8_t *data, uint16_t length );/* 校验帧合法性 (SOF+长度+CS) */

static void mp_process_frame( uint8_t *data, uint16_t length );/* 命令分发入口 (OTA/业务表) */

static void mp_get_tune_mode_handle( uint8_t *data, uint16_t length );// 查询自动调温模式  	

static void mp_manual_cfg_target_apr_handle( uint8_t *data, uint16_t length );//处理手动配置目标温度
        
static void mp_set_tune_mode_handle( uint8_t *data, uint16_t length );// 设置自动调温模式

static void mp_get_apr_percent_handle( uint8_t *data, uint16_t length );//处理获取目标温度百分比

void mp_get_strength_handle( uint8_t *data, uint16_t length );//处理获取加热器功率

void mp_set_strength_handle( uint8_t *data, uint16_t length );//处理设置加热器功率

void mp_get_wifi_mac_handle( uint8_t *data, uint16_t length );//处理获取WiFi MAC地址

void mp_get_device_info_handle( uint8_t *data, uint16_t length );/* 上报设备信息 (固件/硬件/MAC) */

void mp_heater_ctrl_handle( uint8_t *data, uint16_t length );/* 加热器等级控制 */

void mp_get_heater_ctrl_handle( uint8_t *data, uint16_t length );/* 查询加热器状态 */

void mp_notify_snoring_handle( uint8_t *data, uint16_t length );/* AI通知打鼾→切换止鼾震动 */

void mp_stop_snoring_handle( uint8_t *data, uint16_t length );/* 停止止鼾→恢复自动 */

void mp_set_sip_handle( uint8_t *data, uint16_t length );/* 设置SIP吸气开关 */

void mp_get_sip_handle( uint8_t *data, uint16_t length );/* 查询SIP开关状态 */

void send_version_rsp(void);/* 云端查询控制盒的版本号 */

const m_cmd_entry_t g_m_cmd_entrys[]= 
{
	{ M_CMD_GET_TUNE_MODE, mp_get_tune_mode_handle },    //查询自动调温模式  	
	{ M_CMD_SET_TUNE_MODE, mp_set_tune_mode_handle },    //设置自动调温模式
	{ M_CMD_GET_APR_PCT, mp_get_apr_percent_handle },    //获取目标温度百分比
	{ M_CMD_MENUAL_CFG_APR, mp_manual_cfg_target_apr_handle },//手动配置目标温度
	{ M_CMD_GET_STRENGTH, mp_get_strength_handle },      //获取加热器功率
	{ M_CMD_SET_STRENGTH, mp_set_strength_handle },      //设置加热器功率
	{ M_CMD_DEV_INFO, mp_get_device_info_handle },       //上报设备信息
	{ M_CMD_GET_WIFI_MAC_RSP, mp_get_wifi_mac_handle },  //获取WiFi MAC地址
	{ M_CMD_HEATER_CTRL, mp_heater_ctrl_handle },        //加热器等级控制
	{ M_CMD_GET_HEATER_CTRL, mp_get_heater_ctrl_handle },//查询加热器状态
	{ M_CMD_NOTIFY_SNORING, mp_notify_snoring_handle },  //AI通知打鼾→切换止鼾震动
	{ M_CMD_STOP_SNORING, mp_stop_snoring_handle },      //停止止鼾→恢复自动
	{ M_CMD_SET_SIP, mp_set_sip_handle }, 				 //设置SIP吸气开关
	{ M_CMD_GET_SIP, mp_get_sip_handle },                //查询SIP开关状态
};

m_role_t g_role = M_ROLE_MASTER;// 当前控制盒的角色
static uint8_t wifi_mac[6]={0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};// WiFi MAC地址



void mp_init( void )
{
	m_ota_init();

}


/*
multi frame:
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
a5 a5 a7 6d 00 00 01 00 01 00
00 00 01 00 01 09 3c 00 00 00
5c 0d 56 04 42 02 03 03 59 e0
09 17 b8 01 18 09 1a 7b 09 1a
c8 02 1b 05 02 1b 06 02 1b 07
02 1b 08 02 1b 09 02 1b 0a 02
1b 0b 02 1b 0c 02 1b 0d 02 1b
0e 02 2b 0f e3 03 02 1a ff 01
f9 11 d9 13 81 45 88 c6 01 20
32 c0 5a d0 0c 32 96 8b b0 c5
0c 91 5d 18 02 40 08 08 32 10
00 00 00 9d 5e b5 b5 a6 0d 00
01 00 01 00 00 00 01 00 01 09
3c 5c 58 5e
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/
void mp_rx_downlink_data_handle( uint8_t *data, uint16_t length )//下行数据处理
{
	uint8_t *p;
	uint16_t offset;
	uint16_t len_value;
	

	LOG("rx downlink data:");

	offset = 0;

	while( offset < length )
	{
		p = data + offset;  // 指向当前帧的起始位置
		
		/* 云端查询主板版本号: A5 A5 0xE0 0x01 OBJ FCS (兼容带 0x5E 结尾) */
		if( ((length - offset) >= 6) && (0xA5 == p[0]) && (0xA5 == p[1]) )
		{
			uint8_t cmd_v = p[2];
			uint8_t len_v = p[3];

			if( (M_CMD_VERSION_QUERY == cmd_v) && (0x01 == len_v) )
			{
				uint8_t obj  = p[4];
				uint8_t fcs  = p[5];
				uint8_t calc = (uint8_t)(cmd_v + len_v + obj);

				if( fcs == calc )	/* 校验通过 */
				{
					if( OBJ_MAIN_BOARD == obj )	/* 查询对象是主板 */
					{
						send_version_rsp();	/* 上行返回版本号 */
					}

					offset += 6;		/* 消费整帧 */
					if( (offset < length) && (MJ_EOF == data[offset]) )
					{
						offset++;		/* 兼容 7 字节帧的 0x5E 结尾 */
					}
					continue;// 跳出循环
				}
			}
		}

		if((0xA5 == p[0])&&(0xA5 == p[1]))
		{
			len_value = p[3];

			if( length - offset >= len_value + 6 )// 剩余帧长度大于等于帧长度+6
			{
				if( mp_is_frame_valaid( p, len_value + 6 ) == true )
				{
					g_role = M_ROLE_MASTER;
					m_stop_checking_role();
					mp_process_frame( p, len_value + 6 );

					offset += len_value + 6;
					continue;
				}
			}
		}

		if((0xA5 == p[0])&&(0xA5 == p[1]))
		{
			if( length - offset >= 12 )// 剩余帧长度大于等于帧长度+12
			{
				uint8_t crc_len=0;
				uint8_t fctrl=0;
				
				fctrl = p[3];

				if(fctrl&BIT(7))
				{
					crc_len = 2;
				}
	
				len_value = BUILD_UINT16(p[10], p[11]);

				if(  length - offset  >= len_value + 14+ crc_len )
				{
					if(drv_ai_is_frame_valaid( p,  len_value + 14+ crc_len )==true)
					{
						drv_ai_process_frame( p,  len_value + 14+ crc_len );
						offset +=  len_value + 14+ crc_len;
						continue;
					}
				}
			}
		}
			


		offset++;


		#if 0
		if( mp_is_frame_valaid( data, length ) == true )
		{
			g_role = M_ROLE_MASTER;
			m_stop_checking_role();
			mp_process_frame( data, length );
		}


		 if(drv_ai_is_frame_valaid( data, length )==true)
		{
			drv_ai_process_frame(data, length);
		}
		 #endif
	}
}


uint8_t mp_calc_cs( uint8_t *data, uint16_t length )
{
	uint8_t sum=0;

	for( uint16_t i=0; i<length; i++ )
	{
		sum += data[i];
	}

	return sum;
}


uint8_t mp_is_frame_valaid( uint8_t *data, uint16_t length )
{
	uint16_t sof=0;
	uint8_t fcs=0;

	if( length < MIN_BLE_FRAME_SIZE )
	{
		return false;
	}

	sof = data[1]<<8 | data[0];
	if( DL_SOF != sof )
	{
		return false;
	}

	#if 1
	fcs = mp_calc_cs( data +2, length-4);

	if( fcs != data[length-2])
	{
		return false;
	}
	#endif

	return true;
}
void mp_process_frame( uint8_t *data, uint16_t length )
{
	uint8_t i;
	uint8_t cmd = data[2];
	
	if( ( cmd >= OTA_CMD_MIN ) && ( cmd <= OTA_CMD_MAX ))
	{
		m_ota_process_frame( data, length );
	}
	else
	{
		for( i=0;i<ARRAY_SIZE(g_m_cmd_entrys); i++)
		{
			if((g_m_cmd_entrys[i].cmd == cmd )&&
			    (g_m_cmd_entrys[i].handle))
			{
				g_m_cmd_entrys[i].handle(data, length );

				break;
			}
		}
	}
}


void mp_get_apr_handle( uint8_t *data, uint16_t length )
{

}

void mp_get_tune_mode_handle( uint8_t *data, uint16_t length )
{
	uint8_t value[2];
	
	value[0]= m_get_run_para_instance(PARTION_LEFT)->tune_mode;
	value[1]= m_get_run_para_instance(PARTION_RIGHT)->tune_mode;
	
	mp_build_and_send_frame( M_CMD_GET_TUNE_MODE_RSP, value, 2 );
}

void mp_manual_cfg_target_apr_handle( uint8_t *data, uint16_t length )
{
	uint8_t partion;
	acm_msg_set_apr_seq_t  apr_seq;
	uint8_t *p_apr;
//	uint8_t b_action=false;

	partion = data[4];
	p_apr = data+5;

	if(  ( PARTION_LEFT != partion )&&
	      ( PARTION_RIGHT != partion ))
	{
		return;
	}

	LOG(" partion: %d, \r\napr:",partion);
	for(uint8_t i=0;i<8;i++)
	{
		printf("0x%02x ", p_apr[i]);
	}
	printf("\r\n");

	apr_seq.mask=0;

	if(PARTION_LEFT == partion )
	{
		for(uint8_t i=0;i<MAX_ACL_NUM/2;i++)
		{
			if(p_apr[i]!=0xFF)
			{
				apr_seq.target_apr[i] = p_apr[i]*MAX_APR/100;
				apr_seq.mask |= BIT(i);
			}
		}
	}
	else
	{
		for(uint8_t i=0;i<MAX_ACL_NUM/2;i++)
		{
			if(p_apr[i]!=0xFF)
			{
				apr_seq.target_apr[MAX_ACL_NUM/2+i] = p_apr[i]*MAX_APR/100;
				apr_seq.mask |= BIT(MAX_ACL_NUM/2+i);
			}
		}
	}
	
	{
		acm_msg_set_para_t set_para;

		set_para.item = offset_of( acm_run_para_t, tune_mode);
		set_para.value[0] = TUNE_MODE_MENUAL;
		set_para.len = 1;
		set_para.partion = partion;

		m_acm_set_run_para( &set_para );
	}

	osDelay(1);

	m_acm_set_target_apr_seq( &apr_seq );
		
}

void mp_build_and_send_frame( uint8_t cmd, uint8_t *payload, uint8_t len )
{
	static uint8_t mp_upd_frame[ MAX_BLE_FRAME_SIZE ];
	uint8_t *offset;

	if( len + 6 > sizeof(mp_upd_frame))
	{
		return;
	}
	
	offset = mp_upd_frame;

	*offset++ = 0xB5;
	*offset++ = 0xB5;
	*offset++ = cmd;
	*offset++ = len;
	if( len > 0 )
	{
		for( uint8_t i=0;i<len;i++)
		{	
			*offset++ = payload[i];
		}
	}

	*offset++ = mp_calc_cs( mp_upd_frame+2, 2+len );
	*offset++ = MJ_EOF;

	LOG("tx mp data:");

	HAL_UART_Transmit(&huart3,  mp_upd_frame, offset - mp_upd_frame, pdMS_TO_TICKS(5));
}

//A5 A5 E1 02 02 02 E7 5E
static void mp_set_tune_mode_handle( uint8_t *data, uint16_t length )
{
	uint8_t partion = data[4];
	uint8_t tune_mode = data[5];
//	uint8_t b_action=false;

	if(tune_mode < TUNE_MODE_MAX)
	{
		#if 0
		if(mp_get_role()==M_ROLE_MASTER)
		{
			if(PARTION_LEFT == partion )
			{
				b_action = true;
			}
			else if ( PARTION_RIGHT == partion )
			{
				mp_forward_frame_to_slave_board( data, length );
			}
		}
		else if(mp_get_role()==M_ROLE_SLAVE)
		{
			if(PARTION_RIGHT == partion )
			{
				b_action = true;
			}
		}

		if( true ==b_action )
			#endif
		{
			acm_msg_set_para_t set_para;

			set_para.item = offset_of( acm_run_para_t, tune_mode);
			set_para.value[0] = tune_mode;
			set_para.len = 1;
			set_para.partion = partion;

			m_acm_set_run_para( &set_para );

			//if( ( TUNE_MODE_MENUAL == tune_mode )||
			//     ( TUNE_MODE_AUTO == tune_mode ))
			{
				mp_build_and_send_frame( M_CMD_SET_TUNE_MODE_RSP, data+4, 2 );
			}

			return;
		}
	}
	else
	{
		//	if err:
		 data[5] = 0;

		mp_build_and_send_frame( M_CMD_SET_TUNE_MODE_RSP, data+4, 2 );
	}
}


static void mp_get_apr_percent_handle( uint8_t *data, uint16_t length )
{
//	uint8_t b_action=false;
	uint8_t partion = data[4];

	if(  ( PARTION_LEFT != partion )&&
	      ( PARTION_RIGHT != partion ))
	{
		return;
	}

	{
		uint8_t payload[9];
		uint8_t *apr_pct;

		for(uint8_t i=0;i<sizeof(payload);i++)
		{
			payload[i] = 0xFF;
		}
		
		payload[0] = partion;
		apr_pct = payload+1;

		if(PARTION_LEFT==partion)
		{

			for(uint8_t i=0;i<8;i++)
			{
				apr_pct[i] = (uint8_t)(m_get_acm_instance((acl_id_t)i)->current_apr*100/MAX_APR);
				if(apr_pct[i] >100)
				{
					apr_pct[i] = 100;
				}
			}
		}
		else
		{
			for(uint8_t i=8;i<16;i++)
			{
				apr_pct[i] = (uint8_t)(m_get_acm_instance((acl_id_t)i)->current_apr*100/MAX_APR);
				if(apr_pct[i] >100)
				{
					apr_pct[i] = 100;
				}
			}
		}

		mp_build_and_send_frame( M_CMD_GET_APR_PCT_RSP, payload, ARRAY_SIZE(payload));
	}	
}

void mp_report_apr_percent_handle( uint8_t partion )
{
	uint8_t payload[1+MAX_ACL_NUM/2];
	uint8_t *apr_pct;
		
	if(  ( PARTION_LEFT != partion )&&
	      ( PARTION_RIGHT != partion ))
	{
		return;
	}

   	for(uint8_t i=0;i<sizeof(payload);i++)
	{
		payload[i] = 0xFF;
	}
	
	payload[0] = partion;
	apr_pct = payload+1;
		
	if( PARTION_LEFT == partion )
	{
		for(uint8_t i=0;i<MAX_ACL_NUM/2;i++)
		{
			apr_pct[i] = (uint8_t)(m_get_acm_instance((acl_id_t)i)->current_apr*100/MAX_APR);
		}
	}
	else
	{
		for(uint8_t i=0;i<MAX_ACL_NUM/2;i++)
		{
			apr_pct[i] = (uint8_t)(m_get_acm_instance((acl_id_t)(MAX_ACL_NUM/2+i))->current_apr*100/MAX_APR);
		}
	}

	mp_build_and_send_frame( M_CMD_GET_APR_PCT_RSP, payload, ARRAY_SIZE(payload));
}


void m_report_tunning_state(uint8_t partion)
{

}


void mp_get_strength_handle( uint8_t *data, uint16_t length )
{
	uint8_t payload[2];

	payload[0]= data[4];
		
	if(PARTION_LEFT == data[4])
	{
		payload[1]= m_get_pump_strength(PARTION_LEFT);
		
	}
	else
	{
		payload[1]= m_get_pump_strength(PARTION_RIGHT);
	}
	
	mp_build_and_send_frame( M_CMD_GET_STRENGTH_RSP, payload, 2 );
}

void mp_set_strength_handle( uint8_t *data, uint16_t length )
{
	uint8_t payload[2];
	
	payload[1] = 0;
	
	payload[0]=data[4];
	if((M_STRENGH_SOFT<=data[5])&&
	    (data[5]<=M_STRENGH_STRONG))
	{
		m_set_pump_strength( data[4], data[5] );
	}
	else
	{
		payload[1] = 1;
	}

	mp_build_and_send_frame( M_CMD_SET_STRENGTH_RSP, payload, 2 );

}


void mp_get_wifi_mac_handle( uint8_t *data, uint16_t length )
{
	for(uint8_t i=0;i<6;i++)
	{
		wifi_mac[i] = data[4+i];
	}

	LOG("wifi mac: %02x:%02x:%02x:%02x:%02x:%02x",
		wifi_mac[0], wifi_mac[1], wifi_mac[2], 
		wifi_mac[3], wifi_mac[4], wifi_mac[5] );
}

void mp_get_device_info_handle( uint8_t *data, uint16_t length )
{
	//if(mp_get_role()==M_ROLE_MASTER)
//	{
		uint8_t payload[18];
		uint8_t *p_offset;

		p_offset = payload;

		*p_offset++ = HIGH_BYTE(IMG_TYPE);
		*p_offset++ = LOW_BYTE(IMG_TYPE);

		*p_offset++ = HIGH_BYTE(MF_CODE);
		*p_offset++ = LOW_BYTE(MF_CODE);

		*p_offset++ = BREAK_UINT32(0, 3);
		*p_offset++ = BREAK_UINT32(0, 2);
		*p_offset++ = BREAK_UINT32(HW_VER_VALUE, 1);
		*p_offset++ = BREAK_UINT32(HW_VER_VALUE, 0);
		
		*p_offset++ = BREAK_UINT32(SW_VER_VALUE, 3);
		*p_offset++ = BREAK_UINT32(SW_VER_VALUE, 2);
		*p_offset++ = BREAK_UINT32(SW_VER_VALUE, 1);
		*p_offset++ = BREAK_UINT32(SW_VER_VALUE, 0);

		for(uint8_t i=0;i<6;i++)
		{
			*p_offset++ = wifi_mac[i];
		}

		mp_build_and_send_frame( M_CMD_DEV_INFO_RRSP, payload, sizeof(payload) );
//	}
}


void mp_slave_process_foward_data_handle( uint8_t *data, uint16_t length )
{


}

void mp_heater_ctrl_handle( uint8_t *data, uint16_t length )//加热器控制
{
	uint8_t partion = data[4];//分区
	uint8_t pwm_level = data[5];//PWM等级
	uint8_t tmp_value=25;//目标温度
//	uint8_t b_action=false;

	if(pwm_level < 4)
	{
//		uint8_t dutyfactor=0;

		if(0==pwm_level)
		{
			//dutyfactor = 0;
			tmp_value = 0;
		}
		else if(1==pwm_level)
		{
			//dutyfactor = 50;
			tmp_value = 30;
		}
		else if(2==pwm_level)
		{
			//dutyfactor = 75;
			tmp_value = 40;
		}
		else
		{
			//dutyfactor = 100;
			tmp_value = 50;
		}
		
		if(PARTION_LEFT == partion)
		{
			//drv_heater_ctrl( 0, dutyfactor);
			m_set_target_temperature( PARTION_LEFT,tmp_value );
		}
		else
		{
			//drv_heater_ctrl( 1, dutyfactor);
			m_set_target_temperature( PARTION_RIGHT,tmp_value );
		}
	
		mp_build_and_send_frame( M_CMD_HEATER_CTRL_RRSP, data+4, 2 );

		return;
	}
	else
	{
		//	if err:
		 data[5] = 0;

		mp_build_and_send_frame( M_CMD_HEATER_CTRL_RRSP, data+4, 2 );
	}
}

void mp_get_heater_ctrl_handle( uint8_t *data, uint16_t length )
{
	uint8_t rsp[2];
	ht_item_t *p_ht_item;

	for(uint8_t i=0;i<2;i++)
	{
		p_ht_item = m_get_heater_ctrl_instance(i+1);

		if(0==p_ht_item->dutyfactor)
		{
			rsp[i] = 0;
		}
		else if(50==p_ht_item->dutyfactor)
		{
			rsp[i] = 1;
		}
		else if(75==p_ht_item->dutyfactor)
		{
			rsp[i] = 2;
		}
		else if(100==p_ht_item->dutyfactor)
		{
			rsp[i] = 3;
		}

	}
	mp_build_and_send_frame( M_CMD_GET_HEATER_CTRL_RRSP, rsp, 2 );
	
}

void mp_notify_snoring_handle( uint8_t *data, uint16_t length )
{
	static uint8_t ati_snr_index=0;
	
	uint8_t partion = data[4];

	acm_msg_switch_function_t switch_function;

	switch_function.function = (tune_mode_t)(ati_snr_index+TUNE_MODE_ANTI_SNORING_1);
	switch_function.partion = partion;
	ati_snr_index++;
	if(ati_snr_index>3)
	{
		ati_snr_index = 0;
	}
	LOG("function: %d", switch_function.function);
	m_acm_switch_function(&switch_function );

}

void mp_stop_snoring_handle( uint8_t *data, uint16_t length )
{
	uint8_t partion = data[4];

	acm_msg_switch_function_t switch_function;

	switch_function.function = TUNE_MODE_AUTO;
	switch_function.partion = partion;

	LOG("function: %d", switch_function.function);
	m_acm_switch_function(&switch_function );
	
}

void mp_set_sip_handle( uint8_t *data, uint16_t length )
{
	uint8_t payload[2];
	
	payload[1] = 0;
	
	payload[0]=data[4];
	if((0==data[5])||(1==data[5]))
	{
		m_set_sip_config( data[4], data[5] );
	}
	else
	{
		payload[1] = 1;
	}

	mp_build_and_send_frame( M_CMD_SET_SIP_RSP, payload, 2 );

}


void mp_get_sip_handle( uint8_t *data, uint16_t length )
{
	uint8_t payload[2];

	payload[0]= data[4];
		
	if(PARTION_LEFT == data[4])
	{
		payload[1]= m_get_sip_config(PARTION_LEFT);
		
	}
	else
	{
		payload[1]= m_get_sip_config(PARTION_RIGHT);
	}
	
	mp_build_and_send_frame( M_CMD_GET_SIP_RSP, payload, 2 );
}


//设备上报云端主板版本号
void send_version_rsp(void)
{
       uint8_t frame[15]; 
	     uint8_t *p = frame;

       *p++ = 0xB5;                    // SOF high
       *p++ = 0xB5;                    // SOF low
       *p++ = M_CMD_VERSION_RSP;       // CMD = 0xE1
       *p++ = 0x09;                    // LEN = 9
     
       *p++ = 0x02;                 

       *p++ = MB_FW_VERSION_MAJOR;     // 固件主版本      
       *p++ = MB_FW_VERSION_MINOR;     // 固件次版本
       *p++ = MB_FW_VERSION_PATCH;     // 固件修订号

       *p++ = MB_HW_VERSION_J;         // 硬件主版本
       *p++ = MB_HW_VERSION_N;         // 硬件次版本
       *p++ = MB_HW_VERSION_T;         // 硬件修订号
       *p++ = 0x00;                    // SAVE_1
       *p++ = 0x00;                    // SAVE_2
    
	     *p++ = mp_calc_cs(frame + 2, 2 + 9);  // FCS = CMD~SAVE_2累加和
       *p++ = MJ_EOF;                     // 0x5E

        HAL_UART_Transmit(&huart3, frame, sizeof(frame), 10);

}
