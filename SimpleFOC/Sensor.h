#ifndef SENSOR_LIB_H
#define SENSOR_LIB_H

/******************************************************************************/
typedef struct 
{
	unsigned short mag_cpol;
	unsigned short mag_cpha;
	unsigned short mag_BrtPre;
}MagnetSensor_Para;
/******************************************************************************/
extern long  cpr;
extern float angle_prev;
/******************************************************************************/
void MagneticSensor_Init(void);
float getAngle(void);
float getAngle_ABZ(void);
float getVelocity(void);
float getVelocity_ABZ(void);
/******************************************************************************/
//---------------
void Encoder_init(void);
void Encoder_Index_init(void);//如果使用Z信号，调用这个函数，否则不调用，也不会进入下面的中断 EXTI15_10_IRQHandler

//---------------
#endif
