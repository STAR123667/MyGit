#ifndef CANTHREAD_H
#define CANTHREAD_H

#include  <QThread>
#include  <QDebug>
#include  <controlcan.h>

#define DEVICE_TYPE   4
#define DEVICE_CAN1  0
#define DEVICE_CAN2  1

class canthread
{

public:
    canthread();

    void stop();

    //1.打开设备
    bool openDevice(uint deviceType, uint debicIndex, uint baundRate);

    //2.初始化CAN
    bool initCAN();

    //3.启动CAN
    bool startCAN();

    //4.发送数据
    bool sendData(uint channel, uint ID, uchar remoteFlag, uchar externFlag, const unsigned char *data, uchar len);

    //5.关闭设备
    void closeDevice();

    //6.复位设备
    bool reSetCAN();

    uint m_deviceType;
    uint m_debicIndex;
    uint m_baundRate;
    uint m_debicCom;

    bool stopped;

signals:
    // void getProtocolData(VCI_CAN_OBJ *vci,unsigned int dwRel,unsigned int channel);
     //void boardInfo(VCI_BOARD_INFO vbi);

private:

    void  run();
    void  sleep(int msec);

};

#endif // CANTHREAD_H
