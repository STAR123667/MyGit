#ifndef __IC_MU_SPI_H
#define __IC_MU_SPI_H

#include "stm32f10x.h"
#include <stdio.h>


#define  IC_MU_ID       0x07   //ic-MU Y2     HARD_REV(7:0) Addr. SER: 0x74; bit 7:0

#define SPI_IC_MU_PageSize              256
#define SPI_IC_MU_PerWritePageSize      256


/************ I2C_DEVICE(7:0)  Addr.SER:0x5E; bit 7:0  ******************/
/*									Code Meaning
										0xA0 write EEPROM
										0xA1 read EEPROM
										0xC0 write iC-PVL (status/commands)
										0xC1 read iC-PVL (status/commands)
*/
/************ I2C_RAM_START  Addr. SER: 0x5C; bit 7:0 ********************/
/************ I2C_DEV_START Addr. SER: 0x5B; bit 7:0 ********************/
/************ EVENT_COUNT(7:0) Addr. SER:0x73; bit 7:0 ********************/


/************ CMD_MU(7:0)      Addr.SER:0x75; bit 7:0  ******************/
#define reserved          		    0x00  //no function
#define WRITE_ALL          		    0x01  //Write internal confguration and Offset values to EEPROM
#define WRITE_OFF         		    0x02	//Write internal Offset values to EEPROM
#define ABS_RESET         		    0x03	//Reset of Absolute value (including ABZ-part), takes typ. 10 ms
#define NON_VER        		        0x04	//Verifcation of actual position by doing a nonius calculation
#define MT_RESET         		      0x05	//New read in and synchronisation of multiturn value	
#define MT_VER       		          0x06	//Read in of multiturn and verifcation of counted multiturn value
#define SOFT_RESET       		      0x07	//startup with read in of EEPROM
#define SOFT_PRES      		        0x08	//Set output to preset
#define SOFT_E2P_PRES      		    0x09  //Set output to preset and save offset values to EEPROM
#define I2C_COM       		        0x0A	//start I2C communication
#define EVENT_COUNT          		  0x0B	//increment event counter by 1
#define SWITCH          		      0x0C	//Writes all confgurations parameters without offsets to EEPROM.
                                        //MODEA/RPL will be exchanged with MODEA_NEW/RPL_NEW during write operation
#define CRC_VER          		      0x0D	//Verifcation of CRC16 and CRC8
#define CRC_CALC          		    0x0E	//Recalculate internal CRC16 and CRC8 values
#define SET_MTC          		      0x0F	//Set MTC-Pin --MODE_MT=0x00
#define RES_MTC         		      0x10	//Reset MTC-Pin --MODE_MT=0x00
//#define reserved          		  0x11	//no function
//...     ....                    ...
//#define reserved          		  0xFF




/************ SPI OPCODE 操作码  ******************/
#define ACTIVATE          		    0xB0  //
#define SDAD_transmission         0xA6	//
#define SDAD_Status         		  0xF5	//检查Sensor data是否合法，合法 bit8==0。
#define Read_REGISTER          		0x97	//
#define Write_REGISTER            0xD2	//
#define REGISTER_status           0xAD   //  REGISTER_status/data



/* WIP(busy)标志，FLASH内部正在写入 */
#define WIP_Flag                  0x01
#define Dummy_Byte                0xFF
/*命令定义-结尾*******************************/


/*SPI接口定义-开头****************************/
#define      IC_MU_SPIx                        SPI1
#define      IC_MU_SPI_APBxClock_FUN          RCC_APB2PeriphClockCmd
#define      IC_MU_SPI_CLK                     RCC_APB2Periph_SPI1

/*
//CS(NSS)引脚 片选选普通GPIO即可
#define      IC_MU_SPI_CS_APBxClock_FUN       RCC_APB2PeriphClockCmd
#define      IC_MU_SPI_CS_CLK                  RCC_APB2Periph_GPIOC    
#define      IC_MU_SPI_CS_PORT                 GPIOC
#define      IC_MU_SPI_CS_PIN                  GPIO_Pin_2

//SCK引脚
#define      IC_MU_SPI_SCK_APBxClock_FUN      RCC_APB2PeriphClockCmd
#define      IC_MU_SPI_SCK_CLK                 RCC_APB2Periph_GPIOA   
#define      IC_MU_SPI_SCK_PORT                GPIOA   
#define      IC_MU_SPI_SCK_PIN                 GPIO_Pin_5
//MISO引脚
#define      IC_MU_SPI_MISO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define      IC_MU_SPI_MISO_CLK                RCC_APB2Periph_GPIOA    
#define      IC_MU_SPI_MISO_PORT               GPIOA 
#define      IC_MU_SPI_MISO_PIN                GPIO_Pin_6
//MOSI引脚
#define      IC_MU_SPI_MOSI_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define      IC_MU_SPI_MOSI_CLK                RCC_APB2Periph_GPIOA    
#define      IC_MU_SPI_MOSI_PORT               GPIOA 
#define      IC_MU_SPI_MOSI_PIN                GPIO_Pin_7
*/


//CS(NSS)引脚 片选选普通GPIO即可
#define      IC_MU_SPI_CS_APBxClock_FUN       RCC_APB2PeriphClockCmd
#define      IC_MU_SPI_CS_CLK                  RCC_APB2Periph_GPIOB    
#define      IC_MU_SPI_CS_PORT                 GPIOB
#define      IC_MU_SPI_CS_PIN                  GPIO_Pin_8

//SCK引脚
#define      IC_MU_SPI_SCK_APBxClock_FUN      RCC_APB2PeriphClockCmd
#define      IC_MU_SPI_SCK_CLK                 RCC_APB2Periph_GPIOB   
#define      IC_MU_SPI_SCK_PORT                GPIOB   
#define      IC_MU_SPI_SCK_PIN                 GPIO_Pin_13
//MISO引脚
#define      IC_MU_SPI_MISO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define      IC_MU_SPI_MISO_CLK                RCC_APB2Periph_GPIOB    
#define      IC_MU_SPI_MISO_PORT               GPIOB 
#define      IC_MU_SPI_MISO_PIN                GPIO_Pin_14
//MOSI引脚
#define      IC_MU_SPI_MOSI_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define      IC_MU_SPI_MOSI_CLK                RCC_APB2Periph_GPIOB    
#define      IC_MU_SPI_MOSI_PORT               GPIOB 
#define      IC_MU_SPI_MOSI_PIN                GPIO_Pin_15




#define  		SPI_IC_MU_CS_LOW()     						GPIO_ResetBits( IC_MU_SPI_CS_PORT, IC_MU_SPI_CS_PIN )
#define  		SPI_IC_MU_CS_HIGH()    						GPIO_SetBits( IC_MU_SPI_CS_PORT, IC_MU_SPI_CS_PIN )

/*SPI接口定义-结尾****************************/

/*等待超时时间*/
#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

/*信息输出*/
#define FLASH_DEBUG_ON         1

#define FLASH_INFO(fmt,arg...)           printf("<<-FLASH-INFO->> "fmt"\n",##arg)
#define FLASH_ERROR(fmt,arg...)          printf("<<-FLASH-ERROR->> "fmt"\n",##arg)
#define FLASH_DEBUG(fmt,arg...)          do{\
                                          if(FLASH_DEBUG_ON)\
                                          printf("<<-FLASH-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)

void SPI_IC_MU_Init(void);

void SPI_IC_MU_SectorErase(u32 SectorAddr);
void SPI_IC_MU_BulkErase(void);
void SPI_IC_MU_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_IC_MU_BufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_IC_MU_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);
u32 SPI_IC_MU_ReadID(void);
u32 SPI_IC_MU_ReadDeviceID(void);
void SPI_IC_MU_StartReadSequence(u32 ReadAddr);
void SPI_IC_MU_PowerDown(void);
void SPI_IC_MU_WAKEUP(void);


u8 SPI_IC_MU_ReadByte(void);
u8 SPI_IC_MU_SendByte(u8 byte);
u16 SPI_IC_MU_SendHalfWord(u16 HalfWord);
void SPI_IC_MU_WriteEnable(void);
void SPI_IC_MU_WaitForWriteEnd(void);
																					
void ACTIVATE_FUN(void);
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u8 NumByteToRead);

u16 SPI_ReadRegister_Fun( u8 ReadAddr  );
u16 SPI_WriteRegister_Fun ( u8 WriteAddr ,u8 WriteData );
u32 SPI_SDAD_transmission_Fun (void);
u16 SPI_REGISTER_status_Fun(void);

u16 SPI_SDAD_Status_Fun( void  );





#endif /* __IC_MU_SPI_H */

