#include "key.h"


/*添加注释*/


uint8_t GetKeyNum(void)
{//10ms
   static uint8_t SaveKey; 
	 uint8_t KeyNum=0;
   SaveKey = ( KeyNum | SW1 | SW2 <<1 | SW3<<2 );
   return SaveKey;
}

void ScanKeyDealwith(uint8_t knum)
{//10ms
	  
    static uint8_t num;	
	
	
	  if( (knum & SW_OFF) == 0x07 )
		{
				//	device.keyTime=0;
		   device.keyFlag=0;
		}
	  else 
		{
		   device.keyFlag=1;  
		     device.keyTime++;
			//  if(device.keyTime>100) device.keyTime=0;
			  num = knum;
			
		}			

	      if( device.keyFlag == 0 && device.keyTime > 0 )
			  {  
					 switch(num)
					 {
					   case SW_OFF:{;}break;
					   case SW1_ON:{ 
							 
							    gpio_toggle_bits(GPIOD,GPIO_PIN_11);  //LED
							    gpio_toggle_bits(GPIOC,GPIO_PIN_1);   //MOTOR_EN 
							    
							    delay_1ms(1);
							    device.motor_temp=1;
							    motor_frequencyAdj(device.motor_temp);
							    
						 
						 }break;
						 case SW2_ON:{

   							  gpio_toggle_bits(GPIOD,GPIO_PIN_13);  //LED
							    gpio_toggle_bits(GPIOC,GPIO_PIN_3);   //MOTOR_DIR
						 
						 }break;
						 case SW3_ON:{ 
						 
						      gpio_toggle_bits(GPIOD,GPIO_PIN_15);   //LED
							    delay_1ms(1);
							    device.motor_temp++;
							    motor_frequencyAdj(device.motor_temp);
							    if(device.motor_temp>MOTOR_11KHZ){ device.motor_temp=MOTOR_1KHZ; }
						  
						 }break;
					 }
					   num=0;
					  device.keyTime=0;
				}

}

void gpio_toggle_bits(uint32_t gpio_periph,uint32_t pin)
{
    if((uint32_t)RESET !=(GPIO_OCTL(gpio_periph)&(pin))){
        GPIO_BC(gpio_periph) = (uint32_t)pin;
    }else{
        GPIO_BOP(gpio_periph) = (uint32_t)pin;
    }
}

void motor_frequencyAdj(uint8_t adjNum)
{
	  timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara; 
	
	   timer_auto_reload_shadow_disable(TIMER1);
     timer_disable(TIMER1);
	
	
	    timer_deinit(TIMER1);
	  
	    /* TIMER1 configuration */
    timer_initpara.prescaler         = 108-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    //timer_initpara.period            = RUN_SPEEN_2KHZ;
	
	  switch(adjNum)
		{
		  case MOTOR_1KHZ:{ timer_initpara.period = RUN_SPEEN_1KHZ; } break;
			case MOTOR_2KHZ:{ timer_initpara.period = RUN_SPEEN_2KHZ; } break;
			case MOTOR_3KHZ:{ timer_initpara.period = RUN_SPEEN_3KHZ; } break;
			case MOTOR_4KHZ:{ timer_initpara.period = RUN_SPEEN_4KHZ; } break;
		  case MOTOR_5KHZ:{ timer_initpara.period = RUN_SPEEN_5KHZ; } break;
			case MOTOR_6KHZ:{ timer_initpara.period = RUN_SPEEN_6KHZ; } break;
			case MOTOR_7KHZ:{ timer_initpara.period = RUN_SPEEN_7KHZ; } break;
			case MOTOR_8KHZ:{ timer_initpara.period = RUN_SPEEN_8KHZ; } break;
			case MOTOR_9KHZ:{ timer_initpara.period = RUN_SPEEN_9KHZ; } break;
			case MOTOR_10KHZ:{ timer_initpara.period = RUN_SPEEN_10KHZ; } break;
			case MOTOR_11KHZ:{ timer_initpara.period = RUN_SPEEN_11KHZ; } break;
		}
	
	
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER1,&timer_initpara);
	
	  /* CH1,CH2 and CH3 configuration in PWM mode1 */
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_LOW;
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_LOW;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

    timer_channel_output_config(TIMER1,TIMER_CH_1,&timer_ocintpara);

    /* CH1 configuration in PWM mode1,duty cycle 25% */
    timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_1, timer_initpara.period/2);
    timer_channel_output_mode_config(TIMER1,TIMER_CH_1,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER1,TIMER_CH_1,TIMER_OC_SHADOW_DISABLE);
	
	   /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER1);
    /* auto-reload preload enable */
    timer_enable(TIMER1);
		
		
}


