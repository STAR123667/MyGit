#include "gd32f10x.h"
#include "gd32f10x_libopt.h"
#include "systick.h"
#include "include.h"

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
