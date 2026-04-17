#include "gd32f10x.h"
#include "gd32f10x_libopt.h"
#include "systick.h"
#include "include.h"

/*添加电机频率调节变量*/
uint8_t motor_frequencyAdj;  

//主函数
int main(void)
{
	    
	   System_Init();
     systick_config();
	
    while(1)
    {
			
		   ScanKeyDealwith(device.keyNum);
			
			
    }

}
