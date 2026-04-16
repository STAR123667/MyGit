
#include "stm32f10x.h"
#include <stdlib.h>
#include "MyProject.h"


//---------------------------------------------------
//创建日期：2025-2-10
//作    者：Merk Mao
//电机FOC驱动
//电流采样 
//---------------------------------------------------


/******************************************************************************/
#define LED_blink    GPIOC->ODR^=(1<<13)
/******************************************************************************/
void commander_run(void);
/******************************************************************************/
long timecntr_pre=0;
long time_cntr=0;
float target;
/******************************************************************************/
//us计时，每71.5分钟溢出循环一次
uint32_t timecount(void)
{
	uint32_t  diff,now_us;
	
	now_us = _micros();    //0xFFFFFFFF=4294967295 us=71.5分钟
	if(now_us>=timecntr_pre)diff = now_us - timecntr_pre;   //us
	else
		diff = 0xFFFFFFFF - timecntr_pre + now_us;
	timecntr_pre = now_us;
	
	return diff;
}
/******************************************************************************/
void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);//使能GPIOA,GPIOB,GPIOC,AFIO;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;         //PC13是LED
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  //速度
	GPIO_Init(GPIOC, &GPIO_InitStructure);             //对选中管脚初始化
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);                 //上电点亮LED
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;          //PB9是motor1的使能
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);                  //低电平解除,Motor_init()中使能
}
/******************************************************************************/
int main(void)
{
	float  ICMU_Angle;
	GPIO_Config();
	uart_init(115200);
	TIM2_PWM_Init();
	systick_CountInit();       //systick时钟开启1ms中断模式
	
	delay_ms(1000);            //Wait for the system to stabilize
	MagneticSensor_Init();     //初始化编码器参数 和 I2C或者SPI
	//SPI2_Init_ICMU();
	InlineCurrentSense(0.001,1000,ADC_Channel_3,ADC_Channel_4,ADC_Channel_5);    //SimpleMotor//采样电阻阻值，运放倍数，A相，B相，C相
	//InlineCurrentSense(0.001,50,ADC_Channel_3,ADC_Channel_4,NOT_SET);    //SimpleMotor//采样电阻阻值，运放倍数，A相，B相，C相
	InlineCurrentSense_Init(); //ADC初始化和偏置电压校准
	LPF_init();                //LPF参数初始化
	PID_init();                //PID参数初始化
   
/*
	
	//mt6835,ysj空心杯电机，1对极，ASZ,16384,40rad/s
	voltage_power_supply=12;   //12V 电源电压
	pole_pairs=1;             //10电机极对数，按照实际设置
	voltage_sensor_align=0.8;  //0.8V 霍尔电机
	voltage_limit=6;           //6V
	velocity_limit=40;         //10，20,[31.4-4000]rad/s 角度模式时限制最大转速，力矩模式和速度模式不起作用
	//2505电机，50.24,4V
	current_limit=50;          //50A，foc_current和dc_current模式限制电流，不能为0。速度模式和位置模式起作用
	torque_controller=Type_foc_current;  //Type_dc_current;//  Type_foc_current;  //Type_voltage;
	//controller=Type_velocity;  //Type_torque;  //Type_velocity;  //Type_angle; 
	controller=Type_angle;
	PID_current_d.P=0.2;       //0.6电流环PI参数，可以进入 PID_init() 函数中修改其它参数
	PID_current_d.I=0;         //0电流环I参数不太好调试，设置为0只用P参数也可以
	PID_current_q.P=0.2;       //0.6
	PID_current_q.I=0;         //0
	PID_velocity.P=0.1;        //0.1, 速度环PI参数，只用P参数方便快速调试
	PID_velocity.I=1;          //1 
	P_angle.P=8;              //20 位置环参数，只需P参数
	PID_velocity.output_ramp=60; //30,50 速度爬升斜率，如果不需要可以设置为0
	LPF_velocity.Tf=0.01;        //0.02
	target=0;                    //0	
	*/
	
	//mt6835,xd空心杯电机，1对极，ASZ,16384,60rad/s
	voltage_power_supply=12;   //12V 电源电压
	pole_pairs=1;             //10电机极对数，按照实际设置
	voltage_sensor_align=0.8;  //0.8V 霍尔电机
	voltage_limit=6;           //6V
	velocity_limit=60;         //30,10，20,[31.4-4000]rad/s 角度模式时限制最大转速，力矩模式和速度模式不起作用
	//2505电机，50.24,4V
	current_limit=50;          //50A，foc_current和dc_current模式限制电流，不能为0。速度模式和位置模式起作用
	torque_controller=Type_foc_current;  //Type_dc_current;//  Type_foc_current;  //Type_voltage;
	//controller=Type_velocity;  //Type_torque;  //Type_velocity;  //Type_angle; 
	controller=Type_angle;
	PID_current_d.P=0.20;       //0.6电流环PI参数，可以进入 PID_init() 函数中修改其它参数
	PID_current_d.I=0;         //0电流环I参数不太好调试，设置为0只用P参数也可以
	PID_current_q.P=0.20;       //0.6
	PID_current_q.I=0;         //0
	PID_velocity.P=0.1;        //0.1, 速度环PI参数，只用P参数方便快速调试
	PID_velocity.I=1;          //1 
	P_angle.P=8;              //20 位置环参数，只需P参数
	PID_velocity.output_ramp=80; //70,30,50 速度爬升斜率，如果不需要可以设置为0
	LPF_velocity.Tf=0.01;        //0.02
	target=0;                    //0		
	


	

  
  //====================================	
	/*
  //AS560, 7pairs, iic, 5004黑电机
	voltage_power_supply=12;   //V 电源电压
	pole_pairs=7;              //电机极对数，按照实际设置，虽然可以上电检测但有失败的概率
	voltage_sensor_align=2;    //V alignSensor() use it，航模电机设置的值小一点比如0.5-1，云台电机设置的大一点比如2-3
	voltage_limit=6;           //V，主要为限制电机最大电流，最大值需小于12/1.732=6.9
	velocity_limit=50;         //rad/s 角度模式时限制最大转速，力矩模式和速度模式不起作用
	current_limit=50;          //A，foc_current和dc_current模式限制电流，不能为0。速度模式和位置模式起作用
	//torque_controller=Type_foc_current;  //Type_dc_current;//  Type_foc_current;  //Type_voltage;
	torque_controller=Type_foc_current;  //Type_dc_current;//  Type_foc_current;  //Type_voltage;
	//controller=Type_velocity;  //Type_torque;  //Type_velocity;  //Type_angle; 
	controller=Type_angle; 
	PID_current_d.P=0.6;       //电流环PI参数，可以进入 PID_init() 函数中修改其它参数
	PID_current_d.I=0;         //电流环I参数不太好调试，设置为0只用P参数也可以
	PID_current_q.P=0.6;
	PID_current_q.I=0;
	PID_velocity.P=0.1;        //0.1, 速度环PI参数，只用P参数方便快速调试
	PID_velocity.I=1;
	P_angle.P=5;               //位置环参数，只需P参数
	PID_velocity.output_ramp=50; //速度爬升斜率，如果不需要可以设置为0
	LPF_velocity.Tf=0.01;
	target=0;
	*/
  //===================================

	
	Motor_init();
	Motor_initFOC(0,UNKNOWN);  //(2.2,CW);(0,UNKNOWN);  //如果填入零点偏移角度和方向，将跳过上电检测。电机极对数要设置正确。 
	//Motor_initFOC(0,CW);  //(2.2,CW);(0,UNKNOWN);  //如果填入零点偏移角度和方向，将跳过上电检测。电机极对数要设置正确。 
  printf("Motor ready.\r\n");
	
	while(1)
	{
		

		time_cntr +=timecount();
		if(time_cntr>=500000)  //us
		{
			time_cntr=0;
			LED_blink;
			printf("Ang=%.2f   ,Vel=%.2f   \r\n",shaft_angle,shaft_velocity);
			
			//printf("ABZ_angle=%.2f   ,ABZ_Vel=%.2f\r\n",getAngle_ABZ(),getVelocity_ABZ());
			
		  //printf("ia:%.4f,ib:%.4f,ic:%.4f.\r\n",_readADCVoltageInline(3),_readADCVoltageInline(4),_readADCVoltageInline(5));
		  //ICMU_Angle= _2PI*ReadAngle_ICMU()/524288;  //17bit
		  //printf("iCMU_Ang=%.2f\r\n",ICMU_Angle);
		}
		move(target);
		loopFOC();
		commander_run();
		
	}
}
/******************************************************************************/
//通信协议与上位机对接
void commander_run(void)
{
	if((USART_RX_STA&0x8000)!=0)
	{
		switch(USART_RX_BUF[0])
		{
			case 'H':
				printf("Hello World!\r\n");
				break;
			case 'T':   //T6.28
				target=atof((const char *)(USART_RX_BUF+1));
				printf("T=%.4f\r\n", target);
				break;
			case 'V':   //V  读实时速度
				printf("Vel=%.2f\r\n",shaft_velocity);
				break;
			case 'A':   //A  读绝对角度
				printf("Ang=%.2f\r\n",shaft_angle);
				break;
			case 'P':   //P,设置速度模式的P参数,例如设置P=0.8，发送指令P0.8
				PID_velocity.P=atof((const char *)(USART_RX_BUF+1));
				printf("P=%.4f\r\n",PID_velocity.P);
				break;
			case 'I':   //I,设置速度模式的I参数,例如设置I=0.8，发送指令I0.8
				PID_velocity.I=atof((const char *)(USART_RX_BUF+1));
				printf("I=%.4f\r\n",PID_velocity.I);
				break;
		}
		USART_RX_STA=0;
	}
}
/******************************************************************************/



