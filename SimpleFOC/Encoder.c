
#include "MyProject.h"

/***************************************************************************/
//创建日期：2025-2-10
//作    者：Merk Mao
//功    能：abz编码器接线，SCL1--A,SDA1--B,PA12--Z;  SCL2--A,SDA2--B,PA11--Z
/***************************************************************************/
//long cpr = M1ABZ_CPR;
extern long cpr;
/***************************************************************************/
long pulse_counter;//!< current pulse counter
long pulse_timestamp;//!< last impulse timestamp in us
uint8_t A_active,B_active,I_active; //!< current active states of A/B/I channel
uint8_t index_found = 0; //!< flag stating that the index has been found
uint8_t index_needsSearch;
float velocity_index_search = 1;    //针对ABZ编码器，检测机械零点时的速度，默认为1 rad/s
// velocity calculation variables
float prev_Th, pulse_per_second;
long prev_pulse_counter, prev_timestamp_us;
/***************************************************************************/
void Encoder_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE); //开启时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;    //PB6-SCL1-A,PB7-SDA1-B
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line6 | EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //双边触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //使能外部中断
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
  // counter setup
  pulse_counter = 0;
  pulse_timestamp = _micros();
  // velocity calculation variables
  prev_Th = 0;
  pulse_per_second = 0;
  prev_pulse_counter = 0;
  prev_timestamp_us = _micros();
}
/***************************************************************************/
//如果使用Z信号，调用这个函数，否则不调用，也不会进入下面的中断 EXTI15_10_IRQHandler
void Encoder_Index_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE); //开启时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;             //PA12-Z,
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;      //上升沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn; //使能外部中断
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/***************************************************************************/
//PB6--A,PB7--B
void EXTI9_5_IRQHandler(void)
{
	uint8_t A,B;
	
	if(EXTI_GetITStatus(EXTI_Line6) == SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line6);//清除中断标志位
		A = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6);
		if( A != A_active )
		{
			pulse_counter += (A_active == B_active) ? 1 : -1;
			pulse_timestamp = _micros();
			A_active = A;
		}
	}
	
	if(EXTI_GetITStatus(EXTI_Line7) == SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line7);//清除中断标志位
		B = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);
		if( B != B_active )
		{
			pulse_counter += (A_active != B_active) ? 1 : -1;
			pulse_timestamp = _micros();
			B_active = B;
		}
	}
}
/***************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	uint8_t I;
	long tmp;
	
	if(EXTI_GetITStatus(EXTI_Line12) == SET)
	{
		EXTI_ClearITPendingBit(EXTI_Line12); //清除中断标志位
		
		I = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12);
		if(I && !I_active)
		{
			index_found = 1;
			// align encoder on each index
			tmp = pulse_counter;
      // corrent the counter value
      pulse_counter = _round((float)pulse_counter/(float)cpr)*cpr;
      // preserve relative speed
      prev_pulse_counter += pulse_counter - tmp;
    }
    I_active = I;
	}
}
/***************************************************************************/
float encode_getSensorAngle(void)
{
	//return getAngle();
	return getAngle_ABZ();
}
/***************************************************************************/
float encode_getMechanicalAngle(void)
{
  return  _2PI * (pulse_counter % (int)cpr) / ((float)cpr);
}
/***************************************************************************/

//ReadABZ
float getAngle_ABZ(void)
{
  return  _2PI * pulse_counter / ((float)cpr);
}


float getVelocity_ABZ(void)
{
  long timestamp_us,dN;
	float Ts,Th,dt,velocity;
	
	timestamp_us = _micros();
  // sampling time calculation
  Ts = (timestamp_us - prev_timestamp_us) * 1e-6f;
  // quick fix for strange cases (micros overflow)
  if(Ts <= 0 || Ts > 0.5f) Ts = 1e-3f;

  // time from last impulse
  Th = (timestamp_us - pulse_timestamp) * 1e-6f;
  dN = pulse_counter - prev_pulse_counter;

  // Pulse per second calculation (Eq.3.)
  // dN - impulses received
  // Ts - sampling time - time in between function calls
  // Th - time from last impulse
  // Th_1 - time form last impulse of the previous call
  // only increment if some impulses received
  dt = Ts + prev_Th - Th;
  pulse_per_second = (dN != 0 && dt > Ts/2) ? dN / dt : pulse_per_second;

  // if more than 0.05f passed in between impulses
  if ( Th > 0.1f) pulse_per_second = 0;

  // velocity calculation
  velocity = pulse_per_second / ((float)cpr) * (_2PI);

  // save variables for next pass
  prev_timestamp_us = timestamp_us;
  // save velocity calculation variables
  prev_Th = Th;
  prev_pulse_counter = pulse_counter;
  return velocity;
}




