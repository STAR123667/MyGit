#ifndef __INCLUDE_H
#define __INCLUDE_H

#include "gd32f10x.h"
#include "gd32f10x_eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "key.h"
#include "systick.h"

//电机 使能引脚_定义//
#define MOTOR_EN_H   gpio_bit_set(GPIOC, GPIO_PIN_1)
#define MOTOR_EN_L   gpio_bit_reset(GPIOC, GPIO_PIN_1)

//电机 方向引脚_定义//
#define MOTOR_DIR_H   gpio_bit_set(GPIOC, GPIO_PIN_3)
#define MOTOR_DIR_L   gpio_bit_reset(GPIOC, GPIO_PIN_3)


#define MOTOR_EN(x)  if(x==SET){ MOTOR_EN_H; }else{ MOTOR_EN_L; }
#define MOTOR_DIR(x)  if(x==SET){ MOTOR_DIR_H; }else{ MOTOR_DIR_L; }

//LED 引脚_定义//
#define LED_R_H   gpio_bit_set(GPIOD, GPIO_PIN_11);
#define LED_R_L   gpio_bit_reset(GPIOD, GPIO_PIN_11);

#define LED_G_H   gpio_bit_set(GPIOD, GPIO_PIN_13);
#define LED_G_L   gpio_bit_reset(GPIOD, GPIO_PIN_13);

#define LED_B_H   gpio_bit_set(GPIOD, GPIO_PIN_15);
#define LED_B_L   gpio_bit_reset(GPIOD, GPIO_PIN_15);

//KEY 引脚_定义//
#define SW1  gpio_input_bit_get(GPIOC,GPIO_PIN_5)
#define SW2  gpio_input_bit_get(GPIOA,GPIO_PIN_7)
#define SW3  gpio_input_bit_get(GPIOA,GPIO_PIN_5)


#define RUN_SPEEN_1KHZ  (1000-1)
#define RUN_SPEEN_2KHZ  (500-1)
#define RUN_SPEEN_3KHZ  (330-1)
#define RUN_SPEEN_4KHZ  (250-1)
#define RUN_SPEEN_5KHZ  (200-1)
#define RUN_SPEEN_6KHZ  (167-1)
#define RUN_SPEEN_7KHZ  (143-1)
#define RUN_SPEEN_8KHZ  (125-1)
#define RUN_SPEEN_9KHZ  (111-1)
#define RUN_SPEEN_10KHZ (100-1)
#define RUN_SPEEN_11KHZ (91-1)


struct DEVICE_Typedef{ 

    uint8_t motor_temp; 
    uint8_t keyNum; 
	  uint8_t keyTime; 
	  uint8_t keyFlag:1; 
	  
	  #define HIGH  SET 
    #define LOW   RESET
	
};
extern struct DEVICE_Typedef device; 
   

enum SW_VALUE{

     SW_OFF = 0X07, 
     SW1_ON = 0X06,  
     SW2_ON = 0X05, 
     SW3_ON = 0X03, 
	      
};

enum MOTOR_ADJ{

     MOTOR_1KHZ = 0X01, 
     MOTOR_2KHZ,  
     MOTOR_3KHZ,
	   MOTOR_4KHZ,
	   MOTOR_5KHZ,  
     MOTOR_6KHZ,
	   MOTOR_7KHZ,
	   MOTOR_8KHZ,
	   MOTOR_9KHZ,
	   MOTOR_10KHZ,
	   MOTOR_11KHZ,
	      
};



void System_Init(void);
void Clock_config(void); 
void Led_Init(void);
void Key_Init(void);
void Motor_Init(void);
void Time2_Init(void);
void nvic_config(void);
#endif /* __INCLUDE_H */
