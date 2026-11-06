#ifndef M_LOG_H
#define M_LOG_H

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include <stdio.h>

#if 0
#define LOG(x, s...) \
		{uint32_t temp=osKernelSysTick()*portTICK_PERIOD_MS;printf("[ %02d:%02d:%02d \'%03d ] %s():  " x "\r\n",\
		(temp/(3600*1000))%24, (temp/(60*1000))%60,(temp/1000)%60,temp%1000,__FUNCTION__, ##s);}
#endif

#if 0
#define LOG(x, s...) \
		{uint32_t temp=osKernelSysTick()*portTICK_PERIOD_MS;printf("[ %02d:%02d:%02d \'%03d ] :  " x "\r\n",\
		(temp/(3600*1000))%24, (temp/(60*1000))%60,(temp/1000)%60,temp%1000, ##s);}
#endif
#define LOG(x, s...) \
		{uint32_t temp=osKernelSysTick()*portTICK_PERIOD_MS;printf("[ %d day, %02d:%02d:%02d \'%03d ] :  " x "\r\n",\
		(temp/(3600*1000))/24,(temp/(3600*1000))%24, (temp/(60*1000))%60,(temp/1000)%60,temp%1000, ##s);}

#define LOG_NON_CRLF(x, s...) \
		{uint32_t temp=osKernelSysTick()*portTICK_PERIOD_MS;printf("[ %d day, %02d:%02d:%02d \'%03d ] :  " x "",\
		(temp/(3600*1000))/24,(temp/(3600*1000))%24, (temp/(60*1000))%60,(temp/1000)%60,temp%1000, ##s);}

#define LOG_BUF(prefix,buf,length)			\
	{										\
		LOG_NON_CRLF("%s",prefix);			\
		{									\
			uint16_t i	;						\
			for( i=0;i<length;i++)			\
			{								\
				printf("%02X ", frame[i]);		\
			}								\
			printf("\r\n");						\
		}									\
	}
#endif
