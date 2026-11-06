#include "m_acm.h"
#include "cmsis_os.h"
#include "m_log.h"
#include <string.h>
#include <stdio.h>
#include "m_micro.h"
#include "drv_sv.h"
#include "arm_math.h"
#include "ring_buffer.h"
#include "drv_air_pump.h"
#include "m_protocol.h"
#include "main.h"
#include "drv_heater.h"
#include "drv_ai.h"
#include "m_stable.h"
//==============================================================================================================
static void m_acm_thread(void const * argument);//ACM(充气控制模块) 主任务线程
	
static float m_adc_convert_to_kpa(float adc_mv );//adc电压转换为kpa

static void m_acm_refress_comparison(void);//刷新比较结果

static void m_acm_air_pressure_update_handle(acm_msg_content_t *content);//更新气压

static void m_acm_set_target_apr_handle(acm_msg_content_t *content);//设置目标气压

static void m_dump_system_info_handle(acm_msg_content_t *content); //打印系统信息

static BaseType_t m_acm_post_msg( acm_msg_type_t type, acm_msg_content_t *content, uint8_t b_from_isr );//发送消息

static uint8_t m_is_air_cell_tunning(void);//是否正在运行

static void m_tune_tick(void);//调谐定时

static void m_apr_monitor_input_handle( acl_apr_t apr );//apr监控输入

static void m_acl_stable_handler(uint8_t partion );//acl稳定处理

static void m_acm_stop_apr_tunning_handle(acm_msg_content_t *content);//停止apr调谐

static void m_acm_set_target_apr_seq_handle(acm_msg_content_t *content);//设置目标apr序列

static void m_acm_set_run_para_handle(acm_msg_content_t *content);//设置运行参数

static uint8_t m_is_all_air_cell_stable(void);//是否所有充气单元都稳定

void m_vv_delay_timer_callback(TimerHandle_t xTimer);//vv延定时器回调函数

static void m_acm_second_tick_handle(acm_msg_content_t *content);//秒级定时器回调

static void m_work_mode_mng_timer_callback(TimerHandle_t xTimer);//工作模式管理定时器回调     

static uint8_t m_is_mask_acl_all_idle(uint16_t mask);//是否所有acl都空闲

static void m_acm_stop_apr_tunning_direct( void );//直接停止apr调谐

static void m_acm_switch_function_handle(acm_msg_content_t *content);//切换功能

static void m_acm_ai_ctrl_handle(acm_msg_content_t *content);//AI控制处理


//--------------------------------------------------------------------------------------------------------------
static QueueHandle_t g_acm_msg_queue;
static EventGroupHandle_t acm_events=NULL;
static uint8_t b_acm_ready  =false; 

uint8_t tune_pool[sizeof(tune_item_t)*40];
ring_buf_t tune_queue;
uint8_t b_monitor=false;
static float g_apr_pool[MAX_ACL_NUM][sizeof(float)*WINDOW_SIZE+1];
static ring_buf_t g_apr_queue[MAX_ACL_NUM];
static TimerHandle_t m_timer_vv_delay;

static acm_run_para_t g_acm_run_para[2]=
{
	{.tune_mode = TUNE_MODE_AUTO,},
	{.tune_mode = TUNE_MODE_AUTO,},
};

static uint16_t g_sip_sec_cnt[2]={0,0};

static const acm_msg_handle_entry_t g_acm_msg_handle_tbl[]=
{
	{ACM_MSG_TYPE_UPDATE_APR, 		m_acm_air_pressure_update_handle },
	{ACM_MSG_TYPE_SET_TARGET_APR, 	m_acm_set_target_apr_handle },
	{ACM_MSG_TYPE_DUMP_INFO, 		m_dump_system_info_handle },
	//{ACM_MSG_TYPE_UPDATE_CURRENT, 	m_acm_current_update_handle },
	{ACM_MSG_TYPE_STOP_APR_TUNNING, 	m_acm_stop_apr_tunning_handle },
	{ACM_MSG_TYPE_SET_TARGET_APR_SEQ, 	m_acm_set_target_apr_seq_handle },
	{ACM_MSG_TYPE_SET_PARA, 	m_acm_set_run_para_handle },

	{ ACM_MSG_TYPE_SECOND_TICK, m_acm_second_tick_handle },
	{ ACM_MSG_TYPE_SWITCH_MODE, m_acm_switch_function_handle },
	{ ACM_MSG_TYPE_AI_CTRL, m_acm_ai_ctrl_handle },
	
};


acm_t g_acm_table[]=
{
	{
		ACL_ID_01,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0,
		0.0,
		0.0,
		0,
		0,
	},
	
	{
		ACL_ID_02,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0,
		0.0,
		0.0,
		0,
		0,
	},
	
	{
		ACL_ID_03,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0,
 		0.0,
 		0.0,
 		0,
 		0,
	},	

	{
		ACL_ID_04,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0,
		0.0,
		0.0,
		0,
		0,
	},
	
	{
		ACL_ID_05,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0, 
		0.0,
		0.0,
		0,
		0,
	},
	
	{
		ACL_ID_06,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0, 
		0.0,
		0.0,
		0,
		0,
	},	

	{
		ACL_ID_07,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0, 
		0.0,
		0.0,
		0,
		0,
	},	

	{
		ACL_ID_08,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0, 
		0.0,
		0.0,
		0,
		0,
	},	

	{
		ACL_ID_09,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0,
		0.0,
		0.0,
		0,
		0,
	},
	
	{
		ACL_ID_10,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0,
		0.0,
		0.0,
		0,
		0,
	},
	
	{
		ACL_ID_11,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0,
 		0.0,
 		0.0,
 		0,
 		0,
	},	

	{
		ACL_ID_12,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0,
		0.0,
		0.0,
		0,
		0,
	},
	
	{
		ACL_ID_13,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0, 
		0.0,
		0.0,
		0,
		0,
	},
	
	{
		ACL_ID_14,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0, 
		0.0,
		0.0,
		0,
		0,
	},	

	{
		ACL_ID_15,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0, 
		0.0,
		0.0,
		0,
		0,
	},	

	{
		ACL_ID_16,
		false,
		false,
		false,
		TUNE_DIR_UP,
		0.0,
		0.0, 
		0.0,
		0.0,
		0,
		0,
	},			
};

func_mng_t g_function_mng=
{
	.partion = PARTION_MAX,
	.function = TUNE_MODE_AUTO,
};

static uint8_t g_strength[2] = { M_STRENGH_STRONG, M_STRENGH_STRONG };

static uint8_t g_sip_cfg[2]={true, true};

static const float spa_mode_pct[3]=
{
	0.25f,1.0f,0.25f,
};


static const float sleep_enhance_mode_pct[3]=
{
	0.25f,1.0f,0.25f,
};
static tune_mode_t g_experience_mode_index = TUNE_MODE_MAX;

static acm_msg_ai_ctrl_t g_pending_ai_ctrl_seq=
{
	.mask=0,
};

static uint8_t g_force_report_apr = 0;   // 新增：姿态切换时置1，持续上报直到睡姿调节完成清零
//********************************************************************************
void m_acm_init( void )        
{
	ring_buffer_init( &tune_queue, tune_pool, sizeof(tune_pool));

	for( uint8_t i=0;i<MAX_ACL_NUM;i++)
	{
		ring_buffer_init(&g_apr_queue[i], (uint8_t *)g_apr_pool[i], (sizeof(float))*WINDOW_SIZE+1 );
	}
	
	g_acm_msg_queue = xQueueCreate( ACM_MSG_QUEUE_SIZE, sizeof(acm_msg_t));
	if( NULL == g_acm_msg_queue )
	{
		LOG("acm queue init fail");
	}

	if (acm_events == NULL) 
	{
		acm_events = xEventGroupCreate();
	}

	xEventGroupClearBits(acm_events, 0x00ffffff);

	m_timer_vv_delay = xTimerCreate("vvdelay",
								pdMS_TO_TICKS(VV_DELAY_MS),  
								pdFALSE, 
								NULL,
								m_vv_delay_timer_callback);
	xTimerStop( m_timer_vv_delay, pdMS_TO_TICKS(1));

	g_function_mng.timer= xTimerCreate("wk_mode",
								pdMS_TO_TICKS(1000),  
								pdTRUE, 
								NULL,
								m_work_mode_mng_timer_callback);
	xTimerStop( g_function_mng.timer, pdMS_TO_TICKS(1));
	
	
	osThreadDef(m_acm, m_acm_thread, osPriorityNormal, 0, 1024ul*9);
	osThreadCreate(osThread(m_acm), NULL); 
}

void m_acm_thread(void const * argument)
{
	acm_msg_t msg;
	uint16_t i;
	uint16_t cnt;

	cnt = ARRAY_SIZE(g_acm_msg_handle_tbl);

	if (acm_events) 
	{
		xEventGroupSetBits(acm_events, ACM_EVENT_INIT_DONE );
	}

	b_acm_ready = true;

#if 1
	{
		tune_item_t item;

		#if 1

		ring_buffer_clean( &tune_queue );

		for(uint8_t i=0;i<ACL_ID_MAX;i++)	
		{
			if((i!=0)&&(i!=ACL_ID_MAX/2))
			{
				item.acl_mask = BIT(i);
				item.target_apr = 5.0;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
			}
		}
		#endif
		
	}
#endif

	xTimerStart( g_function_mng.timer, pdMS_TO_TICKS(1));

	for(;;) 
	{
		if(pdPASS == xQueueReceive( g_acm_msg_queue,  &msg, portMAX_DELAY))
		{
			for( i=0; i< cnt; i++ )
			{
				if( msg.type == g_acm_msg_handle_tbl[i].type )
				{
					g_acm_msg_handle_tbl[i].handle( &(msg.content) );

					break;
				}
			}
		}
	}
}


BaseType_t m_acm_post_msg( acm_msg_type_t type, acm_msg_content_t *content, uint8_t b_from_isr )
{
	acm_msg_t msg;
	BaseType_t xReturn;

	msg.type = type;

	if(content!=NULL)
	{
		memcpy( (uint8_t *)&(msg.content), ( uint8_t *)content, sizeof(acm_msg_content_t));
	}

	if(true == b_from_isr)
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;

		xQueueSendToBackFromISR( g_acm_msg_queue, &msg, &xHigherPriorityTaskWoken );

		if( xHigherPriorityTaskWoken == pdTRUE )
		{
			portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
		}
	}
	else
	{
		xReturn = xQueueSend( g_acm_msg_queue,  &msg, pdMS_TO_TICKS(20));

		if(xReturn!=pdTRUE)
		{
		}
	}

	return xReturn;
}

float m_adc_convert_to_kpa(float adc_mv )
{
	float kpa;
	
	kpa = (float)((adc_mv-0.2f)*4) ;
	
	return kpa;
}

void m_acm_air_pressure_update( acm_msg_update_apr_t * content )
{
	acm_msg_content_t msg_content;

	memcpy( (uint8_t *)&(msg_content.update_apr), (uint8_t *)content, sizeof(acm_msg_update_apr_t));

	m_acm_post_msg( ACM_MSG_TYPE_UPDATE_APR, &msg_content, true );
}


void m_acm_air_pressure_update_handle(acm_msg_content_t *content)
{
	uint8_t i;
	float *p_cap_volt;
	float cap_pa;
	acl_apr_t apr_array;
	uint8_t b_new_value=false;
		
	p_cap_volt = content->update_apr.cap_mv;
	for(i=0;i<MAX_ACL_NUM;i++)
	{
		cap_pa= m_adc_convert_to_kpa( p_cap_volt[i] );
		
		if(cap_pa>0)
		{
				g_acm_table[i].current_apr = cap_pa;
				b_new_value = true;
		}
	}

	if( true == b_new_value )
	{
		for(i=0;i<MAX_ACL_NUM;i++)
		{
			apr_array[i] = g_acm_table[i].current_apr;
		}
		m_apr_monitor_input_handle(apr_array);
		m_acm_refress_comparison();
	}
}


void m_acm_set_target_apr( acm_msg_set_apr_t * set_apr )
{
	acm_msg_content_t msg_content;

	memcpy( (uint8_t *)&(msg_content.set_apr), (uint8_t *)set_apr, sizeof(acm_msg_set_apr_t));

	 m_acm_post_msg( ACM_MSG_TYPE_SET_TARGET_APR, &msg_content, false );
}

void m_acm_set_target_apr_handle(acm_msg_content_t *content)
{
	uint32_t acl_mask;
	
	acl_mask = content->set_apr.acl_mask;
	if( acl_mask != 0 )
	{
		for(uint32_t i=0;i<MAX_ACL_NUM;i++)
		{
			acm_t *p = &g_acm_table[ i ];

			if(BIT(i)&acl_mask)
			{
				if(DIFF(content->set_apr.target_apr, p->current_apr) > APR_EPSILON )
				{
					p->target_apr = content->set_apr.target_apr;
					p->b_tuning = true;
					p->b_stable = false;
					p->b_leaking = false;
					p->sv_delay_cnt=0;

					ring_buffer_clean(&g_apr_queue[i]);

					if(p->target_apr>p->current_apr)
					{
						p->tune_dir =TUNE_DIR_UP;
					}
					else
					{
						p->tune_dir =TUNE_DIR_DOWN;
					}

					if( i < ACL_ID_MAX/2 )
					{
						if(m_get_run_para_instance(PARTION_LEFT)->tune_mode != TUNE_MODE_MENUAL )
						{
							m_report_tunning_state(PARTION_LEFT);
						}
					}
					else
					{
						if(m_get_run_para_instance(PARTION_RIGHT)->tune_mode != TUNE_MODE_MENUAL )
						{
							m_report_tunning_state(PARTION_RIGHT);
						}
					}
				}
			}
			else
			{
				p->target_apr = content->set_apr.target_apr;
			}
		}
	}	
}
void m_acm_set_target_apr_seq( acm_msg_set_apr_seq_t * apr_seq )
{
	acm_msg_content_t msg_content;

	memcpy( (uint8_t *)&(msg_content.set_apr_seq), (uint8_t *)apr_seq, sizeof(acm_msg_set_apr_seq_t));

	 m_acm_post_msg( ACM_MSG_TYPE_SET_TARGET_APR_SEQ, &msg_content, false );
}

void m_acm_set_target_apr_seq_handle(acm_msg_content_t *content)
{
	m_acm_stop_apr_tunning_direct();
	
	if( content->set_apr_seq.mask != 0 )
	{
		for(uint32_t i=0;i<MAX_ACL_NUM;i++)
		{
			if(content->set_apr_seq.mask & BIT(i))
			{
				acm_t *p = &g_acm_table[i];

				if(content->set_apr_seq.target_apr[i] > MAX_APR)
				{
					LOG("acl [ %d ],error target apr: %f", i, content->set_apr_seq.target_apr[i] );
					
					continue;
				}
				p->target_apr = content->set_apr_seq.target_apr[i];
				p->b_tuning = true;
				p->b_stable = false;
				p->b_leaking = false;
				p->sv_delay_cnt=0;

				LOG("start tune %d acl from %f to %f ", i, p->current_apr, p->target_apr);

				ring_buffer_clean(&g_apr_queue[i]);

				if(p->target_apr>p->current_apr)
				{
					p->tune_dir =TUNE_DIR_UP;
				}
				else
				{
					p->tune_dir =TUNE_DIR_DOWN;
				}
			}
		}
	}	
}

void m_dump_system_info( void )
{
	m_acm_post_msg( ACM_MSG_TYPE_DUMP_INFO, NULL, false );
}

void m_acm_stop_apr_tunning( void )
{
	m_acm_post_msg( ACM_MSG_TYPE_STOP_APR_TUNNING, NULL, false );
}	

void m_dump_system_info_handle(acm_msg_content_t *content)
{
	acm_t *ctrl = g_acm_table;

	for(uint8_t i=0;i<ACL_ID_MAX;i++)
	{
		LOG("acl %d, current apr: %f, target apr: %f", i,
			ctrl[i].current_apr, ctrl[i].target_apr);
	}

}


void m_acm_stop_apr_tunning_handle(acm_msg_content_t *content)
{
	uint8_t i;
	acm_t *p;

	for(i=0;i<MAX_ACL_NUM;i++)	
	{
		p=&g_acm_table[i];

		drv_solenoid_valve_control(i, M_SV_OFF);
		p->b_tuning = false;
	}

	drv_solenoid_valve_control(VV_ID_01, M_SV_OFF);
	drv_solenoid_valve_control(VV_ID_02, M_SV_OFF);
	drv_solenoid_valve_control(VV_ID_03, M_SV_OFF);
	
	drv_air_pump_control(RIGHT_AIR_PUM_PORT, RIGHT_AIR_PUM_PIN, M_PUMP_OFF);
	drv_air_pump_control(LEFT_AIR_PUM_PORT, LEFT_AIR_PUM_PIN, M_PUMP_OFF);
}
void m_acm_refress_comparison(void)
{
	uint8_t i;
	acm_t *p;
	uint32_t pump_mask=0;
	uint16_t vv_mask=0;
	//uint8_t b_tune_down_done=false;
	uint8_t b_sinngle_pump=0;

	static uint16_t rpt_apr_cnt=0;
	 
	for(i=0;i<MAX_ACL_NUM;i++)	
	{
		p=&g_acm_table[i];

		if(p->sv_delay_cnt >0)
		{
			p->sv_delay_cnt --;
			if(0==p->sv_delay_cnt )
			{
				drv_solenoid_valve_control(i, M_SV_OFF);
				LOG("sv[ %d ] turn off", i);
			}
		}

		if(true == p->b_tuning)
		{
			if( TUNE_DIR_UP == p->tune_dir )
			{
				if(( (p->current_apr > p->target_apr )&&(p->current_apr - p->target_apr>APR_EPSILON))||
					(p->current_apr >= MAX_APR))
				{
					drv_solenoid_valve_control(i, M_SV_OFF);
					pump_mask &=~(1<<i);
					vv_mask &=~(1<<i);
					p->b_tuning = false;

					LOG(">>>>>>>>>>>>>>>>>>> inflate %d ac to %f kpa done\r\n", p->acl_id, p->target_apr);

					if( p->acl_id < MAX_ACL_NUM/2 )
					{
						if (m_get_run_para_instance(PARTION_LEFT)->tune_mode != TUNE_MODE_MENUAL )
						{
							m_report_tunning_state(PARTION_LEFT);
						}
						else
						{
							uint8_t status=0;
							
							mp_build_and_send_frame( M_CMD_MENUAL_CFG_APR, &status, 1 );
						}
					}
					else
					{
						if (m_get_run_para_instance(PARTION_RIGHT)->tune_mode != TUNE_MODE_MENUAL )
						{
							m_report_tunning_state(PARTION_RIGHT);
						}
						else
						{
							uint8_t status=0;
							
							mp_build_and_send_frame( M_CMD_MENUAL_CFG_APR, &status, 1 );
						}
					}		
				}
				else
				{
					{
						drv_solenoid_valve_control(i, M_SV_ON);
						
						pump_mask |=(1<<i);
						vv_mask &=~(1<<i);
					}

					if((p->target_apr >p->current_apr)&&(p->target_apr -p->current_apr<=1.0f))
					{
						if(i<MAX_ACL_NUM)
						{
							b_sinngle_pump=1;
						}
						else
						{
							b_sinngle_pump=2;
						}
					}

				}
			}
			else
			{	
				if(((p->current_apr>p->target_apr)&&(p->current_apr-p->target_apr<APR_EPSILON))||
					(p->current_apr<=APR_EPSILON)||
					(p->current_apr<=p->target_apr))
				{
					drv_solenoid_valve_control(i, M_SV_OFF);
					
					pump_mask &=~(1<<i);
					vv_mask &=~(1<<i);
					p->b_tuning = false;

				//	b_tune_down_done = true;

					LOG(">>>>>>>>>>>>>>>>>>> deflate %d ac to %f kpa done\r\n", p->acl_id, p->target_apr);

					if( p->acl_id < MAX_ACL_NUM/2 )
					{
						if (m_get_run_para_instance(PARTION_LEFT)->tune_mode != TUNE_MODE_MENUAL )
						{
							m_report_tunning_state(PARTION_LEFT);
						}
						else
						{
							uint8_t status=0;
							
							mp_build_and_send_frame( M_CMD_MENUAL_CFG_APR, &status, 1 );
						}
					}
					else
					{
						if (m_get_run_para_instance(PARTION_RIGHT)->tune_mode != TUNE_MODE_MENUAL )
						{
							m_report_tunning_state(PARTION_RIGHT);
						}
						else
						{
							uint8_t status=0;
							
							mp_build_and_send_frame( M_CMD_MENUAL_CFG_APR, &status, 1 );
						}
					}
						
				}
				else
				{
					drv_solenoid_valve_control(i, M_SV_ON);
					pump_mask &=~(1<<i);
					vv_mask |=(1<<i);
				}
			}
			printf("id: %d, sv_mask: 0x%08x, current: %f kpa --> target %f kpa\r\n", i, 
							m_get_sv_state_mask(),p->current_apr, p->target_apr);
		}
	}

	if(rpt_apr_cnt>=100)	//  2 second
	{
		uint8_t mode_match=false;
		
		rpt_apr_cnt = 0;

		if( g_force_report_apr||(m_get_air_cell_tunning_mask()&0xFF))
		{
			if(PARTION_LEFT == g_function_mng.partion)		
			{
				if(( TUNE_MODE_RELAX <= g_function_mng.function)&&
				    (g_function_mng.function<TUNE_MODE_MAX)&&
				    (g_function_mng.function != TUNE_MODE_EXPERIENCE))
				{
					mode_match = true;
				}
			}
			
			if( g_force_report_apr||(true == mode_match)||(g_pending_ai_ctrl_seq.mask & 0xFF))
			{
				mp_report_apr_percent_handle(PARTION_LEFT);
			}
		}

		if( g_force_report_apr||(m_get_air_cell_tunning_mask()&0xFF00))
		{
			if(PARTION_RIGHT == g_function_mng.partion)		
			{
				if(( TUNE_MODE_RELAX <= g_function_mng.function)&&
				    (g_function_mng.function<TUNE_MODE_MAX)&&
				    (g_function_mng.function != TUNE_MODE_EXPERIENCE))
				{
					mode_match = true;
				}
			}
			
			if( g_force_report_apr||(true == mode_match)||(g_pending_ai_ctrl_seq.mask & 0xFF00))
			{
				mp_report_apr_percent_handle(PARTION_RIGHT);
			}
		}
				
	}
	else
	{
		rpt_apr_cnt++;
	}
									
	if(0==vv_mask )
	{
		#if 1
		drv_solenoid_valve_control(VV_ID_01, M_SV_OFF);
		drv_solenoid_valve_control(VV_ID_02, M_SV_OFF);
		drv_solenoid_valve_control(VV_ID_03, M_SV_OFF);
		#endif
		
		if(0==pump_mask)
		{
			drv_air_pump_control(RIGHT_AIR_PUM_PORT, RIGHT_AIR_PUM_PIN, M_PUMP_OFF);
			drv_air_pump_control(LEFT_AIR_PUM_PORT, LEFT_AIR_PUM_PIN, M_PUMP_OFF);
		}
		else
		{
			{
				if(pump_mask&0xFF)
				{
					if(M_STRENGH_SOFT == g_strength[0])
					{
						m_set_timer_4_pwm( LOW_PWR_TIM_CNT, LOW_PWR_TIM_CNT );
						
						drv_air_pump_control(LEFT_AIR_PUM_PORT, LEFT_AIR_PUM_PIN, M_PUMP_ON);
						drv_air_pump_control(RIGHT_AIR_PUM_PORT, RIGHT_AIR_PUM_PIN, M_PUMP_OFF);
					}
					else if(M_STRENGH_STAND == g_strength[0])
					{
						m_set_timer_4_pwm(STAND_PWR_TIM_CNT, STAND_PWR_TIM_CNT );
						
						drv_air_pump_control(LEFT_AIR_PUM_PORT, LEFT_AIR_PUM_PIN, M_PUMP_ON);
						drv_air_pump_control(RIGHT_AIR_PUM_PORT, RIGHT_AIR_PUM_PIN, M_PUMP_ON);
					}
					else if(M_STRENGH_STRONG == g_strength[0])
					{
						m_set_timer_4_pwm( HIGH_PWR_TIM_CNT, HIGH_PWR_TIM_CNT );
						
						drv_air_pump_control(LEFT_AIR_PUM_PORT, LEFT_AIR_PUM_PIN, M_PUMP_ON);
						drv_air_pump_control(RIGHT_AIR_PUM_PORT, RIGHT_AIR_PUM_PIN, M_PUMP_ON);
					}
				}

				if(pump_mask&0xFF00)
				{
					if(M_STRENGH_SOFT == g_strength[1])
					{
						m_set_timer_4_pwm( LOW_PWR_TIM_CNT, LOW_PWR_TIM_CNT );
						
						drv_air_pump_control(LEFT_AIR_PUM_PORT, LEFT_AIR_PUM_PIN, M_PUMP_OFF);
						drv_air_pump_control(RIGHT_AIR_PUM_PORT, RIGHT_AIR_PUM_PIN, M_PUMP_ON);
					}
					else if(M_STRENGH_STAND == g_strength[1])
					{
						m_set_timer_4_pwm(STAND_PWR_TIM_CNT, STAND_PWR_TIM_CNT );
						
						drv_air_pump_control(LEFT_AIR_PUM_PORT, LEFT_AIR_PUM_PIN, M_PUMP_ON);
						drv_air_pump_control(RIGHT_AIR_PUM_PORT, RIGHT_AIR_PUM_PIN, M_PUMP_ON);
					}
					else if(M_STRENGH_STRONG == g_strength[1])
					{
						m_set_timer_4_pwm( HIGH_PWR_TIM_CNT, HIGH_PWR_TIM_CNT );
						
						drv_air_pump_control(LEFT_AIR_PUM_PORT, LEFT_AIR_PUM_PIN, M_PUMP_ON);
						drv_air_pump_control(RIGHT_AIR_PUM_PORT, RIGHT_AIR_PUM_PIN, M_PUMP_ON);
					}
				}
			}

			b_sinngle_pump = b_sinngle_pump;
		}
	}
	else
	{
		drv_air_pump_control(RIGHT_AIR_PUM_PORT, RIGHT_AIR_PUM_PIN, M_PUMP_OFF);
		drv_air_pump_control(LEFT_AIR_PUM_PORT, LEFT_AIR_PUM_PIN, M_PUMP_OFF);
		
		drv_solenoid_valve_control(VV_ID_01, M_SV_ON);
		drv_solenoid_valve_control(VV_ID_02, M_SV_ON);
		drv_solenoid_valve_control(VV_ID_03, M_SV_ON);
	}
	
	
	   //所有自适应调节真的完成，清零g_force_report_apr
   if( g_force_report_apr )
	{
		if( (0 == ring_buffer_get_data_len(&tune_queue)) &&     // 队列空
			(0 == g_pending_ai_ctrl_seq.mask) &&               // AI期望值已下发完
			(false == m_is_air_cell_tunning()) &&              // 所有气囊都不在调谐
			(true == m_is_all_air_cell_stable()) )             // 所有气囊都已稳定
		{
			g_force_report_apr = 0;
			LOG("@@@@@ all ai tune done, force_report clear");
		}
	}
	
	m_tune_tick();
}



void m_wait_acm_init_done(void)
{
	 xEventGroupWaitBits(acm_events, ACM_EVENT_INIT_DONE, 1, 0, portMAX_DELAY );

	 xEventGroupClearBits(acm_events, ACM_EVENT_INIT_DONE );
	 
}

uint8_t m_is_acm_ready(void)
{
	return b_acm_ready;
}

uint8_t m_is_air_cell_tunning(void)
{
	uint8_t i;

	for(i=0;i<MAX_ACL_NUM;i++)
	{
		if( true == g_acm_table[i].b_tuning )
		{
			return true;
		}
	}

	return false;
}

uint32_t m_get_air_cell_tunning_mask(void)
{
	uint8_t i;
	uint32_t mask=0;

	for(i=0;i<MAX_ACL_NUM;i++)
	{
		if( true == g_acm_table[i].b_tuning )
		{
			mask |= BIT(i);
		}
	}

	return mask;
}


uint8_t m_is_all_air_cell_stable(void)
{
	uint8_t i;

	for(i=0;i<MAX_ACL_NUM;i++)
	{
		if( false == g_acm_table[i].b_stable)
		{
			return false;
		}
	}

	return true;
}


void m_tune_tick(void)
{
	if(( false == m_is_air_cell_tunning())&&
	    ( true == m_is_all_air_cell_stable()))
	{
		if( ring_buffer_get_data_len( &tune_queue ) >= sizeof( tune_item_t ) )
		{
			tune_item_t item;

			ring_buffer_dequeue( &tune_queue, ( uint8_t *)&item, sizeof( tune_item_t ) );

			if( (item.acl_mask != 0)&&(item.target_apr<=MAX_APR))
			{
				acm_msg_set_apr_t set_apr;

				set_apr.acl_mask =  item.acl_mask;
				set_apr.target_apr = item.target_apr;
				
				m_acm_set_target_apr( &set_apr);
			}

			
			if( 0 ==  ring_buffer_get_data_len( &tune_queue ) )
			{
				if(g_pending_ai_ctrl_seq.mask)
				{
					acm_msg_set_apr_seq_t apr_seq;

					for(uint8_t i=0;i<MAX_ACL_NUM;i++)
					{
						apr_seq.target_apr[i] = g_pending_ai_ctrl_seq.target_apr[i];
					}
					apr_seq.mask = g_pending_ai_ctrl_seq.mask ;
					
					m_acm_set_target_apr_seq( &apr_seq );
					
					g_pending_ai_ctrl_seq.mask = 0;

					LOG("@@@@@ start ai ctrl, mask: %08x", apr_seq.mask );
					for(uint16_t i=0;i<MAX_ACL_NUM;i++)
					{
						if(BIT(i)&apr_seq.mask)
						{
							LOG("acl %d , target apr: %f", i, apr_seq.target_apr[i] );
						}
					}
					
				}
			}
		}
	}
}


void m_apr_monitor_input_handle( acl_apr_t apr )
{
	uint8_t i;
	uint8_t b_tunning = m_is_air_cell_tunning();
	static float apr_cache[WINDOW_SIZE];
	uint8_t b_stable;
	
	uint16_t len;

	b_stable = m_is_all_air_cell_stable();

	for(i=0;i<MAX_ACL_NUM;i++)
	{
		ring_buffer_force_enqueue(&g_apr_queue[i], (uint8_t *)&apr[i], sizeof(float));

		len = ring_buffer_get_free_len(&g_apr_queue[i]);
		if(  len == 0)
		{
			ring_buf_t clone;

			RING_BUF_CLONE( &clone, &g_apr_queue[i] );

			len = ring_buffer_dequeue( &clone, (uint8_t *)apr_cache, sizeof(float)*WINDOW_SIZE);
			if( len == sizeof(float)*WINDOW_SIZE)
			{				
				if( (m_is_stable(apr_cache, WINDOW_SIZE))&&
					(false == g_acm_table[i].b_tuning))
				{	
					if( false == g_acm_table[i].b_stable )
					{
						g_acm_table[i].b_stable = true;
						
						m_acl_stable_handler(i);

						ring_buffer_clean(&g_apr_queue[i]);

						 continue;
					}
				}
			}
		}
	}


	if( (b_stable == false)&&(m_is_all_air_cell_stable() == true ))
	{
		for( uint8_t i=0;i<MAX_ACL_NUM;i++) 
		{
			ring_buffer_clean(&g_apr_queue[i]);
		}
	}
	
}

void m_acl_stable_handler( uint8_t acl_id )
{
}

acm_run_para_t *m_get_run_para_instance(uint8_t partion )
{
	if( ( PARTION_LEFT == partion )||
	     ( PARTION_RIGHT == partion ))
		
	{
		return &g_acm_run_para[partion-1];
	}

	return NULL;
}


void m_acm_set_run_para( acm_msg_set_para_t *set_para )
{
	acm_msg_content_t msg_content;

	memcpy( (uint8_t *)&(msg_content.set_para), (uint8_t *)set_para, sizeof(acm_msg_set_para_t));

	 m_acm_post_msg( ACM_MSG_TYPE_SET_PARA, &msg_content, false );
}

void m_acm_set_run_para_handle(acm_msg_content_t *content)
{
	if(content->set_para.item == offsetof( acm_run_para_t, tune_mode) )
	{
		if(( ( PARTION_LEFT == content->set_para.partion  )||
		      ( PARTION_RIGHT == content->set_para.partion  ))&&
		      (content->set_para.value[0] < TUNE_MODE_MAX))
		{
			acm_run_para_t *run_para = &g_acm_run_para[content->set_para.partion-1];
			acm_msg_switch_function_t switch_function;

			run_para->tune_mode = (tune_mode_t)(content->set_para.value[0]) ;

			switch_function.function = run_para->tune_mode;
			switch_function.partion = content->set_para.partion;

			m_acm_switch_function(&switch_function );
		}

		LOG("set tune mode: partionn: %d, 0x%02x", content->set_para.partion, content->set_para.value[0]);
	}
}

acm_t *m_get_acm_instance( acl_id_t id )
{
	if( id < ACL_ID_MAX )
	{
		return &g_acm_table[id];
	}

	return NULL;
}


void m_vv_delay_timer_callback(TimerHandle_t xTimer) 
{
	drv_solenoid_valve_control(VV_ID_01, M_SV_OFF);
	drv_solenoid_valve_control(VV_ID_02, M_SV_OFF);
	drv_solenoid_valve_control(VV_ID_03, M_SV_OFF);
	xTimerStop( m_timer_vv_delay, pdMS_TO_TICKS(1));
	LOG("timeout stop vv");
}


void m_work_mode_mng_timer_callback(TimerHandle_t xTimer) 
{
	 m_acm_post_msg( ACM_MSG_TYPE_SECOND_TICK, NULL, false );
}


void m_acm_second_tick_handle(acm_msg_content_t *content)
{
	for(uint8_t i=0;i<2;i++)
	{
		if( true == g_sip_cfg[i] )
		{
			g_sip_sec_cnt[i]++;
			if(g_sip_sec_cnt[i]>=1800)
			{			
				g_sip_sec_cnt[i] = 0;

				m_static_injury_prevention_tune(i+1);
			}
		}
	}
		
	g_function_mng.total_sec_cnt++;
	
	switch (g_function_mng.function)
	{
		case TUNE_MODE_ANTI_SNORING_1:
		{
			if( g_function_mng.total_sec_cnt >= g_function_mng.para.anti_snore_1_para.total_sec )
			{		
				g_function_mng.function = TUNE_MODE_AUTO;	
				
				m_reset_posture(g_function_mng.partion);
				LOG("##### mode %d done", g_function_mng.function );
				break;
			
			}


			g_function_mng.para.anti_snore_1_para.sec_cnt++;

			if( 1 == g_function_mng.para.anti_snore_1_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(0);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;

						apr_seq.mask  |= BIT(0);

						apr_seq.target_apr[0] = MAX_APR/4;
					
						LOG("set apr, id: 0 apr: %f, ",  
							apr_seq.target_apr[0]);
		
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.anti_snore_1_para.step = 2;

						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.anti_snore_1_para.step  );
					}
				}
				else 
				{
					mask = BIT(8);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;
						
						apr_seq.mask  |= BIT(8);
						apr_seq.target_apr[8] = MAX_APR/4;
					
						LOG("set apr, id: 8 apr: %f, ",  
							apr_seq.target_apr[8]);
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.anti_snore_1_para.step = 2;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.anti_snore_1_para.step  );
					}
				}
			}
			else if( 2 == g_function_mng.para.anti_snore_1_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(0);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;

						apr_seq.mask  |= BIT(0);

						apr_seq.target_apr[0] = MAX_APR;
					
						LOG("set apr, id: 0 apr: %f, ",  
							apr_seq.target_apr[0]);
		
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.anti_snore_1_para.step = 1;

						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.anti_snore_1_para.step  );
					}
				}
				else 
				{
					mask = BIT(8);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;
						
						apr_seq.mask  |= BIT(8);
						apr_seq.target_apr[8] = MAX_APR;
					
						LOG("set apr, id: 8 apr: %f, ",  
							apr_seq.target_apr[8]);
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.anti_snore_1_para.step = 1;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.anti_snore_1_para.step  );
					}
				}
			}
		}
		break;

		case TUNE_MODE_ANTI_SNORING_2:
		{
			if( g_function_mng.total_sec_cnt >= g_function_mng.para.anti_snore_2_para.total_sec )
			{		
				g_function_mng.function = TUNE_MODE_AUTO;	
				m_reset_posture(g_function_mng.partion);
				LOG("##### mode %d done", g_function_mng.function );
				break;
			
			}

			g_function_mng.para.anti_snore_2_para.sec_cnt++;

			if( 1 == g_function_mng.para.anti_snore_2_para.step )
			{
				uint16_t mask;
				
				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(3)|BIT(4)|BIT(5)|BIT(6);

					if(( true ==m_is_mask_acl_all_idle( mask ))&&
						( 0 == ring_buffer_get_data_len( &tune_queue)))	
					{
						tune_item_t item;
						
						for(uint8_t i=0;i<4;i++)
						{
							item.acl_mask = BIT(3+i);

							if( 25 == g_function_mng.para.anti_snore_2_para.apr_level[i])
							{
								item.target_apr = 35*MAX_APR/100;
							}
							else
							{
								item.target_apr = m_get_lower_apr_level(g_function_mng.para.anti_snore_2_para.apr_level[i])*MAX_APR/100;
							}
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));


							item.target_apr = (g_function_mng.para.anti_snore_2_para.apr_level[i])*MAX_APR/100;
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
						
							LOG("set apr, id: %d, apr: %f, ",  3+i, item.target_apr);
						}
					}
				}
				else 
				{
					mask = BIT(11)|BIT(12)|BIT(13)|BIT(14);

					if(( true ==m_is_mask_acl_all_idle( mask ))&&
						( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						tune_item_t item;
						
						for(uint8_t i=0;i<4;i++)
						{
							item.acl_mask = BIT(11+i);

							if( 25 == g_function_mng.para.anti_snore_2_para.apr_level[i])
							{
								item.target_apr = 35*MAX_APR/100;
							}
							else
							{
								item.target_apr = m_get_lower_apr_level(g_function_mng.para.anti_snore_2_para.apr_level[i])*MAX_APR/100;
							}
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
							
							item.target_apr = (g_function_mng.para.anti_snore_2_para.apr_level[i])*MAX_APR/100;
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
						
							LOG("set apr, id: %d, apr: %f, ",  8+i, item.target_apr);
						}
					}
				}

				g_function_mng.para.anti_snore_2_para.step = 2;
					
				LOG(">>>>> mode: %d, step: %d start", 
					g_function_mng.function, 
					g_function_mng.para.anti_snore_2_para.step  );
			}
			else if( 2 == g_function_mng.para.anti_snore_2_para.step )
			{
				uint16_t mask;
				
				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(3)|BIT(4)|BIT(5)|BIT(6);

					if(( true ==m_is_mask_acl_all_idle( mask ))&&
						( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						tune_item_t item;
						
						for(uint8_t i=0;i<4;i++)
						{
							item.acl_mask = BIT(3+i);
							
							if( 25 == g_function_mng.para.anti_snore_2_para.apr_level[i])
							{
								item.target_apr = 35*MAX_APR/100;
							}
							else
							{
								item.target_apr = m_get_lower_apr_level(g_function_mng.para.anti_snore_2_para.apr_level[i])*MAX_APR/100;
							}
							
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
						
							LOG("set apr, id: %d, apr: %f, ",  3+i, item.target_apr);
						}
					}
				}
				else 
				{
					mask = BIT(11)|BIT(12)|BIT(13)|BIT(14);

					if(( true ==m_is_mask_acl_all_idle( mask ))&&
						( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						tune_item_t item;
						
						for(uint8_t i=0;i<4;i++)
						{
							item.acl_mask = BIT(11+i);
							if( 25 == g_function_mng.para.anti_snore_2_para.apr_level[i])
							{
								item.target_apr = 35*MAX_APR/100;
							}
							else
							{
								item.target_apr = m_get_lower_apr_level(g_function_mng.para.anti_snore_2_para.apr_level[i])*MAX_APR/100;
							}
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
						
							LOG("set apr, id: %d, apr: %f, ",  8+i, item.target_apr);
						}
					}
				}

				g_function_mng.para.anti_snore_2_para.step = 1;
					
				LOG(">>>>> mode: %d, step: %d start", 
					g_function_mng.function, 
					g_function_mng.para.anti_snore_2_para.step  );
			}
		}
		break;

		
		case TUNE_MODE_ANTI_SNORING_3:
		{
			if( g_function_mng.total_sec_cnt >= g_function_mng.para.anti_snore_3_para.total_sec )
			{		
				g_function_mng.function = TUNE_MODE_AUTO;	
				m_reset_posture(g_function_mng.partion);
				LOG("##### mode %d done", g_function_mng.function );
				break;
			
			}

			g_function_mng.para.anti_snore_3_para.sec_cnt++;

			if( 1 == g_function_mng.para.anti_snore_3_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(3)|BIT(4)|BIT(5)|BIT(6);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{

					}
				}
				else 
				{
					mask = BIT(11)|BIT(12)|BIT(13)|BIT(14);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{

					}
				}
			}
		}
		break;	

		case TUNE_MODE_ANTI_SNORING_4:
		{
			if( g_function_mng.total_sec_cnt >= g_function_mng.para.anti_snore_4_para.total_sec )
			{		
				g_function_mng.function = TUNE_MODE_AUTO;	
				
				m_reset_posture(g_function_mng.partion);
				LOG("##### mode %d done", g_function_mng.function );
				break;
			
			}

			g_function_mng.para.anti_snore_4_para.sec_cnt++;

			if( 1 == g_function_mng.para.anti_snore_4_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(2);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;

						apr_seq.mask  |= BIT(2);

						apr_seq.target_apr[2] = MAX_APR/4;
					
						LOG("set apr, id: 2 apr: %f, ",  
							apr_seq.target_apr[2]);
		
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.anti_snore_4_para.step = 2;

						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.anti_snore_4_para.step  );
					}
				}
				else 
				{
					mask = BIT(10);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;
						
						apr_seq.mask  |= BIT(10);
						apr_seq.target_apr[10] = MAX_APR/4;
					
						LOG("set apr, id: 8 apr: %f, ",  
							apr_seq.target_apr[10]);
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.anti_snore_4_para.step = 2;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.anti_snore_4_para.step  );
					}
				}
			}
			else if( 2 == g_function_mng.para.anti_snore_4_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(2);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;

						apr_seq.mask  |= BIT(2);

						apr_seq.target_apr[2] = MAX_APR;
					
						LOG("set apr, id: 0 apr: %f, ",  
							apr_seq.target_apr[2]);
		
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.anti_snore_4_para.step = 1;

						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.anti_snore_4_para.step  );
					}
				}
				else 
				{
					mask = BIT(8);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;
						
						apr_seq.mask  |= BIT(10);
						apr_seq.target_apr[10] = MAX_APR;
					
						LOG("set apr, id: 8 apr: %f, ",  
							apr_seq.target_apr[10]);
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.anti_snore_4_para.step = 1;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.anti_snore_4_para.step  );
					}
				}
			}
		}
		
		break;	

		
		case TUNE_MODE_RELAX:
		{	
			if( g_function_mng.total_sec_cnt >= g_function_mng.para.relax_para.total_sec )
			{				

				{
					acm_msg_set_apr_seq_t  apr_seq;

					if( PARTION_LEFT == g_function_mng.partion )
					{
						for(uint8_t i=1;i<MAX_ACL_NUM/2;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/2;
							apr_seq.mask |= BIT(i);
						}
					}
					else
					{
						for(uint8_t i=MAX_ACL_NUM/2+1;i<MAX_ACL_NUM;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/2;
							apr_seq.mask |= BIT(i);
						}
					}
					m_acm_set_target_apr_seq( &apr_seq );
					g_function_mng.function = TUNE_MODE_AUTO;	
				}

				m_reset_posture(g_function_mng.partion);
				LOG("##### mode %d done", g_function_mng.function );
				break;
			}

			g_function_mng.para.relax_para.sec_cnt++;

			if( 1 == g_function_mng.para.relax_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;

						apr_seq.mask  |= BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);

						for(uint8_t i=1;i<8;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/4;
						
							LOG("set apr, id: i apr: %f, ",  
								apr_seq.target_apr[i]);
						}
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.relax_para.step = 2;

						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}
				else 
				{
					mask = BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;
						
						apr_seq.mask  |= BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);
						for(uint8_t i=9;i<16;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/4;
						
							LOG("set apr, id: i apr: %f, ",  
								apr_seq.target_apr[i]);
						}
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.relax_para.step = 2;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}
			}
			else if( 2 == g_function_mng.para.relax_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;
						
						apr_seq.mask  |= BIT(1);
						apr_seq.target_apr[1] = MAX_APR;
						LOG("set apr, id:1 apr: %f",  apr_seq.target_apr[1] );
						
						m_acm_set_target_apr_seq( &apr_seq );
						g_function_mng.para.relax_para.step = 3;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );	
					}
				}
				else 
				{
					mask = BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;

						apr_seq.mask  |= BIT(9);
						apr_seq.target_apr[9] = MAX_APR;
						LOG("set apr, id: 9 apr: %f",  apr_seq.target_apr[9] );
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.relax_para.step = 3;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );	
					}
				}
				
			}
			else if( 3 == g_function_mng.para.relax_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(1);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;
						
						apr_seq.mask  |= BIT(2);
						apr_seq.target_apr[2] = MAX_APR;
						LOG("set apr, id:2 apr: %f",  apr_seq.target_apr[2] );
						
						m_acm_set_target_apr_seq( &apr_seq );
						g_function_mng.para.relax_para.step = 4;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );	
					}
				}
				else 
				{
					mask = BIT(9);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;

						apr_seq.mask  |= BIT(10);
						apr_seq.target_apr[10] = MAX_APR;
						LOG("set apr, id: 10 apr: %f",  apr_seq.target_apr[10] );
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.relax_para.step = 4;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );	
					}
				}
				
			}
			else if( 4 == g_function_mng.para.relax_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(2);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;

						apr_seq.mask  |=BIT(3)|BIT(4)|BIT(5)|BIT(6);

						for(uint8_t i=3;i<7;i++)
						{
							apr_seq.target_apr[i] = MAX_APR;
						
							LOG("set apr, id: i apr: %f, ",  
								apr_seq.target_apr[i]);
						}
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.relax_para.step = 5;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );				
					}
				}
				else 
				{
					mask = BIT(10);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;
						
						apr_seq.mask  |= BIT(11)|BIT(12)|BIT(13)|BIT(14);
						for(uint8_t i=11;i<15;i++)
						{
							apr_seq.target_apr[i] = MAX_APR;
						
							LOG("set apr, id: i apr: %f, ",  
								apr_seq.target_apr[i]);
						}
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.relax_para.step = 5;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );						
					}
				}

			}
			else if( 5 == g_function_mng.para.relax_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(3)|BIT(4)|BIT(5)|BIT(6);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;

						apr_seq.mask  |= BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);

						for(uint8_t i=1;i<8;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/4;
						
							LOG("set apr, id: i apr: %f, ",  
								apr_seq.target_apr[i]);
						}
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.relax_para.step = 6;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );						
					}
				}
				else 
				{
					mask =BIT(11)|BIT(12)|BIT(13)|BIT(14);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;
						
						apr_seq.mask  |= BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);
						for(uint8_t i=9;i<16;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/4;
						
							LOG("set apr, id: i apr: %f, ",  
								apr_seq.target_apr[i]);
						}
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.relax_para.step = 6;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );							
						
					}
				}
				
			}
			else if( 6 == g_function_mng.para.relax_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						tune_item_t item;

						ring_buffer_clean( &tune_queue );
						
						item.acl_mask = BIT(3);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(4);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(5);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(6);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						g_function_mng.para.relax_para.step=7;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );							
					}
				}
				else
				{
					mask = BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						tune_item_t item;

						ring_buffer_clean( &tune_queue );
						
						item.acl_mask = BIT(11);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(12);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(13);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(14);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						g_function_mng.para.relax_para.step=7;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );							
					}
				}
			}
			else if( 7 == g_function_mng.para.relax_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(3)|BIT(4)|BIT(5)|BIT(6);

					if(( true ==m_is_mask_acl_all_idle( mask ))&&
						( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						tune_item_t item;

						ring_buffer_clean( &tune_queue );
						
						item.acl_mask = BIT(3);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(4);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(5);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(6);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						g_function_mng.para.relax_para.step=8;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );							
					}
				}
				else
				{
					mask =BIT(11)|BIT(12)|BIT(13)|BIT(14);

					if(( true ==m_is_mask_acl_all_idle( mask ))&&
						( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						tune_item_t item;

						ring_buffer_clean( &tune_queue );
						
						item.acl_mask = BIT(11);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(12);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(13);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(14);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						g_function_mng.para.relax_para.step=8;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );							
					}
				}
			}
			else if( 8 == g_function_mng.para.relax_para.step )
			{
				uint16_t mask;
				uint8_t b_done=false;
				
				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(3)|BIT(4)|BIT(5)|BIT(6);

					if(( true ==m_is_mask_acl_all_idle( mask ))&&
						( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						if(TUNE_MODE_RELAX == g_experience_mode_index )
						{
							b_done = true;
						}
						else
						{
							uint16_t mask;


							mask = BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);

							if( true ==m_is_mask_acl_all_idle( mask ))
							{
								acm_msg_set_apr_seq_t  apr_seq;
								apr_seq.mask = 0;
								
								apr_seq.mask  |= BIT(1);
								apr_seq.target_apr[1] = MAX_APR;
								LOG("set apr, id:1 apr: %f",  apr_seq.target_apr[1] );
								
								m_acm_set_target_apr_seq( &apr_seq );
								g_function_mng.para.relax_para.step = 3;
								LOG(">>>>> mode: %d, step: %d start", 
									g_function_mng.function, 
									g_function_mng.para.relax_para.step  );	
							}
						}
					}
				}
				else
				{
					mask = BIT(11)|BIT(12)|BIT(13)|BIT(14);

					if(( true ==m_is_mask_acl_all_idle( mask ))&&
						( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						if(TUNE_MODE_RELAX == g_experience_mode_index )
						{
							b_done = true;
						}
						else
						{
							mask = BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);

							if( true ==m_is_mask_acl_all_idle( mask ))
							{
								acm_msg_set_apr_seq_t  apr_seq;
								apr_seq.mask = 0;

								apr_seq.mask  |= BIT(9);
								apr_seq.target_apr[9] = MAX_APR;
								LOG("set apr, id: 9 apr: %f",  apr_seq.target_apr[9] );
								
								m_acm_set_target_apr_seq( &apr_seq );	
								g_function_mng.para.relax_para.step = 3;
								LOG(">>>>> mode: %d, step: %d start", 
									g_function_mng.function, 
									g_function_mng.para.relax_para.step  );	
							}
						}
					}
				}

				if((TUNE_MODE_RELAX == g_experience_mode_index )&&
					(true==b_done))
				{
					acm_msg_switch_function_t switch_function;
					
					g_experience_mode_index++;

					switch_function.function = g_experience_mode_index;
					switch_function.partion = g_function_mng.partion ;

					LOG("@@@@@ experience, mode: %d start", g_experience_mode_index);
					m_acm_switch_function(&switch_function );
			
				}
								
			}		
		}
		break;

		case TUNE_MODE_SLEEP_ENHANCE:
		{	
			if( g_function_mng.total_sec_cnt >= g_function_mng.para.sleep_enhance_para.total_sec )
			{	
				{
					acm_msg_set_apr_seq_t  apr_seq;

					if( PARTION_LEFT == g_function_mng.partion )
					{
						for(uint8_t i=1;i<MAX_ACL_NUM/2;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/2;
							apr_seq.mask |= BIT(i);
						}
					}
					else
					{
						for(uint8_t i=MAX_ACL_NUM/2+1;i<MAX_ACL_NUM;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/2;
							apr_seq.mask |= BIT(i);
						}
					}
					m_acm_set_target_apr_seq( &apr_seq );
			
					g_function_mng.function = TUNE_MODE_AUTO;
				}

				m_reset_posture(g_function_mng.partion);
				LOG("##### mode %d done", g_function_mng.function );

				break;
			}

			g_function_mng.para.sleep_enhance_para.sec_cnt++;

			if(  1 == g_function_mng.para.sleep_enhance_para.step  )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;

						apr_seq.mask  |= BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);

						for(uint8_t i=1;i<8;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/4;
						
							LOG("set apr, id: i apr: %f, ",  
								apr_seq.target_apr[i]);
						}
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.relax_para.step = 2;

						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}
				else 
				{
					mask = BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;
						
						apr_seq.mask  |= BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);
						for(uint8_t i=9;i<16;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/4;
						
							LOG("set apr, id: i apr: %f, ",  
								apr_seq.target_apr[i]);
						}
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.relax_para.step = 2;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}
			}
			else if(  2 == g_function_mng.para.sleep_enhance_para.step  )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);

					if( (true ==m_is_mask_acl_all_idle( mask ))&&
					     ( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						tune_item_t item;

						ring_buffer_clean( &tune_queue );

						for(uint8_t i=0;i<3;i++)
						{
							item.acl_mask = BIT(2);
							item.target_apr = MAX_APR*sleep_enhance_mode_pct[i];
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
						}

						 g_function_mng.para.sleep_enhance_para.step = 3;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );						 
					}
				}
				else 
				{
					mask = BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);

					if( (true ==m_is_mask_acl_all_idle( mask ))&&
					     ( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						tune_item_t item;

						ring_buffer_clean( &tune_queue );

						for(uint8_t i=0;i<3;i++)
						{
							item.acl_mask = BIT(10);
							item.target_apr = MAX_APR*sleep_enhance_mode_pct[i];
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
						}
						
						g_function_mng.para.sleep_enhance_para.step = 3;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}
			}
			else if( 3 == g_function_mng.para.sleep_enhance_para.step )
			{
				uint16_t mask;
				uint8_t b_done=false;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(2);

					if( (true ==m_is_mask_acl_all_idle( mask ))&&
					     ( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						if(TUNE_MODE_SLEEP_ENHANCE == g_experience_mode_index )
						{
							b_done = true;
						}
						else
						{
							tune_item_t item;

							ring_buffer_clean( &tune_queue );

							for(uint8_t i=0;i<3;i++)
							{
								item.acl_mask = BIT(2);
								item.target_apr = MAX_APR*sleep_enhance_mode_pct[i];
								ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
							}

							 g_function_mng.para.sleep_enhance_para.step = 3;
							LOG(">>>>> mode: %d, step: %d start", 
								g_function_mng.function, 
								g_function_mng.para.relax_para.step  );		
						}
					}
				}
				else 
				{
					mask = BIT(10);

					if( (true ==m_is_mask_acl_all_idle( mask ))&&
					     ( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						if(TUNE_MODE_SLEEP_ENHANCE == g_experience_mode_index )
						{
							b_done = true;
						}
						else
						{
							tune_item_t item;

							ring_buffer_clean( &tune_queue );

							for(uint8_t i=0;i<3;i++)
							{
								item.acl_mask = BIT(10);
								item.target_apr = MAX_APR*sleep_enhance_mode_pct[i];
								ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
							}
							
							g_function_mng.para.sleep_enhance_para.step = 3;
							LOG(">>>>> mode: %d, step: %d start", 
								g_function_mng.function, 
								g_function_mng.para.relax_para.step  );
						}
					}
				}

				if((TUNE_MODE_SLEEP_ENHANCE == g_experience_mode_index )&&
					(true==b_done))
				{
					acm_msg_set_apr_seq_t  apr_seq;
					
					LOG("##### mode %d done", g_function_mng.function );

					g_experience_mode_index = TUNE_MODE_MAX;

					LOG("@@@@@ experience mode done !");

					if( PARTION_LEFT == g_function_mng.partion )
					{
						apr_seq.target_apr[0] = MAX_APR;
						apr_seq.mask |= BIT(0);
							
						for(uint8_t i=1;i<MAX_ACL_NUM/2;i++)
						{
							apr_seq.target_apr[i] = MAX_APR*0.2f;
							apr_seq.mask |= BIT(i);
						}
					}
					else
					{
						apr_seq.target_apr[MAX_ACL_NUM/2] = MAX_APR;
						apr_seq.mask |= BIT(MAX_ACL_NUM/2);
						
						for(uint8_t i=MAX_ACL_NUM/2+1;i<MAX_ACL_NUM;i++)
						{
							apr_seq.target_apr[i] = MAX_APR*0.2f;
							apr_seq.mask |= BIT(i);
						}
					}
					
					m_acm_set_target_apr_seq( &apr_seq );
			
					g_function_mng.function = TUNE_MODE_AUTO;
				}
			}
		}
		break;

		case TUNE_MODE_PUSH_SPINE:
		{					
			if( g_function_mng.total_sec_cnt >= g_function_mng.para.push_spine_para.total_sec )
			{
				{
					acm_msg_set_apr_seq_t  apr_seq;

					if( PARTION_LEFT == g_function_mng.partion )
					{
						for(uint8_t i=1;i<MAX_ACL_NUM/2;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/2;
							apr_seq.mask |= BIT(i);
						}
					}
					else
					{
						for(uint8_t i=MAX_ACL_NUM/2+1;i<MAX_ACL_NUM;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/2;
							apr_seq.mask |= BIT(i);
						}
					}

					m_acm_set_target_apr_seq( &apr_seq );
			
					g_function_mng.function = TUNE_MODE_AUTO;
				}

				m_reset_posture(g_function_mng.partion);
				LOG("##### mode %d done", g_function_mng.function );

				break;
			}

			g_function_mng.para.push_spine_para.sec_cnt++;

			if( 1 == g_function_mng.para.push_spine_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;

						apr_seq.mask  = BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);
						for(uint8_t i=1;i<8;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/4;
						}
						LOG("set apr, id: 1 ~ 7apr: %f",  apr_seq.target_apr[1] );
						
						m_acm_set_target_apr_seq( &apr_seq );	

						g_function_mng.para.push_spine_para.step = 2;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}
				else 
				{
					mask = BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;
						
						apr_seq.mask  =BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);
						for(uint8_t i=9;i<16;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/4;
						}
						LOG("set apr, id: 9~15 apr: %f",  apr_seq.target_apr[9] );
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.push_spine_para.step = 2;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}

				
			}
			else if( 2 == g_function_mng.para.push_spine_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						tune_item_t item;

						ring_buffer_clean( &tune_queue );
						
						item.acl_mask = BIT(3);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(4);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(5);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(6);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						LOG("set apr, id: 3~6 apr: %f",  MAX_APR);

						g_function_mng.para.push_spine_para.step = 3;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );

					}
				}
				else 
				{
					mask = BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						tune_item_t item;
					
						item.acl_mask = BIT(11);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(12);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(13);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(14);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
						
						LOG("set apr, id: 11~14 apr: %f",  MAX_APR);

						g_function_mng.para.push_spine_para.step = 3;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}
			}
			else if( 3 == g_function_mng.para.push_spine_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(3)|BIT(4)|BIT(5)|BIT(6);

					if(( true ==m_is_mask_acl_all_idle( mask ))&&
						( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						tune_item_t item;

						ring_buffer_clean( &tune_queue );
						
						item.acl_mask = BIT(3);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(4);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(5);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(6);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						
						LOG("set apr, id: 3~6 apr: %f",  MAX_APR/4);
							
						g_function_mng.para.push_spine_para.step = 4;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}
				else 
				{
					mask = BIT(11)|BIT(12)|BIT(13)|BIT(14);

					if( (true ==m_is_mask_acl_all_idle( mask ))&&
						( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						tune_item_t item;
				
						item.acl_mask = BIT(11);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(12);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(13);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(14);
						item.target_apr = MAX_APR/4;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
						
						LOG("set apr, id: 11~14 apr: %f",  MAX_APR/4 );
						

						g_function_mng.para.push_spine_para.step = 4;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}

				
			}

			else if( 4 == g_function_mng.para.push_spine_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(3)|BIT(4)|BIT(5)|BIT(6);

					if( (true ==m_is_mask_acl_all_idle( mask ))&&
						( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						
						 apr_seq.mask = 0;

						apr_seq.mask  |= BIT(3)|BIT(6);

						apr_seq.target_apr[3] =MAX_APR;
						apr_seq.target_apr[6] =MAX_APR;
							
						LOG("set apr, id: 3,6 apr: %f, ",  
									apr_seq.target_apr[3]);

						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.push_spine_para.step = 5;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}
				else
				{
					mask = BIT(11)|BIT(12)|BIT(13)|BIT(14);

					if( (true ==m_is_mask_acl_all_idle( mask ))&&
						( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						
						 apr_seq.mask = 0;

						apr_seq.mask  |= BIT(11)|BIT(14);

						apr_seq.target_apr[11] =MAX_APR;
						apr_seq.target_apr[14] =MAX_APR;
							
						LOG("set apr, id: 11,14 apr: %f, ",  
									apr_seq.target_apr[11]);
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.push_spine_para.step = 5;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}
			}
			else if( 5 == g_function_mng.para.push_spine_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(3)|BIT(6);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						
						 apr_seq.mask = 0;

						apr_seq.mask  |= BIT(4)|BIT(5);

						apr_seq.target_apr[4] =MAX_APR;
						apr_seq.target_apr[5] =MAX_APR;
							
						LOG("set apr, id: 4,5 apr: %f, ",  
									apr_seq.target_apr[4]);

						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.push_spine_para.step = 6;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}
				else
				{
					mask = BIT(11)|BIT(14);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						
						 apr_seq.mask = 0;

						apr_seq.mask  |= BIT(12)|BIT(13);

						apr_seq.target_apr[12] =MAX_APR;
						apr_seq.target_apr[13] =MAX_APR;
							
						LOG("set apr, id: 12,13 apr: %f, ",  
									apr_seq.target_apr[12]);

						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.push_spine_para.step = 6;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}
			}
			else if( 6 == g_function_mng.para.push_spine_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(4)|BIT(5);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;

						apr_seq.mask  = BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6);
						for(uint8_t i=2;i<7;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/4;
						}
						LOG("set apr, id: 2 ~ 7apr: %f",  apr_seq.target_apr[2] );
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.push_spine_para.step=7;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}
				else
				{
					mask = BIT(12)|BIT(13);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						apr_seq.mask = 0;

						apr_seq.mask  = BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14);
						for(uint8_t i=10;i<15;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/4;
						}
						LOG("set apr, id: 10 ~ 15apr: %f",  apr_seq.target_apr[10] );
						
						m_acm_set_target_apr_seq( &apr_seq );	
						g_function_mng.para.push_spine_para.step=7;
						LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
					}
				}
			}
			else if( 7 == g_function_mng.para.push_spine_para.step )
			{	
				uint16_t mask;
				uint8_t b_done=false;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						if(TUNE_MODE_PUSH_SPINE == g_experience_mode_index )
						{
							b_done = true;
						}
						else
						{
							tune_item_t item;

							ring_buffer_clean( &tune_queue );
							
							item.acl_mask = BIT(3);
							item.target_apr = MAX_APR;
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

							item.acl_mask = BIT(4);
							item.target_apr = MAX_APR;
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

							item.acl_mask = BIT(5);
							item.target_apr = MAX_APR;
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

							item.acl_mask = BIT(6);
							item.target_apr = MAX_APR;
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

							LOG("set apr, id: 3~6 apr: %f",  MAX_APR);

							g_function_mng.para.push_spine_para.step = 3;
							LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
						}
					}
				}
				else
				{
					mask = BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						if(TUNE_MODE_PUSH_SPINE == g_experience_mode_index )
						{
							b_done = true;
						}
						else
						{
							tune_item_t item;
						
							item.acl_mask = BIT(11);
							item.target_apr = MAX_APR;
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

							item.acl_mask = BIT(12);
							item.target_apr = MAX_APR;
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

							item.acl_mask = BIT(13);
							item.target_apr = MAX_APR;
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

							item.acl_mask = BIT(14);
							item.target_apr = MAX_APR;
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
							
							LOG("set apr, id: 11~14 apr: %f",  MAX_APR);

							g_function_mng.para.push_spine_para.step = 3;
							LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
						}
					}
				}


				if((TUNE_MODE_PUSH_SPINE == g_experience_mode_index )&&
				   (true == b_done))
				{
					acm_msg_switch_function_t switch_function;
					
					g_experience_mode_index++;

					switch_function.function = g_experience_mode_index;
					switch_function.partion = g_function_mng.partion ;

					LOG("@@@@@ experience, mode: %d start", g_experience_mode_index);
					m_acm_switch_function(&switch_function );
			
				}
								
			}
		}
		break;

		case TUNE_MODE_SPA:
		{	
			if( g_function_mng.total_sec_cnt >= g_function_mng.para.spa_para.total_sec )
			{
	
				{
					acm_msg_set_apr_seq_t  apr_seq;

					if( PARTION_LEFT == g_function_mng.partion )
					{
						for(uint8_t i=1;i<MAX_ACL_NUM/2;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/2;
							apr_seq.mask |= BIT(i);
						}
					}
					else
					{
						for(uint8_t i=MAX_ACL_NUM/2+1;i<MAX_ACL_NUM;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/2;
							apr_seq.mask |= BIT(i);
						}
					}
					m_acm_set_target_apr_seq( &apr_seq );
			
					g_function_mng.function = TUNE_MODE_AUTO;
				}	

				m_reset_posture(g_function_mng.partion);
				LOG("##### mode %d done", g_function_mng.function );

				break;
			}

			g_function_mng.para.spa_para.sec_cnt++;

			if(  1 == g_function_mng.para.spa_para.step  )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						
						apr_seq.mask = 0;
						
						apr_seq.mask  |= BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);
						for(uint8_t i=1;i<8;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/4;
						
							LOG("set apr, id: 1~7 apr: %f, ",  
								apr_seq.target_apr[1]);
						}

						m_acm_set_target_apr_seq( &apr_seq );
						g_function_mng.para.spa_para.step =2;
					}
				}
				else 
				{
					mask = BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);

					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						acm_msg_set_apr_seq_t  apr_seq;
						
						apr_seq.mask = 0;
						
						apr_seq.mask  |= BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);
						for(uint8_t i=9;i<16;i++)
						{
							apr_seq.target_apr[i] = MAX_APR/4;
						
							LOG("set apr, id: 9~16 apr: %f, ",  
								apr_seq.target_apr[9]);
						}
						m_acm_set_target_apr_seq( &apr_seq );
						g_function_mng.para.spa_para.step =2;
					}
				}
			}

			if( (2<=g_function_mng.para.spa_para.step )&&
				(g_function_mng.para.spa_para.step <= 8 ))
			{
				uint16_t mask;
				uint8_t step = g_function_mng.para.spa_para.step;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					if(2==g_function_mng.para.spa_para.step)
					{
						mask = BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);
					}
					else
					{
						mask = BIT(step-2);
					}

					if( (true ==m_is_mask_acl_all_idle( mask ))&&
					     ( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						tune_item_t item;

						g_function_mng.para.spa_para.step++;
	
						if(9 ==g_function_mng.para.spa_para.step )
						{
							if(TUNE_MODE_SPA == g_experience_mode_index )
							{
								acm_msg_switch_function_t switch_function;
								
								g_experience_mode_index++;

								switch_function.function = g_experience_mode_index;
								switch_function.partion = g_function_mng.partion ;

								LOG("@@@@@ experience, mode: %d start", g_experience_mode_index);
								m_acm_switch_function(&switch_function );
						
							}
							else		
							{
								g_function_mng.para.spa_para.step = 3;
								LOG(">>>>> mode: %d, step: %d start", 
									g_function_mng.function, 
									g_function_mng.para.relax_para.step  );
							}
						}
						
						step = g_function_mng.para.spa_para.step;
						

						ring_buffer_clean( &tune_queue );

						for(uint8_t i=0;i<3;i++)
						{
							item.acl_mask = BIT(step-2);
							item.target_apr = MAX_APR*spa_mode_pct[i];
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
						}
					}
				}
				else 
				{
					if(1==g_function_mng.para.spa_para.step)
					{
						mask = BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);
					}
					else
					{
						mask = BIT(8+step-2);
					}

					if( (true ==m_is_mask_acl_all_idle( mask ))&&
					     ( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						tune_item_t item;

						g_function_mng.para.spa_para.step++;
						
						if(9 ==g_function_mng.para.spa_para.step )
						{
							if(TUNE_MODE_SPA == g_experience_mode_index )
							{
								acm_msg_switch_function_t switch_function;
								
								g_experience_mode_index++;

								switch_function.function = g_experience_mode_index;
								switch_function.partion = g_function_mng.partion ;

								LOG("@@@@@ experience, mode: %d start", g_experience_mode_index);
								m_acm_switch_function(&switch_function );
						
							}
							else		
							{
								g_function_mng.para.spa_para.step = 3;
								LOG(">>>>> mode: %d, step: %d start", 
									g_function_mng.function, 
									g_function_mng.para.relax_para.step  );
							}
						}
						step = g_function_mng.para.spa_para.step;
						

						ring_buffer_clean( &tune_queue );

						for(uint8_t i=0;i<3;i++)
						{
							item.acl_mask = BIT(8+step-2);
							item.target_apr = MAX_APR*spa_mode_pct[i];
							ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
						}
					}
				}
			}
		}

		break;	

		case TUNE_MODE_WAKEUP:
		{
			if( g_function_mng.total_sec_cnt >= g_function_mng.para.wakeup_para.total_sec )
			{
				acm_msg_set_apr_seq_t  apr_seq;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					for(uint8_t i=1;i<MAX_ACL_NUM/2;i++)
					{
						apr_seq.target_apr[i] = MAX_APR/2;
						apr_seq.mask |= BIT(i);
					}
				}
				else
				{
					for(uint8_t i=MAX_ACL_NUM/2+1;i<MAX_ACL_NUM;i++)
					{
						apr_seq.target_apr[i] = MAX_APR/2;
						apr_seq.mask |= BIT(i);
					}
				}
				m_acm_set_target_apr_seq( &apr_seq );
		
				g_function_mng.function = TUNE_MODE_AUTO;

				m_reset_posture(g_function_mng.partion);
				LOG("##### mode %d done", g_function_mng.function );

				break;
			}

			g_function_mng.para.wakeup_para.sec_cnt++;
			
		 	if( 1 == g_function_mng.para.wakeup_para.step )
			{
				uint16_t mask;

				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(1)|BIT(2)| BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);
					
					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						tune_item_t item;

						ring_buffer_clean( &tune_queue );
						
						item.acl_mask = BIT(2);
						item.target_apr = MAX_APR/2;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(2);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(2);
						item.target_apr = MAX_APR/2;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						g_function_mng.para.wakeup_para.delay_sec = 20;
						g_function_mng.para.wakeup_para.step = 2;
						LOG(">>>>> mode: %d, step: %d start", 
									g_function_mng.function, 
									g_function_mng.para.relax_para.step  );

					}
				}
				else
				{
					mask = BIT(9)|BIT(10)| BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);
					
					if( true ==m_is_mask_acl_all_idle( mask ))
					{
						tune_item_t item;

						ring_buffer_clean( &tune_queue );
						
						item.acl_mask = BIT(10);
						item.target_apr = MAX_APR/2;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(10);
						item.target_apr = MAX_APR;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						item.acl_mask = BIT(10);
						item.target_apr = MAX_APR/2;
						ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

						g_function_mng.para.wakeup_para.delay_sec = 20;
						g_function_mng.para.wakeup_para.step = 2;
						LOG(">>>>> mode: %d, step: %d start", 
									g_function_mng.function, 
									g_function_mng.para.relax_para.step  );

					}
				}
			}
			else if( 2 == g_function_mng.para.wakeup_para.step )
			{
				uint16_t mask;
	
				if( PARTION_LEFT == g_function_mng.partion )
				{
					mask = BIT(2);

					if( (true ==m_is_mask_acl_all_idle( mask ))&&
				            ( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						if(g_function_mng.para.wakeup_para.delay_sec >0)
						{
							g_function_mng.para.wakeup_para.delay_sec--;

							LOG("wakeup mode, delay: %d ", g_function_mng.para.wakeup_para.delay_sec );

							if( 0 == g_function_mng.para.wakeup_para.delay_sec )
							{
								tune_item_t item;

								ring_buffer_clean( &tune_queue );
								
								item.acl_mask = BIT(2);
								item.target_apr = MAX_APR/2;
								ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

								item.acl_mask = BIT(2);
								item.target_apr = MAX_APR;
								ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

								item.acl_mask = BIT(2);
								item.target_apr = MAX_APR/2;
								ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

								g_function_mng.para.wakeup_para.delay_sec = 20;
								g_function_mng.para.wakeup_para.step = 2;
								LOG(">>>>> mode: %d, step: %d start", 
								g_function_mng.function, 
								g_function_mng.para.relax_para.step  );

							}
						}
						
					}
				}
				else
				{
					mask = BIT(10);

					if( (true ==m_is_mask_acl_all_idle( mask ))&&
				            ( 0 == ring_buffer_get_data_len( &tune_queue)))
					{
						if(g_function_mng.para.wakeup_para.delay_sec >0)
						{
							g_function_mng.para.wakeup_para.delay_sec--;

							LOG("wakeup mode, delay: %d ", g_function_mng.para.wakeup_para.delay_sec );

							if( 0 == g_function_mng.para.wakeup_para.delay_sec )
							{
								tune_item_t item;

								ring_buffer_clean( &tune_queue );
								
								item.acl_mask = BIT(10);
								item.target_apr = MAX_APR/2;
								ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

								item.acl_mask = BIT(10);
								item.target_apr = MAX_APR;
								ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

								item.acl_mask = BIT(10);
								item.target_apr = MAX_APR/2;
								ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

								g_function_mng.para.wakeup_para.delay_sec = 20;
								g_function_mng.para.wakeup_para.step = 2;
								LOG(">>>>> mode: %d, step: %d start", 
								g_function_mng.function, 
								g_function_mng.para.relax_para.step  );

							}
						}
					}
				}
			}
		}
		break;	
		
		default:
		break;
		
	}

}


uint8_t m_is_mask_acl_all_idle(uint16_t mask)
{
	
	for(uint32_t i=0;i<MAX_ACL_NUM;i++)
	{
		if( BIT(i) & mask )
		{
			if( true == g_acm_table[i].b_tuning )
			{
				return false;
			}
		}
	}

	return true;
}


void m_acm_switch_function( acm_msg_switch_function_t *content )
{
	acm_msg_content_t msg_content;

	memcpy( (uint8_t *)&(msg_content.switch_function), (uint8_t *)content, sizeof(acm_msg_switch_function_t));

	 m_acm_post_msg( ACM_MSG_TYPE_SWITCH_MODE, &msg_content, false );
}

void m_acm_switch_function_handle(acm_msg_content_t *content)
{
	g_function_mng.function = content->switch_function.function;
	g_function_mng.partion = content->switch_function.partion;
	g_function_mng.total_sec_cnt=0;
	m_acm_stop_apr_tunning_direct();

	ring_buffer_clean( &tune_queue);
	
	if((g_function_mng.function!=TUNE_MODE_AUTO)&&
		(g_function_mng.function!=TUNE_MODE_MENUAL))
	{
		m_set_timer_4_pwm( 2500, 2500 );
	}

	LOG("@@@@@ switch to mode: %d", g_function_mng.function);

	if(TUNE_MODE_MENUAL== g_function_mng.function )
	{
		m_reset_posture(g_function_mng.partion);
	}
	
	if(TUNE_MODE_EXPERIENCE == g_function_mng.function )
	{
		g_function_mng.function = TUNE_MODE_RELAX;
		g_experience_mode_index = TUNE_MODE_RELAX;
	}
	
	if((g_function_mng.function>TUNE_MODE_AUTO)&&(g_function_mng.function<TUNE_MODE_MAX))
	{
		LOG("@@@@@ mode %d start", g_function_mng.function);
	}

	switch (g_function_mng.function)
	{

		case TUNE_MODE_ANTI_SNORING_1:
		{
			acm_msg_set_apr_seq_t  apr_seq;
			
			g_function_mng.para.anti_snore_1_para.total_sec = ZHS_RELAX_MODE_TOTAL_SEC;
			g_function_mng.para.anti_snore_1_para.action = ACL_ACTION_INFLATE,
			g_function_mng.para.anti_snore_1_para.sec_cnt=0;
			g_function_mng.para.anti_snore_1_para.step=1;
			g_function_mng.para.anti_snore_1_para.shake_cnt=0;
			//drv_heater_ctrl( g_function_mng.partion, 75);
			
			LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.anti_snore_1_para.step  );
			apr_seq.mask = 0;
			if( PARTION_LEFT == g_function_mng.partion )
			{
				apr_seq.mask  |= BIT(0);

				apr_seq.target_apr[0] = 7;
			
				LOG("set apr, id: 0apr: %f, ",  
					apr_seq.target_apr[0]);
	
			}
			else
			{
				apr_seq.mask  |= BIT(8);

				apr_seq.target_apr[8] = 7;
			
				LOG("set apr, id: 0apr: %f, ",  
					apr_seq.target_apr[8]);
			}
			
			m_acm_set_target_apr_seq( &apr_seq );	
		}
		break;

		case TUNE_MODE_ANTI_SNORING_2:
		{
			tune_item_t item;
			
			g_function_mng.para.anti_snore_2_para.total_sec = ZHS_RELAX_MODE_TOTAL_SEC;
			g_function_mng.para.anti_snore_2_para.action = ACL_ACTION_INFLATE,
			g_function_mng.para.anti_snore_2_para.sec_cnt=0;
			g_function_mng.para.anti_snore_2_para.step=1;
			
			LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.anti_snore_2_para.step  );
			
			ring_buffer_clean( &tune_queue );

			for(uint8_t i=0;i<4;i++)
			{
				g_function_mng.para.anti_snore_2_para.apr_level[i] = m_calc_apr_level(g_acm_table[i].current_apr);

				if( PARTION_LEFT == g_function_mng.partion )
				{
					item.acl_mask = BIT(3+i);

					if( 25 == g_function_mng.para.anti_snore_2_para.apr_level[i])
					{
						item.target_apr = 35*MAX_APR/100;
					}
					else
					{
						item.target_apr = m_get_lower_apr_level(g_function_mng.para.anti_snore_2_para.apr_level[i])*MAX_APR/100;
					}
					ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

					
					item.target_apr = g_function_mng.para.anti_snore_2_para.apr_level[i]*MAX_APR/100;
					ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

				
					LOG("set apr, id: %d, apr: %f, ",  3+i, item.target_apr);
				}
				else
				{
					item.acl_mask = BIT(11+i);
					if( 25 == g_function_mng.para.anti_snore_2_para.apr_level[i])
					{
						item.target_apr = 35*MAX_APR/100;
					}
					else
					{
						item.target_apr = m_get_lower_apr_level(g_function_mng.para.anti_snore_2_para.apr_level[i])*MAX_APR/100;
					}
					ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

					item.target_apr = g_function_mng.para.anti_snore_2_para.apr_level[i]*MAX_APR/100;
					ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
					
				
					LOG("set apr, id: %d, apr: %f, ",  11+i, item.target_apr);
				}
			}
		}
		break;
		
		case TUNE_MODE_ANTI_SNORING_3:
		{
			acm_msg_set_apr_seq_t  apr_seq;
			
			g_function_mng.para.anti_snore_3_para.total_sec = ZHS_RELAX_MODE_TOTAL_SEC;
			g_function_mng.para.anti_snore_3_para.action = ACL_ACTION_INFLATE,
			g_function_mng.para.anti_snore_3_para.sec_cnt=0;
			g_function_mng.para.anti_snore_3_para.step=1;
			//drv_heater_ctrl( g_function_mng.partion, 75);
			
			LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.anti_snore_3_para.step  );
			
			apr_seq.mask = 0;


			if( PARTION_LEFT == g_function_mng.partion )
			{
				apr_seq.mask  |= BIT(3)|BIT(4)|BIT(5)|BIT(6);
				apr_seq.target_apr[3] = MAX_APR;
				apr_seq.target_apr[4] = MAX_APR;
				apr_seq.target_apr[5] = MIN_APR;
				apr_seq.target_apr[6] = MIN_APR;
	
				LOG("set apr, id: 3,4, apr: %f, id: 5,6, apr: %f, ",  apr_seq.target_apr[3], apr_seq.target_apr[5]);
			}
			else
			{
				apr_seq.mask  |= BIT(11)|BIT(12)|BIT(13)|BIT(14);

				apr_seq.target_apr[11] = MAX_APR;
				apr_seq.target_apr[12] = MAX_APR;
				apr_seq.target_apr[13] = MIN_APR;
				apr_seq.target_apr[14] = MIN_APR;
	
				LOG("set apr, id: 11,12, apr: %f, id: 13,14, apr: %f, ",  apr_seq.target_apr[11], apr_seq.target_apr[13]);
			}
			
			m_acm_set_target_apr_seq( &apr_seq );	
		}
		break;

		case TUNE_MODE_ANTI_SNORING_4:
		{
			acm_msg_set_apr_seq_t  apr_seq;
			
			g_function_mng.para.anti_snore_4_para.total_sec = ZHS_RELAX_MODE_TOTAL_SEC;
			g_function_mng.para.anti_snore_4_para.action = ACL_ACTION_INFLATE,
			g_function_mng.para.anti_snore_4_para.sec_cnt=0;
			g_function_mng.para.anti_snore_4_para.step=1;
			g_function_mng.para.anti_snore_4_para.shake_cnt=0;
			//drv_heater_ctrl( g_function_mng.partion, 75);
			
			LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.anti_snore_4_para.step  );
			apr_seq.mask = 0;
			if( PARTION_LEFT == g_function_mng.partion )
			{
				apr_seq.mask  |= BIT(2);

				apr_seq.target_apr[2] = 7;
			
				LOG("set apr, id: 2, apr: %f, ",  
					apr_seq.target_apr[2]);
	
			}
			else
			{
				apr_seq.mask  |= BIT(10);

				apr_seq.target_apr[10] = 7;
			
				LOG("set apr, id: 10, apr: %f, ",  
					apr_seq.target_apr[10]);
			}
			
			m_acm_set_target_apr_seq( &apr_seq );	
		}
		break;
		
		case TUNE_MODE_RELAX:
		{
			acm_msg_set_apr_seq_t  apr_seq;
			
			g_function_mng.para.relax_para.total_sec = ZHS_RELAX_MODE_TOTAL_SEC;
			g_function_mng.para.relax_para.action = ACL_ACTION_INFLATE,
			g_function_mng.para.relax_para.sec_cnt=0;
			g_function_mng.para.relax_para.step=1;
			g_function_mng.para.relax_para.loop_cnt=0;
			//drv_heater_ctrl( g_function_mng.partion, 75);
			
			LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
			apr_seq.mask = 0;
			if( PARTION_LEFT == g_function_mng.partion )
			{
				apr_seq.mask  |= BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);
				for(uint8_t i=1;i<8;i++)
				{
					apr_seq.target_apr[i] = MAX_APR;
				
					LOG("set apr, id: 1~7 apr: %f, ",  
						apr_seq.target_apr[1]);
				}
			}
			else
			{
				apr_seq.mask  |= BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);
				for(uint8_t i=9;i<16;i++)
				{
					apr_seq.target_apr[i] = MAX_APR;
				
					LOG("set apr, id: 9~16 apr: %f, ",  
						apr_seq.target_apr[9]);
				}
			}
			
			m_acm_set_target_apr_seq( &apr_seq );	
		}
		break;

		case TUNE_MODE_SLEEP_ENHANCE:
		{
			acm_msg_set_apr_seq_t  apr_seq;
			
			g_function_mng.para.sleep_enhance_para.total_sec = ZHS_SLEEP_ENHANCE_MODE_TOTAL_SEC;
			g_function_mng.para.sleep_enhance_para.action = ACL_ACTION_INFLATE,
			g_function_mng.para.sleep_enhance_para.sec_cnt=0;
			g_function_mng.para.sleep_enhance_para.step=1;

			//drv_heater_ctrl( g_function_mng.partion, 75);
			
			LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
			apr_seq.mask = 0;
			
			if( PARTION_LEFT == g_function_mng.partion )
			{
				apr_seq.mask  |= BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);
				for(uint8_t i=1;i<8;i++)
				{
					apr_seq.target_apr[i] = MAX_APR;
				
					LOG("set apr, id: 1~7 apr: %f, ",  
						apr_seq.target_apr[1]);
				}
			}
			else
			{
				apr_seq.mask  |= BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);
				for(uint8_t i=9;i<16;i++)
				{
					apr_seq.target_apr[i] = MAX_APR;
				
					LOG("set apr, id: 9~16 apr: %f, ",  
						apr_seq.target_apr[9]);
				}
			}
			
			m_acm_set_target_apr_seq( &apr_seq );	
		}
		break;

		case TUNE_MODE_SPA:
		{
			acm_msg_set_apr_seq_t  apr_seq;
			
			g_function_mng.para.spa_para.total_sec = ZHS_SPA_MODE_TOTAL_SEC;
			g_function_mng.para.spa_para.action = ACL_ACTION_INFLATE,
			g_function_mng.para.spa_para.sec_cnt=0;
			g_function_mng.para.spa_para.step=1;

			//drv_heater_ctrl( g_function_mng.partion, 50);
			

			LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );
			apr_seq.mask = 0;
			
			if( PARTION_LEFT == g_function_mng.partion )
			{
				apr_seq.mask  |= BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);
				for(uint8_t i=1;i<8;i++)
				{
					apr_seq.target_apr[i] = MAX_APR;
				
					LOG("set apr, id: 1~7 apr: %f, ",  
						apr_seq.target_apr[1]);
				}
			}
			else
			{
				apr_seq.mask  |= BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);
				for(uint8_t i=9;i<16;i++)
				{
					apr_seq.target_apr[i] = MAX_APR;
				
					LOG("set apr, id: 9~16 apr: %f, ",  
						apr_seq.target_apr[9]);
				}
			}
			
			m_acm_set_target_apr_seq( &apr_seq );	
		}
		
		break;


		case TUNE_MODE_PUSH_SPINE:
		{
			acm_msg_set_apr_seq_t  apr_seq;
			
			g_function_mng.para.push_spine_para.total_sec = ZHS_PUSH_SPINE_TOTAL_SEC;
			g_function_mng.para.push_spine_para.action = ACL_ACTION_DEFLATE,
			g_function_mng.para.push_spine_para.sec_cnt=0;
			g_function_mng.para.push_spine_para.step=1;
			//drv_heater_ctrl( g_function_mng.partion, 100);

			LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );

			apr_seq.mask = 0;

			if( PARTION_LEFT == g_function_mng.partion )
			{
				apr_seq.mask  |= BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);
				for(uint8_t i=1;i<8;i++)
				{
					apr_seq.target_apr[i] = MAX_APR;
				
					LOG("set apr, id: 1~7 apr: %f, ",  apr_seq.target_apr[1]);
				}
			}
			else
			{
				apr_seq.mask  |= BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);
				for(uint8_t i=9;i<16;i++)
				{
					apr_seq.target_apr[i] = MAX_APR;
				
					LOG("set apr, id: 9~16 apr: %f, ",  apr_seq.target_apr[9]);
				}
			}
			
			m_acm_set_target_apr_seq( &apr_seq );	
		}
		break;	

		case TUNE_MODE_WAKEUP:
		{
			acm_msg_set_apr_seq_t  apr_seq;
			
			g_function_mng.para.wakeup_para.total_sec = ZHS_WAKEUP_MODE_TOTAL_SEC;
			g_function_mng.para.wakeup_para.action = ACL_ACTION_DEFLATE,
			g_function_mng.para.wakeup_para.sec_cnt=0;
			g_function_mng.para.wakeup_para.step=1;
			g_function_mng.para.wakeup_para.delay_sec=20;

			LOG(">>>>> mode: %d, step: %d start", 
							g_function_mng.function, 
							g_function_mng.para.relax_para.step  );

			apr_seq.mask = 0;
			
			if( PARTION_LEFT == g_function_mng.partion )
			{
				apr_seq.mask  |= BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7);
				for(uint8_t i=1;i<8;i++)
				{
					apr_seq.target_apr[i] = MAX_APR/2;
				
					LOG("set apr, id: 1~7 apr: %f, ",  apr_seq.target_apr[1]);
				}
			}
			else
			{
				apr_seq.mask  |= BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15);
				for(uint8_t i=9;i<16;i++)
				{
					apr_seq.target_apr[i] = MAX_APR/2;
				
					LOG("set apr, id: 9~15 apr: %f, ",  apr_seq.target_apr[9]);
				}
			}
			
			m_acm_set_target_apr_seq( &apr_seq );	
		}
		break;
		
		default:
		break;
		
	}

	//xTimerStart( g_function_mng.timer, pdMS_TO_TICKS(1));
}

void m_acm_stop_apr_tunning_direct( void )
{
	uint8_t i;
	acm_t *p;

	for(i=0;i<MAX_ACL_NUM;i++)	
	{
		p=&g_acm_table[i];

		drv_solenoid_valve_control(i, M_SV_OFF);
		p->b_tuning = false;

		ring_buffer_clean(&g_apr_queue[i]);
	}

	drv_solenoid_valve_control(VV_ID_01, M_SV_OFF);
	drv_solenoid_valve_control(VV_ID_02, M_SV_OFF);
	drv_solenoid_valve_control(VV_ID_03, M_SV_OFF);
	
	drv_air_pump_control(RIGHT_AIR_PUM_PORT, RIGHT_AIR_PUM_PIN, M_PUMP_OFF);
	drv_air_pump_control(LEFT_AIR_PUM_PORT, LEFT_AIR_PUM_PIN, M_PUMP_OFF);
}

void m_set_pump_strength( uint8_t partion, uint8_t strength )
{
	if( PARTION_LEFT == partion )
	{
		g_strength[0] = strength;
	}
	else if( PARTION_RIGHT == partion )
	{
		g_strength[1] = strength;
	}
}

uint8_t m_get_pump_strength(  uint8_t partion )
{
	if( PARTION_LEFT == partion )
	{
		return g_strength[0];
	}
	else if( PARTION_RIGHT == partion )
	{
		return g_strength[1];
	}
	
	return g_strength[0];
}

void m_acm_ai_ctrl( acm_msg_ai_ctrl_t * content )
{
	acm_msg_content_t msg_content;

	memcpy( (uint8_t *)&(msg_content.ai_ctrl), (uint8_t *)content, sizeof(acm_msg_ai_ctrl_t));

	 m_acm_post_msg( ACM_MSG_TYPE_AI_CTRL, &msg_content, false );

}

void m_acm_ai_ctrl_handle(acm_msg_content_t *content)
{
	acm_msg_ai_ctrl_t	*ai_ctrl;
	sensor_status_t *sensor_status;

	ai_ctrl = &(content->ai_ctrl);

	
	if(ai_ctrl->mask)
	{ 
		g_force_report_apr = 1;
		ring_buffer_clean( &tune_queue );

		if( ai_ctrl->mask & 0xFF )		//left 
		{
			tune_item_t item;

			sensor_status = m_get_ai_sensor_status(PARTION_LEFT);

			if( POSTURE_SUPINE == sensor_status->posture)
			{
				item.acl_mask = BIT(0);
				item.target_apr = MAX_APR*0.1f;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
				
				item.acl_mask = BIT(2);
				item.target_apr = MAX_APR;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

				item.acl_mask = BIT(2);
				item.target_apr = MAX_APR*0.15f;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
			}
			else
			{
				item.acl_mask = BIT(1);
				item.target_apr = MAX_APR*0.1f;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

				item.acl_mask = BIT(0);
				item.target_apr = MAX_APR;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
				
				item.acl_mask = BIT(2);
				item.target_apr = MAX_APR;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

				item.acl_mask = BIT(2);
				item.target_apr = MAX_APR*0.15f;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
				
			}

			item.acl_mask = BIT(3)|BIT(4)|BIT(5)|BIT(6);
			item.target_apr = MAX_APR;
			ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

			item.acl_mask = BIT(3)|BIT(4)|BIT(5)|BIT(6);
			item.target_apr = MAX_APR*0.7f;
			ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
		
		}

		if( ai_ctrl->mask & 0xFF00 )		//right 
		{
			tune_item_t item;

			sensor_status = m_get_ai_sensor_status(PARTION_RIGHT);


			if( POSTURE_SUPINE == sensor_status->posture)
			{
				item.acl_mask = (acl_id_t)8;
				item.target_apr = MAX_APR*0.1f;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
				
				item.acl_mask = (acl_id_t)10;
				item.target_apr = MAX_APR;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

				item.acl_mask = (acl_id_t)10;
				item.target_apr = MAX_APR*0.15f;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
			}
			else
			{
				item.acl_mask = (acl_id_t)9;
				item.target_apr = MAX_APR*0.1f;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

				item.acl_mask = (acl_id_t)8;
				item.target_apr = MAX_APR;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
				
				item.acl_mask = (acl_id_t)10;
				item.target_apr = MAX_APR;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

				item.acl_mask = (acl_id_t)10;
				item.target_apr = MAX_APR*0.15f;
				ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
				
			}

			item.acl_mask = BIT(11)|BIT(12)|BIT(13)|BIT(14);
			item.target_apr = MAX_APR;
			ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

			item.acl_mask = BIT(11)|BIT(12)|BIT(13)|BIT(14);
			item.target_apr = MAX_APR*0.7f;
			ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

		}
		
		for(uint8_t i=0;i<MAX_ACL_NUM; i++)
		{
			g_pending_ai_ctrl_seq.target_apr[i] = ai_ctrl->target_apr[i];
		}
		g_pending_ai_ctrl_seq.mask = ai_ctrl->mask;

		LOG("@@@@@ record ai ctrl, mask: %08x",g_pending_ai_ctrl_seq.mask );
		for(uint16_t i=0;i<MAX_ACL_NUM;i++)
		{
			if(BIT(i)&g_pending_ai_ctrl_seq.mask)
			{
				LOG("acl %d , target apr: %f", i, g_pending_ai_ctrl_seq.target_apr[i] );
			}
		}
					
	}
}

uint8_t m_is_ai_action_doing(void)
{
	if(g_pending_ai_ctrl_seq.mask)
	{
		return true;
	}

	return false;
}

uint8_t m_is_tunning_queue_empty(void)
{
	if( 0 == ring_buffer_get_data_len( &tune_queue))
	{
		return true;
	}

	return false;
}

uint8_t m_calc_apr_level(float apr)
{
	uint8_t apr_level[]={100,75,50,35,25};
	uint8_t cmp_level=0;
	uint8_t dif=100;
	uint8_t index=0;

	if(apr>=MAX_APR)
	{
		return 100;
	}

	if(apr<=MIN_APR)
	{
		return 25;
	}
	
	cmp_level = apr*100/MAX_APR;

	for(uint8_t i=0;i<ARRAY_SIZE(apr_level);i++)
	{
		if(DIFF(apr_level[i], cmp_level) < dif)
		{
			index = i;
			dif = DIFF(apr_level[i], cmp_level);
		}
	}

	return apr_level[ index ];
}

uint8_t m_get_lower_apr_level(uint8_t level)
{
		uint8_t i;
	uint8_t apr_level[]={100,75,50,35,25};

	for(i=0;i<ARRAY_SIZE(apr_level);i++)
	{
		if( level == apr_level[i] )
		{
			break;
		}
	}

	if( i == ARRAY_SIZE(apr_level))
	{
		return 25;
	}

	if( i == ARRAY_SIZE(apr_level)-1)
	{
		return apr_level[i-1];
	}
	else
	{
		return apr_level[i+1];
	}
}

uint8_t m_get_higher_apr_level(uint8_t level)
{
		uint8_t i;
	uint8_t apr_level[]={100,75,50,35,25};

	for(i=0;i<ARRAY_SIZE(apr_level);i++)
	{
		if( level == apr_level[i] )
		{
			break;
		}
	}

	if( i == ARRAY_SIZE(apr_level))
	{
		return 100;
	}

	if( i == 0)
	{
		return apr_level[i];
	}
	else
	{
		return apr_level[i-1];
	}
}



void m_static_injury_prevention_tune( uint8_t partion )
{
	uint8_t base_id=0;
	tune_item_t item;
	uint8_t apr_level=25;

	if(PARTION_LEFT == partion)
	{
		base_id=0;
	}
	else if(PARTION_RIGHT == partion)
	{
		base_id=8;
	}
	else
	{
		return;
	}

	ring_buffer_clean( &tune_queue );


	item.acl_mask = BIT(base_id+1);
	apr_level = m_calc_apr_level(g_acm_table[base_id+1].current_apr);
	if( 25 == apr_level )
	{
		item.target_apr = 35*MAX_APR/100;
		ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

		item.target_apr =25*MAX_APR/100;
		ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
	}
	else
	{
		item.target_apr = m_get_lower_apr_level( apr_level )*MAX_APR/100;
		ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

		item.target_apr =apr_level*MAX_APR/100;
		ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
	}


	item.acl_mask = BIT(base_id+2);
	apr_level = m_calc_apr_level(g_acm_table[base_id+2].current_apr);
	if( 25 == apr_level )
	{
		item.target_apr = 35*MAX_APR/100;
		ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

		item.target_apr =25*MAX_APR/100;
		ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
	}
	else
	{
		item.target_apr = m_get_lower_apr_level( apr_level )*MAX_APR/100;
		ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

		item.target_apr =apr_level*MAX_APR/100;
		ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
	}

	item.acl_mask = BIT(base_id+3) | BIT(base_id+4)| BIT(base_id+5)| BIT(base_id+6);
	apr_level = m_calc_apr_level(g_acm_table[base_id+3].current_apr);
	if( 25 == apr_level )
	{
		item.target_apr = 35*MAX_APR/100;
		ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

		item.target_apr =25*MAX_APR/100;
		ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
	}
	else
	{
		item.target_apr = m_get_lower_apr_level( apr_level )*MAX_APR/100;
		ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));

		item.target_apr =apr_level*MAX_APR/100;
		ring_buffer_enqueue( &tune_queue, (uint8_t *)&item, sizeof(tune_item_t));
	}


	
}


void m_set_sip_config( uint8_t partion, uint8_t enable )
{
	if( PARTION_LEFT == partion )
	{
		g_sip_cfg[0] = enable;
		g_sip_sec_cnt[0] = 0;
	}
	else if( PARTION_RIGHT == partion )
	{
		g_sip_cfg[1] = enable;
		g_sip_sec_cnt[1]=0;
	}
}

uint8_t m_get_sip_config( uint8_t partion )
{
	if( PARTION_LEFT == partion )
	{
		return g_sip_cfg[0];
	}
	else if( PARTION_RIGHT == partion )
	{
		return g_sip_cfg[1];
	}
	
	return g_sip_cfg[0];
}

