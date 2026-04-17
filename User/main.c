#include "gd32f10x.h"
#include "gd32f10x_libopt.h"
#include "systick.h"
#include "include.h"

/*增加注释*/
uint8_t key_value = 0;
uint16_t key_num = 0;

int main(void)
{
	    
	   System_Init();
     systick_config();


	
    while(1)
    {
			
		   ScanKeyDealwith(device.keyNum);
			
			
    }

}
