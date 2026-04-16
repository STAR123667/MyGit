+ /**
  ******************************************************************************
	//创建日期：2025-2-10
  //作    者：Merk Mao
  //IC_MU spi  底层应用函数
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
	
#include "MyProject.h"
	
//#include "stm32f10x_spi.h"

//#include "IC_MU_SPI.h"
//#include "bsp_SysTick.h"
//#include "pbdata.h"

static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;    
static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);

/**
  * @brief  SPI_IC_MU   初始化                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            初始化
  * @param  无
  * @retval 无
  */
void SPI_IC_MU_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 使能SPI时钟 */
	IC_MU_SPI_APBxClock_FUN ( IC_MU_SPI_CLK, ENABLE );
	
	/* 使能SPI引脚相关的时钟 */
 	IC_MU_SPI_CS_APBxClock_FUN ( IC_MU_SPI_CS_CLK | IC_MU_SPI_SCK_CLK |
															 IC_MU_SPI_MISO_PIN | IC_MU_SPI_MOSI_PIN, ENABLE );
	
  /* 配置SPI的 CS引脚，普通IO即可 */
  GPIO_InitStructure.GPIO_Pin = IC_MU_SPI_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(IC_MU_SPI_CS_PORT, &GPIO_InitStructure);
	
  /* 配置SPI的 SCK引脚*/
  GPIO_InitStructure.GPIO_Pin = IC_MU_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(IC_MU_SPI_SCK_PORT, &GPIO_InitStructure);

  /* 配置SPI的 MISO引脚*/
  GPIO_InitStructure.GPIO_Pin = IC_MU_SPI_MISO_PIN;
  GPIO_Init(IC_MU_SPI_MISO_PORT, &GPIO_InitStructure);

  /* 配置SPI的 MOSI引脚*/
  GPIO_InitStructure.GPIO_Pin = IC_MU_SPI_MOSI_PIN;
  GPIO_Init(IC_MU_SPI_MOSI_PORT, &GPIO_InitStructure);

  /* 停止信号 IC_MU: CS引脚高电平*/
  SPI_IC_MU_CS_HIGH();

  /* SPI 模式配置 IC-MU最大时钟频率为10M  */
  // IC_MU芯片 支持SPI模式0及模式3，据此设置CPOL CPHA
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   //通过软件配置NSS
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;  //总72Mhz 设置分频2，4，8，16，……256。
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(IC_MU_SPIx , &SPI_InitStructure);

  /* 使能 SPI  */
  SPI_Cmd(IC_MU_SPIx , ENABLE);
	
	/* 使能 SPI的CRC校验  */
	//-------------------------------------------
	
}



 /**
  * @brief  激活IC-MU芯片，使OPCODE正常工作
  * @param  
  * @retval 无
  */
void ACTIVATE_FUN(void)
{
  
  SPI_IC_MU_CS_LOW();

  SPI_IC_MU_SendByte(ACTIVATE);
	SPI_IC_MU_SendByte(0X83);    //激活PACTIVE和RACTIVE
 
  SPI_IC_MU_CS_HIGH();
	
	//SysTick_Delay_Us(100);
  delay_us(100);
}

/**
  * @brief  读寄存器的状态
  * @param  
  * @retval 无
  */

u16 SPI_SDAD_Status_Fun(   )
{
	u16 Temp = 0,  Temp1 = 0 , Temp2 = 0 ;
  ACTIVATE_FUN();  
	

	 /* 开始通讯：CS低电平 */  
    SPI_IC_MU_CS_LOW();
	
	    SPI_IC_MU_SendByte(SDAD_Status);					//0xF5
	    SPI_IC_MU_SendByte(0x00);					
	    Temp1=SPI_IC_MU_SendByte(Dummy_Byte);
			Temp2=SPI_IC_MU_SendByte(Dummy_Byte);
 
	/* 结束通讯：CS高电平*/
	   SPI_IC_MU_CS_HIGH();
	
	Temp =  (Temp1 << 8) | Temp2;    //Temp的高8位是状态标志位，低8位是地址数据。
	
	return Temp;
  
}



/**
  * @brief  读IC-MU寄存器的数据
  * @param  ReadAddr，IC-MU芯片寄存器地址
  * @retval 无
  */

u16 SPI_ReadRegister_Fun( u8 ReadAddr  )
{
	u16 Temp = 0,  Temp1 = 0 , Temp2 = 0 ;
  ACTIVATE_FUN();  
	
  /* 开始通讯：CS低电平 */
  SPI_IC_MU_CS_LOW();
	
	 SPI_IC_MU_SendByte(Read_REGISTER);
	 SPI_IC_MU_SendByte(ReadAddr);
	/* 结束通讯：CS高电平*/
 SPI_IC_MU_CS_HIGH();

	 /* 开始通讯：CS低电平 */  
 SPI_IC_MU_CS_LOW();
	
	  SPI_IC_MU_SendByte(REGISTER_status);
	    Temp1=SPI_IC_MU_SendByte(Dummy_Byte);
			Temp2=SPI_IC_MU_SendByte(Dummy_Byte);
 
	/* 结束通讯：CS高电平*/
	   SPI_IC_MU_CS_HIGH();
	
	Temp =  (Temp1 << 8) | Temp2;    //Temp的高8位是状态标志位，低8位是地址数据。
	
	return Temp;
  
}



/**
  * @brief  写IC-MU寄存器的数据
  * @param  WriteAddr  写地址
  * @param  WriteData  写数据，该数据是写到芯片的寄存器的
  * @retval 无
  */

u16 SPI_WriteRegister_Fun ( u8 WriteAddr ,u8 WriteData )
{
	
	u16 Temp = 0,   Temp1 = 0 , Temp2 = 0;
  ACTIVATE_FUN();
	
  /* 开始通讯：CS低电平 */
 SPI_IC_MU_CS_LOW();
	
	SPI_IC_MU_SendByte(Write_REGISTER);
	SPI_IC_MU_SendByte(WriteAddr);
	SPI_IC_MU_SendByte(WriteData);
	
//	SPI_I2S_SendData(IC_MU_SPIx ,Write_REGISTER);
////	Temp0=SPI_I2S_ReceiveData(IC_MU_SPIx );
//	
//	SPI_I2S_SendData(IC_MU_SPIx ,WriteAddr);
////	Temp1=SPI_I2S_ReceiveData(IC_MU_SPIx );
//	
//	SPI_I2S_SendData(IC_MU_SPIx ,WriteData);
////	Temp2=SPI_I2S_ReceiveData(IC_MU_SPIx );
	
  SPI_IC_MU_CS_HIGH();
  //SysTick_Delay_Us(10000);
	 
  SPI_IC_MU_CS_LOW();
 
    SPI_IC_MU_SendByte(REGISTER_status);
		 Temp1=SPI_IC_MU_SendByte(Dummy_Byte);
		 Temp2=SPI_IC_MU_SendByte(Dummy_Byte);
 
//    SPI_I2S_SendData(IC_MU_SPIx ,REGISTER_status);
////	Temp3=SPI_I2S_ReceiveData(IC_MU_SPIx );
//	
//		SPI_I2S_SendData(IC_MU_SPIx ,Dummy_Byte);
//	Temp4=SPI_I2S_ReceiveData(IC_MU_SPIx );
//	
//	SPI_IC_MU_SendByte(Dummy_Byte);
//	Temp5=SPI_I2S_ReceiveData(IC_MU_SPIx );

 SPI_IC_MU_CS_HIGH();
 
   Temp =  (Temp1 << 8) | Temp2;   //高8位是状态标志位，可以根据状态判断是否写数据成功。低8位是写入的数据。
	 
	 return Temp;
 
 }

 
 /**
  * @brief  接收绝对值位置的数据，数据的长度需要自己配置，该函数以后还需要重新修改，可以修改成跟随配置的数据长度。
  * @param  
  * @retval 无
  * @attention   单步调试可以不考虑延时，当直接运行的时候，需要考虑延时等情况。
  */
 u32 SPI_SDAD_transmission_Fun ( void)
{
	
	u32 Temp = 0 , Temp1 = 0, Temp2 = 0 , Temp3 = 0 ;
  ACTIVATE_FUN();
	
   /* 开始通讯：CS低电平 */
   SPI_IC_MU_CS_LOW();
	
	    SPI_IC_MU_SendByte(SDAD_transmission);
			
			Temp1=SPI_IC_MU_SendByte(Dummy_Byte);
			Temp2=SPI_IC_MU_SendByte(Dummy_Byte);
			Temp3=SPI_IC_MU_SendByte(Dummy_Byte);
	 /* 结束通讯：CS高电平*/
   SPI_IC_MU_CS_HIGH();
     
   Temp = (  (Temp1 << 16) | (Temp2 << 8) | Temp3  )>> 5 ; //读出数据，右移5位，共24位，有效位为19位
	 
	 return Temp;
}


 /**
  * @brief  使用SPI读取一个字节的数据
  * @param  无
  * @retval 返回接收到的数据
  */
u8 SPI_IC_MU_ReadByte(void)
{
  return (SPI_IC_MU_SendByte(Dummy_Byte));   //#define Dummy_Byte    0xFF  Dummy_Byte可以为任意值
}

 /**
  * @brief  使用SPI发送一个字节的数据
  * @param  byte：要发送的数据
  * @retval 返回接收到的数据
  */
u8 SPI_IC_MU_SendByte(u8 byte)
{
	 SPITimeout = SPIT_FLAG_TIMEOUT;    //0x1000,十六进制的8，一个字节是8位
  /* 等待发送缓冲区为空，TXE事件 */  //等待上个字节发送完毕，传输完一帧，发送缓存区为空，TXE=1;跳出While循环。?`
  while (SPI_I2S_GetFlagStatus(IC_MU_SPIx , SPI_I2S_FLAG_TXE) == RESET)  
	{
    if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(0);  //等待8次还没发送完，则表示通讯失败。
   }

  /* 写入数据寄存器，把要写入的数据写入发送缓冲区 */
  SPI_I2S_SendData(IC_MU_SPIx , byte);

	SPITimeout = SPIT_FLAG_TIMEOUT;
  /* 等待接收缓冲区非空，RXNE事件 */ //接收完一帧?J接收缓存区非空，RXNE=1;跳出While循环
  while (SPI_I2S_GetFlagStatus(IC_MU_SPIx , SPI_I2S_FLAG_RXNE) == RESET)
  {
    if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
   }

  /* 读取数据寄存器，获取接收缓冲区数据 */
  return SPI_I2S_ReceiveData(IC_MU_SPIx );
}




/* WIP(busy)标志，IC_MU内部正在写入 */
#define WIP_Flag                  0x01

 /**
  * @brief  等待WIP(BUSY)标志被置0，即等待到IC_MU内部数据写入完毕
  * @param  none
  * @retval none
  */
void SPI_IC_MU_WaitForWriteEnd(void)
{
  u8 IC_MU_Status = 0;

  /* 选择 IC_MU: CS 低 */
  SPI_IC_MU_CS_LOW();

  /* 发送 读状态寄存器 命令 */
  SPI_IC_MU_SendByte(Read_REGISTER);

  /* 若IC_MU忙碌，则等待 */
  do
  {
		/* 读取IC_MU芯片的状态寄存器 */
    IC_MU_Status = SPI_IC_MU_SendByte(Dummy_Byte);	 
  }
  while ((IC_MU_Status & WIP_Flag) == SET);  /* 正在写入标志 */

  /* 停止信号  IC_MU: CS 高 */
  SPI_IC_MU_CS_HIGH();
}


   

/**
  * @brief  等待超时回调函数
  * @param  None.
  * @retval None.
  */
static  uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* 等待超时后的处理,输出错误信息 */
  FLASH_ERROR("SPI 等待超时!errorCode = %d",errorCode);
  return 0;
}
   
/*********************************************END OF FILE**********************/
