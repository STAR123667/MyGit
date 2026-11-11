#ifndef M_ACM_H
#define M_ACM_H

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"


#define MAX_APR			8.5f
#define MIN_APR			0.5f

#define MAX_ACL_NUM						16
#define ADC_GAP_SEC						0.02f

#define ACM_MSG_QUEUE_SIZE				10
#define TMG_MSG_QUEUE_SIZE				10

#define WINDOW_SIZE						200

#define STD_DEVI_EMPTY_THRESHOLD			0.1f


#define IDLE_AIR_PRESSURE_KPA				5.0f

#define APR_EPSILON							0.2f 
#define LOW_APR_THRESHOLD				1.0f

#define PEAK_THRESHOLD_KPA				0.5f
#define LEAVE_THRESHOLD_KPA				0.5f
#define TRIG_CNT							20

#define AUTO_INFLATE_THRESHOLD			1.0f

#define ADC_POWER_EN_PORT				GPIOD
#define ADC_POWER_EN_PIN					GPIO_PIN_3


#define TUNE_DIR_UP						0
#define TUNE_DIR_DOWN						1

#define ACM_EVENT_INIT_DONE				0x00000001

#define PARTION_LEFT						1
#define PARTION_RIGHT						2
#define PARTION_MAX						3

#define USER_SLEEP_TIMEOUT_MS			(1000*60*20)	
#define USER_LEAVE_BBED_TIMEOUT_MS		(1000*60*60)	

#define VV_DELAY_MS	(200)

#if 1
#define ZHS_RELAX_MODE_TOTAL_SEC				(60*10) //深海潮汐浮浪模式
#define ZHS_RELAX_MODE_INFLATE_SEC				2		//14 per min	
#define ZHS_RELAX_MODE_DEFLATE_SEC				2
  

#define ZHS_PUSH_SPINE_TOTAL_SEC			   	(60*10) //臂腿净排模式
#define ZHS_SPA_MODE_TOTAL_SEC				    (60*10) //云柔全身速舒模式 
#define ZHS_SLEEP_ENHANCE_MODE_TOTAL_SEC		(60*10) //浅澜速眠模式 
#define ZHS_WAKEUP_MODE_TOTAL_SEC			    (60*2) 



#define ZHS_EXPERIENCE_MODE_TOTAL_SEC			(60*10)
#define ZHS_EXPERIENCE_MODE_INFLATE_SEC			4		//14 per min	
#define ZHS_EXPERIENCE_MODE_DEFLATE_SEC			4


#define ZHS_STANDARD_MODE_TOTAL_SEC				(60*15)
#define ZHS_STANDARD_MODE_STEP_2_INFLATE_SEC	3		//18 per min	
#define ZHS_STANDARD_MODE_STEP_2_DEFLATE_SEC	3
#define ZHS_STANDARD_MODE_STEP_2_TOTAL_SEC		(60*5)
#define ZHS_STANDARD_MODE_STEP_3_INFLATE_SEC	4		//14 per min	
#define ZHS_STANDARD_MODE_STEP_3_DEFLATE_SEC	4


#define ZHS_SOFT_MODE_TOTAL_SEC					(60*15)
#define ZHS_SOFT_MODE_STEP_2_INFLATE_SEC			3		//18 per min	
#define ZHS_SOFT_MODE_STEP_2_DEFLATE_SEC			3
#define ZHS_SOFT_MODE_STEP_2_TOTAL_SEC			(60*5)

#define ZHS_SOFT_MODE_STEP_3_INFLATE_SEC			3		//16 per min	
#define ZHS_SOFT_MODE_STEP_3_DEFLATE_SEC			3
#define ZHS_SOFT_MODE_STEP_3_TOTAL_SEC			(60*5)

#define ZHS_SOFT_MODE_STEP_4_INFLATE_SEC			4		//16 per min	
#define ZHS_SOFT_MODE_STEP_4_DEFLATE_SEC			4

#endif



#define ZHS_RPT_TYPE_CURRENT_APR				0
#define ZHS_RPT_TYPE_TARGET_APR					1

#define M_STRENGH_SOFT							0x01
#define M_STRENGH_STAND							0x02
#define M_STRENGH_STRONG					    0x03

#define HIGH_PWR_TIM_CNT	500
#define STAND_PWR_TIM_CNT	5000
#define LOW_PWR_TIM_CNT		5000

typedef enum
{
	MTRS_STATE_EMPTY=0,
	MTRS_STATE_STABLE,
	MTRS_STATE_MOTION,	
}mtrs_state_t;//气囊状态

typedef enum
{
	ACL_ID_01=0,
	ACL_ID_02,
	ACL_ID_03,
	ACL_ID_04,
	ACL_ID_05,
	ACL_ID_06,
	ACL_ID_07,
	ACL_ID_08,
	ACL_ID_09,
	ACL_ID_10,
	ACL_ID_11,
	ACL_ID_12,
	ACL_ID_13,
	ACL_ID_14,
	ACL_ID_15,
	ACL_ID_16,
	ACL_ID_MAX,
	ACL_ID_INVALAID=0xFF
}acl_id_t;//气囊编号

typedef float acl_apr_t[MAX_ACL_NUM];

typedef struct
{
	float left_sole_current;
	float right_sole_current;
	float pump_current;
}acm_current_t;//当前气囊的电流值

typedef enum
{
	ACM_MSG_TYPE_UPDATE_APR=0,
	ACM_MSG_TYPE_SET_TARGET_APR,
	ACM_MSG_TYPE_SET_TARGET_APR_SEQ,
	ACM_MSG_TYPE_DUMP_INFO,
	ACM_MSG_TYPE_UPDATE_CURRENT,
	ACM_MSG_TYPE_STOP_APR_TUNNING,
	ACM_MSG_TYPE_CLEAR_APR,
	ACM_MSG_TYPE_SET_PARA,

	ACM_MSG_TYPE_SECOND_TICK,
	ACM_MSG_TYPE_SWITCH_MODE,
	ACM_MSG_TYPE_AI_CTRL,
}acm_msg_type_t;//消息类型

typedef enum
{
	TUNE_MODE_UNKONOWN=0,    // 未知模式
	TUNE_MODE_MENUAL=1,      // 手动模式
	TUNE_MODE_AUTO,          // 自动模式
	TUNE_MODE_RELAX,         // 放松模式
	TUNE_MODE_PUSH_SPINE,    // 推背模式
	TUNE_MODE_SPA,           // SPA模式
	TUNE_MODE_SLEEP_ENHANCE, // 助眠模式
	//TUNE_MODE_FLOAT, 
	TUNE_MODE_EXPERIENCE,    // 体验模式
	TUNE_MODE_WAKEUP,        // 唤醒模式
	TUNE_MODE_ANTI_SNORING_1,// 止鼾模式1
	TUNE_MODE_ANTI_SNORING_2,// 止鼾模式2
	TUNE_MODE_ANTI_SNORING_3,// 止鼾模式3
	TUNE_MODE_ANTI_SNORING_4,// 止鼾模式4
	//TUNE_MOE_SIP,			 /*Static Injury Prevention Mode*/
	TUNE_MODE_MAX            // 最大模式
}tune_mode_t;//模式类型


typedef struct 
{
	float cap_mv[MAX_ACL_NUM];
}acm_msg_update_apr_t;

typedef struct
{
	uint32_t acl_mask;
	float target_apr; 
}tune_item_t;//调节项

typedef struct 
{
	float target_apr[MAX_ACL_NUM];
	uint32_t mask;
}acm_msg_set_apr_seq_t;//设置气压序列
typedef struct 
{
	float target_apr;
	uint32_t acl_mask;
}acm_msg_set_apr_t;//设置单个气囊的目标气压

typedef struct 
{
	float cur_mv[3];
}acm_msg_update_current_t;//当前气囊的电流值

typedef struct 
{
	uint32_t item;
	uint8_t value[4]; //参数值
	uint8_t len;      //参数长度
	uint8_t partion;  //左床还是右床
}acm_msg_set_para_t;//设置参数

typedef struct 
{
	uint8_t partion;       //左床还是右床
	tune_mode_t function;  //当前对应执行的模式
}acm_msg_switch_function_t;//切换模式

typedef struct 
{
	float target_apr[MAX_ACL_NUM];// 目标气压序列
	uint32_t mask;//调节项
}acm_msg_ai_ctrl_t;//AI控制

typedef union
{
	acm_msg_update_apr_t update_apr;
	acm_msg_set_apr_t	     set_apr;
	acm_msg_update_current_t current;
	acm_msg_set_apr_seq_t set_apr_seq;
	acm_msg_set_para_t set_para;
	acm_msg_switch_function_t switch_function;
	acm_msg_ai_ctrl_t ai_ctrl;
}acm_msg_content_t;//消息体

typedef struct
{
	acm_msg_type_t type;
	acm_msg_content_t content;
}acm_msg_t;//消息结构体

typedef void(*acm_msg_handle_t)(acm_msg_content_t *content);

typedef struct
{
	acm_msg_type_t type;
	acm_msg_handle_t handle;
}acm_msg_handle_entry_t;//消息处理函数表


typedef struct
{
	uint16_t acl_id;   //气囊的编号
	uint8_t b_tuning;  //当前是否在调节状态
	uint8_t b_leaking; //当前是否在漏气状态
	uint8_t b_stable;  //当前气囊是否平稳
	uint8_t tune_dir;  //当前是否在充放气
	float current_apr; //当前的气压值
	float target_apr;  //目标气压
	float avg_apr;     //平均气压
	float avg_apr_stable;//稳定状态后的平均气压
	uint8_t exceed_cnt;  //稳定状态计数
	uint8_t sv_delay_cnt;//电磁阀充气延时计数
}acm_t;//气囊结构体

typedef enum
{
	ACL_ACTION_INFLATE,//充气
	ACL_ACTION_DEFLATE,//放气
}acl_action_t;//气囊动作

typedef struct
{
	tune_mode_t tune_mode;//当前对应执行的模式
}acm_run_para_t;//运行参数


typedef enum
{
	TMG_STATE_ACTIVE=0,
	TMG_STATE_IDLE   
}tmg_state_t;//定时器状态


typedef struct 
{
	uint32_t sec_cnt;
	uint32_t total_sec;
	uint8_t step;
	acl_action_t action;
	uint8_t loop_cnt;
}func_relax_para_t;//放松模式 

typedef struct 
{
	uint32_t sec_cnt;
	uint32_t total_sec;
	uint8_t step;
	acl_action_t action;
}func_experience_para_t;//体验模式

typedef struct 
{
	uint32_t sec_cnt;
	uint32_t total_sec;
	uint8_t step;
	acl_action_t action;
}func_standard_para_t;//标准模式

typedef struct 
{
	uint32_t sec_cnt;
	uint32_t total_sec;
	uint8_t step;
	acl_action_t action;
}func_soft_para_t;//清流模式

typedef struct 
{
	uint32_t sec_cnt;
	uint32_t total_sec;
	uint8_t step;
	acl_action_t action;
}func_sleep_enhance_para_t;//助眠模式

typedef struct 
{
	uint32_t sec_cnt;
	uint32_t total_sec;
	uint8_t step;
	acl_action_t action;
}func_float_para_t;//清流模式


typedef struct 
{
	uint32_t sec_cnt;
	uint32_t total_sec;
	uint8_t step;
	acl_action_t action;
}func_push_spine_para_t;//推背模式

typedef struct 
{
	uint32_t sec_cnt;
	uint32_t total_sec;
	uint8_t step;
	acl_action_t action;
}func_spa_para_t;//SPA模式


typedef struct 
{
	uint32_t sec_cnt;
	uint32_t total_sec;
	uint8_t step;
	uint8_t delay_sec;
	acl_action_t action;
}func_wakeup_para_t;//唤醒模式

typedef struct 
{
	uint32_t sec_cnt;    //总执行时间
	uint32_t total_sec;  //总执行时间
	uint8_t step;        //当前执行的步骤
	uint8_t shake_cnt;   //电磁阀充气延时计数
	acl_action_t action; //当前执行的步骤
}func_anti_snore_1_para_t;//止鼾模式1

typedef struct 
{
	uint32_t sec_cnt;
	uint32_t total_sec;
	uint8_t step;
	uint8_t apr_level[4];
	acl_action_t action;
}func_anti_snore_2_para_t;//止鼾模式2

typedef struct 
{
	uint32_t sec_cnt;
	uint32_t total_sec;
	uint8_t step;
	acl_action_t action;
}func_anti_snore_3_para_t;//止鼾模式3

typedef struct 
{
	uint32_t sec_cnt;
	uint32_t total_sec;
	uint8_t step;
	uint8_t shake_cnt;
	acl_action_t action;
}func_anti_snore_4_para_t;//止鼾模式4



typedef struct
{
	union
	{
		func_relax_para_t 		    relax_para;
		func_spa_para_t			    spa_para;        
		func_sleep_enhance_para_t   sleep_enhance_para;
		func_push_spine_para_t	    push_spine_para;
		func_wakeup_para_t		    wakeup_para;
		func_anti_snore_1_para_t  	anti_snore_1_para;
		func_anti_snore_2_para_t  	anti_snore_2_para;
		func_anti_snore_3_para_t  	anti_snore_3_para;
		func_anti_snore_4_para_t  	anti_snore_4_para;
	}para;
	uint8_t partion;       //左床还是右床
	tune_mode_t function;  //当前对应执行的模式
	uint32_t total_sec_cnt;//模式总的执行时间
	TimerHandle_t timer;   //定时器句柄
}func_mng_t;//模式管理结构体



void m_acm_init( void );

void m_apr_update_notify( float *apr, uint8_t num );

void m_acm_air_pressure_update( acm_msg_update_apr_t * content );

void m_wait_acm_init_done(void);

uint8_t m_is_acm_ready(void);

void m_dump_system_info( void );

void m_acm_stop_apr_tunning( void );

void m_acl_iddle_handler(void);

void m_acm_set_target_apr_seq( acm_msg_set_apr_seq_t * apr_seq );

acm_run_para_t *m_get_run_para_instance(uint8_t partion );

acm_t *m_get_acm_instance( acl_id_t id );

void m_acm_set_target_apr( acm_msg_set_apr_t * set_apr );

void m_acm_set_run_para( acm_msg_set_para_t *set_para );

void m_set_pump_strength( uint8_t partion, uint8_t strength );

uint8_t m_get_pump_strength(  uint8_t partion );
	
void m_acm_ai_ctrl( acm_msg_ai_ctrl_t * content );

uint8_t m_is_ai_action_doing(void);

uint32_t m_get_air_cell_tunning_mask(void);

uint8_t m_calc_apr_level(float apr);

uint8_t m_get_lower_apr_level(uint8_t level);

uint8_t m_get_higher_apr_level(uint8_t level);

void m_static_injury_prevention_tune( uint8_t partion );

void m_acm_switch_function( acm_msg_switch_function_t *content );

void m_set_sip_config( uint8_t partion, uint8_t enable );

uint8_t m_get_sip_config( uint8_t partion );
	
#endif
