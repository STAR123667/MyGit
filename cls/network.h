#ifndef NETWORK_H
#define NETWORK_H

#include <QWidget>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QObject>
#include <QSharedPointer>
#include <QActionGroup>
#include <QCoreApplication>
#include <QDebug>
#include <QTime>
#include <QByteArray>
#include <QIODevice>
#include <QBuffer>
#include <QImageReader>
#include <QDataStream>
#include <stdio.h>
/*Sql head flie*/
#include <mysql.h>

/*C head flie*/
#include <stdio.h>
#include <string.h>

/*AI head flie*/
#include <ai_python.h>

/*公共部分*/

/* 设备状态——地址 */
#define DEVICE_RUN                         "%DB600.DBD0"       /*设备运行状态*/
#define DEVICE_FOREWARD_SPEEN    "%DB600.DBD12"    /*设备正转速度*/
#define DEVICE_REAL_SPEEN             "%DB600.DBD16"    /*设备实时速度*/
#define MACHIN_HEAD_A_STATE        "%DB600.DBD4"      /*机头A涂布状态*/
#define MACHIN_HEAD_B_STATE        "%DB600.DBD8"      /*机头B涂布状态*/

/* 机头A——地址 */
#define MACHINHEAD_A_A_TUBU_VALUE                    "%DB600.DBD20"    /*机头A_A料涂布压力实时值*/
#define MACHINHEAD_A_B_TUBU_VALUE                    "%DB600.DBD24"    /*机头A_B料涂布压力实时值*/
#define MACHINHEAD_A_A_BREAK_VALUE                  "%DB600.DBD28"    /*机头A_A料回流压力实时值*/
#define MACHINHEAD_A_B_BREAK_VALUE                  "%DB600.DBD32"    /*机头A_B料回流压力实时值*/
#define MACHINHEAD_A_A_BENSPEEN_SET_VALUE     "%DB600.DBD36"    /*机头A_A料螺杆泵泵速设定值*/
#define MACHINHEAD_A_B_BENSPEEN_SET_VALUE     "%DB600.DBD40"    /*机头A_B料螺杆泵泵速设定值*/
#define MACHINHEAD_A_A_BENSPEEN_REAL_VALUE   "%DB600.DBD44"    /*机头A_A料螺杆泵泵速实时值*/
#define MACHINHEAD_A_B_BENSPEEN_REAL_VALUE   "%DB600.DBD48"    /*机头A_B料螺杆泵泵速实时值*/

/* 机头B——地址 */
#define MACHINHEAD_B_A_TUBU_VALUE                    "%DB600.DBD52"    /*机头B_A料涂布压力实时值*/
#define MACHINHEAD_B_B_TUBU_VALUE                    "%DB600.DBD56"    /*机头B_B料涂布压力实时值*/
#define MACHINHEAD_B_A_BREAK_VALUE                  "%DB600.DBD60"    /*机头B_A料回流压力实时值*/
#define MACHINHEAD_B_B_BREAK_VALUE                  "%DB600.DBD64"    /*机头B_B料回流压力实时值*/
#define MACHINHEAD_B_A_BENSPEEN_SET_VALUE     "%DB600.DBD68"    /*机头B_A料螺杆泵泵速设定值*/
#define MACHINHEAD_B_B_BENSPEEN_SET_VALUE     "%DB600.DBD72"    /*机头B_B料螺杆泵泵速设定值*/
#define MACHINHEAD_B_A_BENSPEEN_REAL_VALUE   "%DB600.DBD76"    /*机头B_A料螺杆泵泵速实时值*/
#define MACHINHEAD_B_B_BENSPEEN_REAL_VALUE   "%DB600.DBD80"    /*机头B_B料螺杆泵泵速实时值*/
/* 机头A浆料温度——地址  */
#define MACHINHEAD_A_A_SIZING_TEMPERATURE     "%DB600.DBD92"    /*机头A_A料浆料温度*/
#define MACHINHEAD_A_B_SIZING_TEMPERATURE     "%DB600.DBD96"    /*机头A_B料浆料温度*/
/* 机头B浆料温度——地址  */
#define MACHINHEAD_B_A_SIZING_TEMPERATURE     "%DB600.DBD100"   /*机头B_A料浆料温度*/
#define MACHINHEAD_B_B_SIZING_TEMPERATURE     "%DB600.DBD104"   /*机头B_B料浆料温度*/
/* 单面产能——地址 */
#define DAN_FACE_MAKE       "%DB600.DBD84"    /*单面产能*/
/* 双面产能——地址 */
#define SUANG_FACE_MAKE   "%DB600.DBD88"    /*双面产能*/


/*泵速闭环——地址*/
#define BENSPEEN_OPEN_SIGNAL_      "D19004"      /*泵速闭环开启信号*/
#define BENSPEEN_HEART_SIGNAL      "D19630"      /*泵速闭环心跳信号*/
#define BENSPEEN_ADJUST_NUM         "D3518"       /*泵速调节量*/
#define BENSPEEN_ADJUST_UPDATE    "D3516"       /*泵速调节更新标志*/

/*模头纠偏闭环——地址*/
#define MACHINHEAD_A_SKEWING_OPEN     "D7774"      /*机头A_膜头纠偏闭环开启信号*/
#define MACHINHEAD_A_WORK_STATE         "D7766"      /*机头A_工作状态信号*/
#define MACHINHEAD_A_OFFSET                  "D7846"      /*机头A_纠偏偏移量*/
#define MACHINHEAD_A_UPDATE_FLAG         "D9204"      /*机头A_纠偏刷新标志位*/

#define MACHINHEAD_B_SKEWING_OPEN     "D8774"       /*机头B_膜头纠偏闭环开启信号*/
#define MACHINHEAD_B_WORK_STATE         "D8766"       /*机头B_工作状态信号*/
#define MACHINHEAD_B_OFFSET                  "D8848"      /*机头B_纠偏偏移量*/
#define MACHINHEAD_B_UPDATE_FLAG        "D9208"       /*机头B_纠偏刷新标志位*/

/*模头刀距闭环——地址*/
#define MACHINHEAD_A_KNIFETOOL_OPEN      "D19018"   /*机头A_刀距闭环开启信号*/
#define MACHINHEAD_A_KNIFEADJUST_FLAG   "D7120"     /*机头A_刀距调节量标示*/
#define MACHINHEAD_A_LEFT_ADJUST            "D7116"     /*机头A_左调刀调节量*/
#define MACHINHEAD_A_RIGHT_ADJUST         "D7118"      /*机头A_右调刀调节量*/
#define MACHINHEAD_A_KNIFE_HEART           "D9210"      /*机头A_心跳信号*/

#define MACHINHEAD_B_KNIFETOOL_OPEN      "D19318"    /*机头B_刀距闭环开启信号*/
#define MACHINHEAD_B_KNIFEADJUST_FLAG   "D7520"      /*机头B_刀距调节量标示*/
#define MACHINHEAD_B_LEFT_ADJUST            "D7516"      /*机头B_左调刀调节量*/
#define MACHINHEAD_B_RIGHT_ADJUST         "D7518"      /*机头B_右调刀调节量*/
#define MACHINHEAD_B_KNIFE_HEART           "D9212"      /*机头B_心跳信号*/


namespace Ui {
class network;
}

class network : public QWidget
{
    Q_OBJECT

public:
    explicit network(QWidget *parent = nullptr);
    ~network();

    /**/
       bool Client_Tcp_Connect_Face(void);
       bool Client_Tcp_Connect_MachinHead_A(void);
       bool Client_Tcp_Connect_MachinHead_B(void);
       bool Client_Tcp_Connect_CCD(void);

       int Client_FACE_Send_Byte(uint8_t ByteData);
       int Client_FACE_Send_Buffer(uint8_t *BufferData, uint8_t count);
       int Client_FACE_Send_String(char *stringBuffer);

       int Client_MachinHead_A_Send_Byte(uint8_t ByteData);
       int Client_MachinHead_A_Send_Buffer(uint8_t *BufferData, uint8_t count);
       int Client_MachinHead_A_Send_String(char *stringBuffer);

       int Client_MachinHead_B_Send_Byte(uint8_t ByteData);
       int Client_MachinHead_B_Send_Buffer(uint8_t *BufferData, uint8_t count);
       int Client_MachinHead_B_Send_String(char *stringBuffer);

       int Client_CCD_Send_Byte(uint8_t ByteData);
       int Client_CCD_Send_Buffer(uint8_t *BufferData, uint8_t count);
       int Client_CCD_Send_String(char *stringBuffer);


       bool readData(void)
       {
            QByteArray byteArray = face_Socket->readAll();   /*读取所有数据*/
//                   QByteArray byteArray = face_Socket->readLine(0);   /*读取一行数据*/
//                    byteArray = byteArray.trimmed();                           /*去掉换行字符*/

           if( byteArray != NULL )     /*正常接收数据*/
           {
               const char* cStr = byteArray.data();         /*数据格式转换*/

               sqlite->ClearFree_CCD_Table();    /*清空CCD表格*/

               sqlite->InsertInto_CCD_Table(cStr); /*插入数据到表格*/

               aiPython->ccd_updata_TableCSV();  /*生成CCD CSV表格*/

               face_Socket->write(cStr);   /*向服务器发送数据*/

                          return 1;
           }
           else
           {
                   /*没数据可供读取或者发生了错误*/
                   return 0;
           }

       }

       void disconnectedFromServer(void)
       {
           // std::count << "Disconnected from server." << std::end;
           qDebug() << "face server connect off";
       }

       void displayError(QAbstractSocket::SocketError socketError)
       {
           //  std::count << "Error:" << tcpSocket->errorString().toStdString() << std::end;
            qDebug() << "face server connect error";
       }


       void readData2(void)
       {
           QByteArray byteArray = ccd_Socket->readAll();
           const char* cStr = byteArray.data();
           ccd_Socket->write(cStr);
       }

       void disconnectedFromServer2(void)
       {
           // std::count << "Disconnected from server." << std::end;
           qDebug() << "ccd server connect off";
       }

       void displayError2(QAbstractSocket::SocketError socketError)
       {
           //  std::count << "Error:" << tcpSocket->errorString().toStdString() << std::end;
            qDebug() << "ccd server connect error";
       }


       void readData3(void)
       {
           QByteArray byteArray = machineHead_A_Socket->readAll();
           const char* cStr = byteArray.data();
           machineHead_A_Socket->write(cStr);
       }

       void disconnectedFromServer3(void)
       {
           // std::count << "Disconnected from server." << std::end;
           qDebug() << "machineHead_A server connect off";
       }

       void displayError3(QAbstractSocket::SocketError socketError)
       {
           //  std::count << "Error:" << tcpSocket->errorString().toStdString() << std::end;
            qDebug() << "machineHead_A server connect error";
       }


       void readData4(void)
       {
           QByteArray byteArray = machineHead_B_Socket->readAll();
           const char* cStr = byteArray.data();
           machineHead_B_Socket->write(cStr);
       }

       void disconnectedFromServer4(void)
       {
           // std::count << "Disconnected from server." << std::end;
           qDebug() << "machineHead_B server connect off";
       }

       void displayError4(QAbstractSocket::SocketError socketError)
       {
           //  std::count << "Error:" << tcpSocket->errorString().toStdString() << std::end;
            qDebug() << "machineHead_B server connect error";
       }

        QByteArray ccd_Array;                   /*CCD接收缓冲区*/
        QByteArray machinHeadA_Array;    /*机头A接收缓冲区*/
        QByteArray machinHeadB_Array;    /*机头B接收缓冲区*/
        QByteArray face_Array;                  /*面密度仪接收缓冲区*/

        const char* ccd_TxBuffer;               /*CCD发送缓冲区*/
        const char* face_TxBuffer;              /*面密度仪发送缓冲区*/
        const char* machinheadA_TxBuffer; /*机头A发送缓冲区*/
        const char* machinheadB_TxBuffer; /*机头B发送缓冲区*/

        mySql *sqlite;                         /*sqlite tpye*/
        ai_python *aiPython;

private:
    Ui::network *ui;

          QTcpServer  *tcpServer;   /*TCP 服务器*/
          QTcpSocket  *tcpSocket;  /*TCP 客户端 */
          QUdpSocket *udpSocket; /*UDP 客户端 服务器*/

          QTcpSocket  *face_Socket;    /*面密度仪 SOCKET*/
          QTcpSocket  *ccd_Socket;    /*CCD SOCKET*/
          QTcpSocket  *machineHead_A_Socket;   /*机头A SOCKET*/
          QTcpSocket  *machineHead_B_Socket;   /*机头B SOCKET*/

};

#endif // NETWORK_H
