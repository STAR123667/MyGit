#include "mainwindow.h"
#include "ui_mainwindow.h"

#include  <fcntl.h>
#include  <unistd.h>
#include  <termios.h>
#include  <iostream>
#include  <cstring>

#include  <QFile>
#include  <QTextStream>
#include  <QDir>
#include  <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(1000);//每秒更新一次时间

    /****  程序开始，执行页面所有对应主函数   ****/

    Page_ManualOperation = new manualOperation(this);/**/
    Page_HomePage = new homepage(this);
    Page_DataFace =new dataface(this);
    Page_ConfigManagement = new configurationmanagement(this);
    Page_DataManagement = new datamanagement(this);
    Page_SystemManagement = new systemmanagement(this);
    Page_WorkManagement = new workmanagement(this);
    Page_PageControl = new PageControl(this);

    Page_NetWork = new network(this);  /*为了程序开始执行时，自动连接到服务器，在此调用实例对象执行对应的类函数*/
    Page_sqlist = new mySql();     /*为了程序开始执行时，数据库连接和创建表格，在此调用实例对象执行对应的类函数*/


    /****   隐藏相应其他子页面，主页保存显示  ****/

    Page_ManualOperation->hide();
    Page_DataFace->hide();
    Page_ConfigManagement->hide();
    Page_DataManagement->hide();
    Page_SystemManagement->hide();
    Page_WorkManagement->hide();
    Page_NetWork->hide();
    Page_PageControl->hide();

    Page_HomePage->move(5, 35);
    Page_HomePage->show();


    /**/
    ui->tabWidget->setCurrentIndex(6);
    /**/
    ui->label_start->hide();
    ui->label_close->show();

    ui->label_start2->hide();
    ui->label_close2->show();

    ui->label_start3->hide();
    ui->label_close3->show();

    ui->label_start_CAN->hide();
    ui->label_close_CAN->show();

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateTime()
{
        QString yearTime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
        QString currentTime = QDateTime::currentDateTime().toString("hh:mm:ss");
        ui->t_year_label->setText(yearTime);
        ui->t_date_label->setText(currentTime);
}




void MainWindow::on_T_OPEN_valueChanged(int value)
{
    if(!value)
    {
                 ui->T_OPEN->setStyleSheet(
                       "QSlider::groove:horizontal{ border: none; background-color: rgb(255,0,0); border-radius: 10px; }"
                       "QSlider::handle:horizontal{ width: 20px; height: 30px; background-color: white; border-radius:10px; }"
                    );

               ui->label_start->hide();
               ui->label_close->show();
    }
    else
    {
                 ui->T_OPEN->setStyleSheet(
                           "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 10px; }"
                           "QSlider::handle:horizontal{ width: 20px; height: 30px; background-color: white; border-radius:10px; }"
                        );

                 ui->label_start->show();
                 ui->label_close->hide();
    }
}

void MainWindow::on_BS_OPEN_valueChanged(int value)
{
    if(!value)
    {
        ui->BS_OPEN->setStyleSheet(
                       "QSlider::groove:horizontal{ border: none; background-color: rgb(255,0,0); border-radius: 10px; }"
                       "QSlider::handle:horizontal{ width: 20px; height: 30px; background-color: white; border-radius:10px; }"
                    );

        ui->label_start2->hide();
        ui->label_close2->show();
    }
    else
    {
        ui->BS_OPEN->setStyleSheet(
                       "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 10px; }"
                       "QSlider::handle:horizontal{ width: 20px; height: 30px; background-color: white; border-radius:10px; }"
                    );

             ui->label_start2->show();
             ui->label_close2->hide();
    }
}

void MainWindow::on_CAP_OPEN_valueChanged(int value)
{
    if(!value)
    {
        ui->CAP_OPEN->setStyleSheet(
                       "QSlider::groove:horizontal{ border: none; background-color: rgb(255,0,0); border-radius: 10px; }"
                       "QSlider::handle:horizontal{ width: 20px; height: 30px; background-color: white; border-radius:10px; }"
                    );

        ui->label_start3->hide();
        ui->label_close3->show();
    }
    else
    {
        ui->CAP_OPEN->setStyleSheet(
                       "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 10px; }"
                       "QSlider::handle:horizontal{ width: 20px; height: 30px; background-color: white; border-radius:10px; }"
                    );

        ui->label_start3->show();
        ui->label_close3->hide();
    }

}

void MainWindow::on_tabWidget_currentChanged(int index)
{

        Page_HomePage->hide();
        Page_ManualOperation->hide();
        Page_DataFace->hide();
        Page_ConfigManagement->hide();
        Page_DataManagement->hide();
        Page_SystemManagement->hide();
        Page_WorkManagement->hide();
       // Page_PageControl->hide();

      switch(index){

          case 0:{

          Page_WorkManagement->move(5,40);
          Page_WorkManagement->show();

          // Page_PageControl->move(5, 40);
         //  Page_PageControl->show();

      }break;
          case 1:{

           Page_SystemManagement->move(5,40);
           Page_SystemManagement->show();

      }break;
          case 2:{

          Page_DataManagement->move(5,40);
          Page_DataManagement->show();

      }break;
          case 3:{

          Page_ConfigManagement->move(5,40);
          Page_ConfigManagement->show();

      }break;
          case 4:{

          Page_DataFace->move(5,40);
          Page_DataFace->show();

      }break;
          case 5:{

           Page_ManualOperation->move(5, 40);
           Page_ManualOperation->show();

          }
          break;
          case 6:{

           Page_HomePage->move(5, 35);
           Page_HomePage->show();

      }break;
          default:{}break;

}
}


uint8_t openStart;

void MainWindow::on_CAN_OPEN_valueChanged(int value)
{

    openStart = 0;

    if(!value)
    {
        CAN_Thread->closeDevice();

        ui->CAN_OPEN->setStyleSheet(
                       "QSlider::groove:horizontal{ border: none; background-color: rgb(255,0,0); border-radius: 10px; }"
                       "QSlider::handle:horizontal{ width: 20px; height: 30px; background-color: white; border-radius:10px; }"
                    );

               ui->label_start_CAN->hide();
               ui->label_close_CAN->show();

               ui->label_CAN->setText("控制盒未连接");
    }
    else
    {
           if(CAN_Thread->openDevice(4, 0, 500))
           {
               CAN_Thread->initCAN();
               CAN_Thread->startCAN();
               ui->CAN_OPEN->setStyleSheet(
                              "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 10px; }"
                              "QSlider::handle:horizontal{ width: 20px; height: 30px; background-color: white; border-radius:10px; }"
                           );

                ui->label_start_CAN->show();
                ui->label_close_CAN->hide();

                ui->label_CAN->setText("控制盒连接成功");

                openStart = 1;
           }
           else
           {
               CAN_Thread->closeDevice();
               ui->CAN_OPEN->setStyleSheet(
                              "QSlider::groove:horizontal{ border: none; background-color: rgb(255,0,0); border-radius: 10px; }"
                              "QSlider::handle:horizontal{ width: 20px; height: 30px; background-color: white; border-radius:10px; }"
                           );

               ui->label_start_CAN->hide();
               ui->label_close_CAN->show();

               ui->label_CAN->setText("控制盒连接失败");
           }

    }

}





