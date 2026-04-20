#include "network.h"
#include "ui_network.h"

/*添加注释*/
__uint8_t  openStart = 0;   /*CAN发送标志位*/
/**/

network::network(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::network)
{
    ui->setupUi(this);

   /*Network*/
      Client_Tcp_Connect_Face();
      Client_Tcp_Connect_CCD();
      Client_Tcp_Connect_MachinHead_A();
      Client_Tcp_Connect_MachinHead_B();
}

network::~network()
{
    delete ui;
}


/**/
bool network::Client_Tcp_Connect_Face(void)
{
      face_Socket = new QTcpSocket(this); /*TCP 客户端 */
      connect(face_Socket,  &QTcpSocket::readyRead,  this,  &network::readData);
      connect(face_Socket,  &QTcpSocket::disconnected, this, &network::disconnectedFromServer);
      connect(face_Socket, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &network::displayError);
//      face_Socket->connectToHost("192.168.1.100", 31416);
      face_Socket->connectToHost("192.168.5.50", 4);

      return 0;
}

int network::Client_FACE_Send_Byte(uint8_t ByteData)
{
         char str[1];
         sprintf(str,"%x", ByteData);
         face_Socket->write(str);    /* 向服务器发送数据 */
         return 0;
}

int network::Client_FACE_Send_Buffer(uint8_t *BufferData, uint8_t count)
{
      uint8_t i;
      char str[1];
      for(i=0; i<count; i++)
      {
           sprintf(str,"%x", BufferData[i]);
           face_Socket->write(str);    /* 向服务器发送数据 */
           face_Socket->write(" ");    /* 向服务器发送数据 */
      }
      return 0;
}

int network::Client_FACE_Send_String(char *stringBuffer)
{
      face_Socket->write(stringBuffer);
      return 0;
}


/**/
bool network::Client_Tcp_Connect_CCD(void)
{
       ccd_Socket = new QTcpSocket(this); /*TCP 客户端 */
       connect(ccd_Socket,  &QTcpSocket::readyRead,  this,  &network::readData2);
       connect(ccd_Socket,  &QTcpSocket::disconnected, this, &network::disconnectedFromServer2);
       connect(ccd_Socket, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &network::displayError2);
       ccd_Socket->connectToHost("127.0.0.1", 7899);

       return 0;
}

int network::Client_CCD_Send_Byte(uint8_t ByteData)
{
         char str[1];
         sprintf(str,"%x", ByteData);
         ccd_Socket->write(str);    /* 向服务器发送数据 */
         return 0;
}

int network::Client_CCD_Send_Buffer(uint8_t *BufferData, uint8_t count)
{
      uint8_t i;
      char str[1];
      for(i=0; i<count; i++)
      {
           sprintf(str,"%x", BufferData[i]);
           ccd_Socket->write(str);    /* 向服务器发送数据 */
           ccd_Socket->write(" ");    /* 向服务器发送数据 */
      }
      return 0;
}

int network::Client_CCD_Send_String(char *stringBuffer)
{
      ccd_Socket->write(stringBuffer);
      return 0;
}


/**/
bool network::Client_Tcp_Connect_MachinHead_A(void)
{
      machineHead_A_Socket = new QTcpSocket(this); /*TCP 客户端 */
      connect(machineHead_A_Socket,  &QTcpSocket::readyRead,  this,  &network::readData3);
      connect(machineHead_A_Socket,  &QTcpSocket::disconnected, this, &network::disconnectedFromServer3);
      connect(machineHead_A_Socket, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &network::displayError3);
      machineHead_A_Socket->connectToHost("192.168.0.1", 102);

      return 0;
}

int network::Client_MachinHead_A_Send_Byte(uint8_t ByteData)
{
         char str[1];
         sprintf(str,"%x", ByteData);
         machineHead_A_Socket->write(str);    /* 向服务器发送数据 */
         return 0;
}

int network::Client_MachinHead_A_Send_Buffer(uint8_t *BufferData, uint8_t count)
{
      uint8_t i;
      char str[1];
      for(i=0; i<count; i++)
      {
           sprintf(str,"%x", BufferData[i]);
           machineHead_A_Socket->write(str);    /* 向服务器发送数据 */
           machineHead_A_Socket->write(" ");    /* 向服务器发送数据 */
      }
      return 0;
}

int network::Client_MachinHead_A_Send_String(char *stringBuffer)
{
      machineHead_A_Socket->write(stringBuffer);
      return 0;
}


bool network::Client_Tcp_Connect_MachinHead_B(void)
{
       machineHead_B_Socket = new QTcpSocket(this); /*TCP 客户端 */
       connect(machineHead_B_Socket,  &QTcpSocket::readyRead,  this,  &network::readData4);
       connect(machineHead_B_Socket,  &QTcpSocket::disconnected, this, &network::disconnectedFromServer4);
       connect(machineHead_B_Socket, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &network::displayError4);
       machineHead_B_Socket->connectToHost("192.168.0.10", 102);
       if(machineHead_B_Socket->waitForConnected(1))
           return 1;    /* 成功返回1 */
       else
           return 0;    /* 失败返回0 */
}

int network::Client_MachinHead_B_Send_Byte(uint8_t ByteData)
{
         char str[1];
         sprintf(str,"%x", ByteData);
         machineHead_B_Socket->write(str);    /* 向服务器发送数据 */
         return 0;
}

int network::Client_MachinHead_B_Send_Buffer(uint8_t *BufferData, uint8_t count)
{
      uint8_t i;
      char str[1];
      for(i=0; i<count; i++)
      {
           sprintf(str,"%x", BufferData[i]);
           machineHead_B_Socket->write(str);    /* 向服务器发送数据 */
           machineHead_B_Socket->write(" ");    /* 向服务器发送数据 */
      }
      return 0;
}

int network::Client_MachinHead_B_Send_String(char *stringBuffer)
{
      machineHead_B_Socket->write(stringBuffer);
      return 0;
}


