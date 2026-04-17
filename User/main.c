#include "gd32f10x.h"
#include "gd32f10x_libopt.h"
#include "systick.h"
#include "include.h"

/*增加注释*/
uint8_t key_value = 0;
uint16_t key_num = 0;

//按键处理函数
void ScanKeyDealwith(uint16_t key_num) 
{
    static uint8_t num;	
    
    
      if( (key_num & SW_OFF) == 0x07 )
        {
                //	device.keyTime=0;
           device.keyFlag=0;
        }
      else 
        {
           device.keyFlag=1;  
             device.keyTime++;
            //  if(device.keyTime>100) device.keyTime=0;
              num = key_num;
            
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
}


int main(void)
{
	    
	   System_Init();
     systick_config();


	
    while(1)
    {
			
		   ScanKeyDealwith(device.keyNum);
			
			
    }

}
