#include "canthread.h"
#include <QTime>
#include <QCoreApplication>
#include <QMetaType>
#include <string.h>

canthread::canthread()
{
      stopped = false;
}


void canthread::stop()
{
      stopped = true;
}


bool canthread::openDevice(uint deviceType, uint debicIndex, uint baundRate)
{
       m_deviceType = deviceType;
       m_debicIndex = debicIndex;
       m_baundRate = baundRate;
       unsigned int dwRel;
       dwRel = VCI_OpenDevice(m_deviceType, m_debicIndex, 0);
       if(dwRel != 1)
           return false;
        else
           return true;
}


bool canthread::initCAN()
{
    unsigned int dwRel = VCI_ClearBuffer(m_deviceType, m_debicIndex, 0);
    dwRel = VCI_ClearBuffer(m_deviceType, m_debicIndex, 1);
    VCI_INIT_CONFIG vic;
    vic.AccCode=0x80000008;
    vic.AccMask=0xFFFFFFFF;
    vic.Filter=1;
    vic.Mode=0;
    switch(m_baundRate) {
     case 10:
            vic.Timing0=0x31;
            vic.Timing1=0x1c;
        break;//(10K)
     case 20:
            vic.Timing0=0x18;
            vic.Timing1=0x1c;
        break;//(20K)
     case 40:
         vic.Timing0=0x87;
         vic.Timing1=0xff;
        break;//(40K)
     case 50:
         vic.Timing0=0x09;
         vic.Timing1=0x1c;
        break;//(50K)
    case 80:
         vic.Timing0=0x83;
         vic.Timing1=0xff;
        break;//(80K)
    case 100:
         vic.Timing0=0x04;
         vic.Timing1=0x1c;
        break;//(100K)
    case 125:
         vic.Timing0=0x03;
         vic.Timing1=0x1c;
         break;//(125K)
    case 200:
         vic.Timing0=0x81;
         vic.Timing1=0xfa;
         break;//(200K)
    case 250:
         vic.Timing0=0x01;
         vic.Timing1=0x1c;
         break;//(250K)
    case 400:
         vic.Timing0=0x80;
         vic.Timing1=0xfa;
         break;//(400K)
    case 500:
         vic.Timing0=0x00;
         vic.Timing1=0x1c;
         break;//(500K)
    case 666:
         vic.Timing0=0x80;
         vic.Timing1=0xb6;
         break;//(666K)
    case 800:
         vic.Timing0=0x00;
         vic.Timing1=0x16;
         break;//(800K)
    case 1000:
         vic.Timing0=0x00;
         vic.Timing1=0x14;
         break;//(1000K)
    case 33:
         vic.Timing0=0x09;
         vic.Timing1=0x6f;
         break;//(33K)
    case 66:
         vic.Timing0=0x04;
         vic.Timing1=0x6f;
         break;//(66K)
    case 83:
         vic.Timing0=0x03;
         vic.Timing1=0x6f;
         break;//(83K)
    default:
         break;
    }
    dwRel = VCI_InitCAN(m_deviceType, m_debicIndex, 0, &vic);
    dwRel = VCI_InitCAN(m_deviceType, m_debicIndex, 1, &vic);
    if(dwRel !=1)
          return false;
    else
         qDebug()<<"init success";

    VCI_BOARD_INFO vbi;
    dwRel = VCI_ReadBoardInfo(m_deviceType, m_debicIndex, &vbi);
    if(dwRel !=1)
        return false;
    else
      //  emit boardInfo(vbi);
    return true;
}


bool canthread::startCAN()
{
     if(VCI_StartCAN(m_deviceType, m_debicIndex, 0) !=1)
     {
         qDebug()<<"start 0 fail.";
         return false;
     }
     else
         qDebug()<<"start 0 success.";
     if(VCI_StartCAN(m_deviceType, m_debicIndex, 1) !=1)
     {
         qDebug()<<"start 1 fail.";
         return false;
     }
     else
         qDebug()<<"start 1 success.";
     return true;
}


bool canthread::sendData(uint channel, uint ID, uchar remoteFlag, uchar externFlag, const unsigned char *data, uchar len)
{
    unsigned int dwRel;
    VCI_CAN_OBJ vco;
    vco.ID = ID;
    vco.RemoteFlag = remoteFlag;
    vco.ExternFlag  = externFlag;
    vco.DataLen = len;
    for(uint j=0; j<len; j++)
    {
        vco.Data[j] = data[j];
    }
    dwRel = VCI_Transmit(DEVICE_TYPE , DEVICE_CAN1, channel, &vco,1);
    if(dwRel>0)
        return true;
    else
        return false;
}


void canthread::closeDevice()
{
      VCI_CloseDevice(m_deviceType, m_debicIndex);
}


bool canthread::reSetCAN()
{
      if(VCI_ResetCAN(m_deviceType, m_debicIndex, 0) !=1)
      {
             qDebug()<<"reset 0 fail.";
             return false;
      }
      else
             qDebug()<<"reset 0 success.";
      if(VCI_ResetCAN(m_deviceType, m_debicIndex, 1) !=1)
      {
             qDebug()<<"reset 1 fail.";
             return false;
      }
      else
             qDebug()<<"reset 1 success.";
      return true;
}


void canthread::run()
{
        while(!stopped)
        {
            unsigned int dwRel;
            VCI_CAN_OBJ vco[2500];
            dwRel = VCI_Receive(m_deviceType, m_debicIndex, 0, vco,2500,0);
            if(dwRel > 0)
              //  emit getProtocolData(vco,dwRel,0);
            dwRel = VCI_Receive(m_deviceType, m_debicIndex, 1, vco,2500,0);
            if(dwRel > 0)
               // emit getProtocolData(vco,dwRel,1);
            sleep(30);
        }
        stopped = false;
}


void canthread::sleep(int msec)
{
       QTime dieTime = QTime::currentTime().addMSecs(msec);
       while( QTime::currentTime() < dieTime )
          QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}












