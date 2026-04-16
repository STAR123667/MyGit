//===========================
//创建日期：2025-2-10
//作    者：Merk Mao
//功    能：SPI传感器
//===========================


#include "MyProject.h"

/******************************************************************************/
#define SPI2_CS1_L  GPIO_ResetBits(GPIOB, GPIO_Pin_8)      //CS1_L
#define SPI2_CS1_H  GPIO_SetBits(GPIOB, GPIO_Pin_8)        //CS1_H
/******************************************************************************/
void delay_s(int i)
{
	while(i--);
}
/******************************************************************************/
//AS5047P、AS5048、AS5147 代码通用
unsigned short ReadAS5047P(unsigned short  addr)
{
	unsigned short  u16Data;
	
	SPI2_CS1_L;
	SPIx_ReadWriteByte(addr);
	SPI2_CS1_H;
	delay_s(20);  //1us
	
	SPI2_CS1_L;
	u16Data = SPIx_ReadWriteByte(0);
	SPI2_CS1_H;
	delay_s(20);  //1us
	
	return u16Data;
}
/******************************************************************************/
#define SPI2_TX_OFF {GPIOB->CRH&=0x0FFFFFFF;GPIOB->CRH|=0x40000000;}  //把PB15(MOSI)配置为浮空模式
#define SPI2_TX_ON  {GPIOB->CRH&=0x0FFFFFFF;GPIOB->CRH|=0xB0000000;}  //把PB15(MOSI)配置为复用推挽输出(50MHz)
/******************************************************************************/
unsigned short ReadTLE5012B(unsigned short Comm)
{
	unsigned short u16Data;
	
	SPI2_CS1_L;
	SPIx_ReadWriteByte(Comm);
	SPI2_TX_OFF;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();  //Twr_delay=130ns min
	u16Data = SPIx_ReadWriteByte(0xffff);
	
	SPI2_CS1_H;
	SPI2_TX_ON;
	return(u16Data);
}
/******************************************************************************/
/******************************************************************************/
unsigned short ReadMA730(unsigned short  addr)
{
	unsigned short u16Data;
	
	SPI2_CS1_L;
	u16Data=SPIx_ReadWriteByte(addr);
	SPI2_CS1_H;
	
	return u16Data;
}
/******************************************************************************/


/*uint8_t crc_high_first(uint8_t *ptr, int len)
{
	uint8_t i;
	uint8_t crc=0;
	
	while(len--)
	{
		crc ^= *ptr++;
		
		for(i=0;i<8;i++)
		{
			if(crc&0x80)crc=(crc<<1)^0x07;
			else  crc=(crc<<1);
		}
	}
	
	return (crc);
}
**************************************************************************/

unsigned long ReadMT6835(void)//连续读角度
///void ReadContinousAngle(MT6835_VAL *buff)
{
	uint16_t back[2];
	//uint8_t  p[3];
	//uint8_t  crc;
	
	SPI2_CS1_L;
	SPIx_ReadWriteByte_MT6835(0xA003);
	back[0] = SPIx_ReadWriteByte_MT6835(0);  //reg.3+reg.4  angle[20:5]
	back[1] = SPIx_ReadWriteByte_MT6835(0);  //reg.5+reg.6  angle[4:0]+status[2:0]+crc[7:0]
	SPI2_CS1_H;
	
  return  (back[0]<<5)|(back[1]>>11);
}

//连续读角度
/*
void ReadContinousAngle(MT6835_VAL *buff)
{
	uint16_t back[2];
	uint8_t  p[3];
	uint8_t  crc;
	
	SPI2_CS1_L;
	SPIx_ReadWriteByte(0xA003);
	back[0] = SPIx_ReadWriteByte(0);  //reg.3+reg.4  angle[20:5]
	back[1] = SPIx_ReadWriteByte(0);  //reg.5+reg.6  angle[4:0]+status[2:0]+crc[7:0]
	SPI2_CS1_H;
	
	buff->angle = (back[0]<<5)|(back[1]>>11);
	buff->statu = (back[1]>>8)&0x07;
	
	p[0]=back[0]>>8;
	p[1]=back[0];
	p[2]=back[1]>>8;
	crc =back[1];
	
	if(crc_high_first(p,3)==crc)buff->crc = 0;
	else  buff->crc = 1;
}
*/
/***************************************************************************/
 /**
  * @brief  激活IC-MU芯片，使OPCODE正常工作
  * @param  
  * @retval 无
  */
void ACTIVATE_FUN_ICMU(void)
{
  
  //SPI_IC_MU_CS_LOW();
	 SPI2_CS1_L;

  //SPI_IC_MU_SendByte(ACTIVATE);
	SPIx_ReadWriteByte_ICMU(ACTIVATE);
	
	//SPI_IC_MU_SendByte(0X83);    //激活PACTIVE和RACTIVE
  SPIx_ReadWriteByte_ICMU(0X83);    //激活PACTIVE和RACTIVE
	
  //SPI_IC_MU_CS_HIGH();
	 SPI2_CS1_H;
	
	//SysTick_Delay_Us(100);
  delay_us(100);
}


 /**
  * @brief  接收绝对值位置的数据，数据的长度需要自己配置，该函数以后还需要重新修改，可以修改成跟随配置的数据长度。
  * @param  
  * @retval 无
  * @attention   单步调试可以不考虑延时，当直接运行的时候，需要考虑延时等情况。
  */
//u32 SPI_SDAD_transmission_Fun_ICMU ( void)
u32  ReadAngle_ICMU(void)
{
	
	u32 Temp = 0 , Temp1 = 0, Temp2 = 0 , Temp3 = 0 ;
  ACTIVATE_FUN_ICMU();
	
   /* 开始通讯：CS低电平 */
   //SPI_IC_MU_CS_LOW();
	 SPI2_CS1_L;
	    //SPI_IC_MU_SendByte(SDAD_transmission);
			SPIx_ReadWriteByte_ICMU(SDAD_transmission);
	
			//Temp1=SPI_IC_MU_SendByte(Dummy_Byte);
			Temp1=SPIx_ReadWriteByte_ICMU(Dummy_Byte);
	
			//Temp2=SPI_IC_MU_SendByte(Dummy_Byte);
			Temp2=SPIx_ReadWriteByte_ICMU(Dummy_Byte);
	
			//Temp3=SPI_IC_MU_SendByte(Dummy_Byte);
			Temp3=SPIx_ReadWriteByte_ICMU(Dummy_Byte);
	
	 /* 结束通讯：CS高电平*/
   //SPI_IC_MU_CS_HIGH();
	 SPI2_CS1_H;
     
   Temp = (  (Temp1 << 16) | (Temp2 << 8) | Temp3  )>> 5 ; //读出数据，右移5位，共24位，有效位为19位
	 
	 return Temp;
}


