#include "manualoperation.h"
#include "ui_manualoperation.h"

#include <QStringListModel>
#include <QListView>
#include <QStandardItemModel>

manualOperation::manualOperation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::manualOperation)
{
    ui->setupUi(this);
    on_SelectMode_Button1_clicked();/*默认单膜区模式*/
    on_pushButton_modeArae1_clicked();/*默认膜区1*/

    ui->label_heard->show();
    ui->label_autor->hide();

    ui->label_heard2->show();
    ui->label_autor2->hide();

    ui->label_heard3->show();
    ui->label_autor3->hide();

    ui->label_close->show();
    ui->label_open->hide();


    ui->stackedWidget_onlymode->setCurrentIndex(0);
    ui->stackedWidget_allmode->setCurrentIndex(0);
    ui->stackedWidget_hightmode->setCurrentIndex(0);

     FaceReal_DataChart() ;             /*面密度仪实时数据*/
     //FaceReal_TendencyChart();       /*面密度仪趋势图*/

     FaceReal_DataChart2();               /*面密度仪实时数据*/
   //FaceReal_TendencyChart2();       /*面密度仪趋势图*/

     FaceReal_DataChart3();               /*面密度仪实时数据*/
   //FaceReal_TendencyChart3();       /*面密度仪趋势图*/
}


manualOperation::~manualOperation()
{
    delete ui;
}


void manualOperation::on_SelectMode_Button1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->SelectMode_Button1->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(255, 255, 255);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(255, 255, 255);}"
                );
    ui->SelectMode_Button2->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(255, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(0, 0, 0);}"
                );
    ui->SelectMode_Button3->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(255, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(0, 0, 0);}"
                );
    ui->SelectMode_Button4->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(255, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(0, 0, 0);}"
                );
}

void manualOperation::on_SelectMode_Button2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->SelectMode_Button1->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(255, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(0, 0, 0);}"
                                );
    ui->SelectMode_Button2->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(255, 255, 255);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(255, 255, 255);}"
                );
    ui->SelectMode_Button3->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(255, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(0, 0, 0);}"
                );
    ui->SelectMode_Button4->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(255, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(0, 0, 0);}"
                );
}
void manualOperation::on_SelectMode_Button3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->SelectMode_Button1->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(255, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(0, 0, 0);}"
                                );
    ui->SelectMode_Button2->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(255, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                );
    ui->SelectMode_Button3->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(255, 255, 255);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(255, 255, 255);}"
                );
    ui->SelectMode_Button4->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(255, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(0, 0, 0);}"
                );
}
void manualOperation::on_SelectMode_Button4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->SelectMode_Button1->setStyleSheet(
                "QPushButton {"
                     "background-color: rgb(255, 255, 255);"
                     "color: rgb(0, 0, 0);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(0, 0, 0);}"
                );
    ui->SelectMode_Button2->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(255, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(0, 0, 0);}"
                );
    ui->SelectMode_Button3->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(255, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(0, 0, 0);}"
                );
    ui->SelectMode_Button4->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(255, 255, 255);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(255, 255, 255);}"
                );
}


/*motor stie adjust*/
void manualOperation::on_motor3_add_button_pressed()
{
     if(!ui->motor3_open_button->value())
      return;
     device_typedef.WString = ui->motor3_adj->text();
     device_typedef.Wint = device_typedef.WString.toInt();
     device_typedef.Wint +=1;
     if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
     device_typedef.Motor_AdjSite[2] = device_typedef.Wint;/*slave data*/
     device_typedef.WString.setNum(device_typedef.Wint);
     ui->motor3_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor3_sub_button_pressed()
{
    if(!ui->motor3_open_button->value())
     return;
    device_typedef.WString = ui->motor3_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[2] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor3_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor4_add_button_pressed()
{
    if(!ui->motor4_open_button->value())
     return;
    device_typedef.WString = ui->motor4_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
     device_typedef.Motor_AdjSite[3] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor4_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor4_sub_button_released()
{
    if(!ui->motor4_open_button->value())
     return;
    device_typedef.WString = ui->motor4_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[3] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor4_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor5_add_button_pressed()
{
    if(!ui->motor5_open_button->value())
     return;
    device_typedef.WString = ui->motor5_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[4] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor5_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor5_sub_button_pressed()
{
    if(!ui->motor5_open_button->value())
     return;
    device_typedef.WString = ui->motor5_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[4] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor5_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor6_add_button_pressed()
{
    if(!ui->motor6_open_button->value())
     return;
    device_typedef.WString = ui->motor6_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[5] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor6_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor6_sub_button_pressed()
{
    if(!ui->motor6_open_button->value())
     return;
    device_typedef.WString = ui->motor6_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[5] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor6_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor7_add_button_pressed()
{
    if(!ui->motor7_open_button->value())
     return;
    device_typedef.WString = ui->motor7_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[6] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor7_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor7_sub_button_pressed()
{
    if(!ui->motor7_open_button->value())
     return;
    device_typedef.WString = ui->motor7_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[6] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor7_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor8_add_button_pressed()
{
    if(!ui->motor8_open_button->value())
     return;
    device_typedef.WString = ui->motor8_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[7] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor8_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor8_sub_button_pressed()
{
    if(!ui->motor8_open_button->value())
     return;
    device_typedef.WString = ui->motor8_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[7] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor8_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor9_add_button_pressed()
{
    if(!ui->motor9_open_button->value())
     return;
    device_typedef.WString = ui->motor9_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[8] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor9_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor9_sub_button_pressed()
{
    if(!ui->motor9_open_button->value())
     return;
    device_typedef.WString = ui->motor9_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[8] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor9_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor10_add_button_pressed()
{
    if(!ui->motor10_open_button->value())
     return;
    device_typedef.WString = ui->motor10_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[9] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor10_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor10_sub_button_pressed()
{
    if(!ui->motor10_open_button->value())
     return;
    device_typedef.WString = ui->motor10_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[9] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor10_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor11_add_button_pressed()
{
    if(!ui->motor11_open_button->value())
     return;
    device_typedef.WString = ui->motor11_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[10] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor11_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor11_sub_button_pressed()
{
    if(!ui->motor11_open_button->value())
     return;
    device_typedef.WString = ui->motor11_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[10] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor11_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor12_add_button_pressed()
{
    if(!ui->motor12_open_button->value())
     return;
    device_typedef.WString = ui->motor12_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[11] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor12_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor12_sub_button_pressed()
{
    if(!ui->motor12_open_button->value())
     return;
    device_typedef.WString = ui->motor12_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[11] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor12_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor13_add_button_pressed()
{
    if(!ui->motor13_open_button->value())
     return;
    device_typedef.WString = ui->motor13_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[12] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor13_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor13_sub_button_pressed()
{
    if(!ui->motor13_open_button->value())
     return;
    device_typedef.WString = ui->motor13_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[12] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor13_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor18_add_button_pressed()
{
    if(!ui->motor18_open_button->value())
     return;
    device_typedef.WString = ui->motor18_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[17] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor18_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor18_sub_button_pressed()
{
    if(!ui->motor18_open_button->value())
     return;
    device_typedef.WString = ui->motor18_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[17] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor18_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor19_add_button_pressed()
{
    if(!ui->motor19_open_button->value())
     return;
    device_typedef.WString = ui->motor19_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[18] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor19_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor19_sub_button_pressed()
{
    if(!ui->motor19_open_button->value())
     return;
    device_typedef.WString = ui->motor19_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[18] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor19_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor20_add_button_pressed()
{
    if(!ui->motor20_open_button->value())
     return;
    device_typedef.WString = ui->motor20_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[19] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor20_adj->setText(device_typedef.WString);
}

void manualOperation::on_motor20_sub_button_pressed()
{
    if(!ui->motor20_open_button->value())
     return;
    device_typedef.WString = ui->motor20_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[19] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor20_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor21_add_button_pressed()
{
    if(!ui->motor21_open_button->value())
     return;
    device_typedef.WString = ui->motor21_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[20] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor21_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor21_sub_button_pressed()
{
    if(!ui->motor21_open_button->value())
     return;
    device_typedef.WString = ui->motor21_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[20] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor21_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor22_add_button_pressed()
{
    if(!ui->motor22_open_button->value())
     return;
    device_typedef.WString = ui->motor22_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[21] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor22_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor22_sub_button_pressed()
{
    if(!ui->motor22_open_button->value())
     return;
    device_typedef.WString = ui->motor22_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[21] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor22_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor23_add_button_pressed()
{
    if(!ui->motor23_open_button->value())
     return;
    device_typedef.WString = ui->motor23_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[22] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor23_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor23_sub_button_pressed()
{
    if(!ui->motor23_open_button->value())
     return;
    device_typedef.WString = ui->motor23_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[22] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor23_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor24_add_button_pressed()
{
    if(!ui->motor24_open_button->value())
     return;
    device_typedef.WString = ui->motor24_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[23] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor24_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor24_sub_button_pressed()
{
    if(!ui->motor24_open_button->value())
     return;
    device_typedef.WString = ui->motor24_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[23] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor24_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor25_add_button_pressed()
{
    if(!ui->motor25_open_button->value())
     return;
    device_typedef.WString = ui->motor25_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[24] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor25_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor25_sub_button_pressed()
{
    if(!ui->motor25_open_button->value())
     return;
    device_typedef.WString = ui->motor25_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[24] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor25_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor26_add_button_pressed()
{
    if(!ui->motor26_open_button->value())
     return;
    device_typedef.WString = ui->motor26_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[25] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor26_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor26_sub_button_pressed()
{
    if(!ui->motor26_open_button->value())
     return;
    device_typedef.WString = ui->motor26_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[25] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor26_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor27_add_button_pressed()
{
    if(!ui->motor27_open_button->value())
     return;
    device_typedef.WString = ui->motor27_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[26] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor27_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor27_sub_button_pressed()
{
    if(!ui->motor27_open_button->value())
     return;
    device_typedef.WString = ui->motor27_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[26] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor27_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor28_add_button_pressed()
{
    if(!ui->motor28_open_button->value())
     return;
    device_typedef.WString = ui->motor28_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[27] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor28_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor28_sub_button_pressed()
{
    if(!ui->motor28_open_button->value())
     return;
    device_typedef.WString = ui->motor28_adj->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[27] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor28_adj->setText(device_typedef.WString);
}

/*单区模式写入位置*/
void manualOperation::on_pushButton_siteWrite_pressed()
{
     //int currentIndex =  ui->stackedWidget->currentIndex();

      if(!openStart)
          CAN_WarningMessage_Show();
      else
      {

           //if(currentIndex == 0)
        //   {
                 int dmodePage =  ui->stackedWidget2->currentIndex();
                  OnlyModeSend(dmodePage);
           //}
      }
}


void manualOperation::CAN_WarningMessage_Show(void)
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("提示");
    msgBox.setText(tr("控制盒未打开!"));
    msgBox.setSizeIncrement(200,100);
    msgBox.exec();
}


void manualOperation::OnlyModeSend(uint8_t Area)
{
    uint8_t dwRel=0;
    VCI_CAN_OBJ vco;
    uint8_t OneMode = 2;
    uint8_t TwoMode = 17;

    dwRel= Area ;

    switch(dwRel)
    {

        case 0:{

             for( ; OneMode<13; OneMode++)
             {
                vco.ID = MOTOR_ADDRESS_BASE_ID + (OneMode+1);
                vco.RemoteFlag = 0;
                vco.ExternFlag = 0;
                vco.DataLen = 8;

                vco.Data[0] =  device_typedef.Motor_AdjSite[OneMode] <<8;
                vco.Data[1] =  device_typedef.Motor_AdjSite[OneMode];
                vco.Data[2] = 0;
                vco.Data[3] = 0;
                vco.Data[4] = 0;
                vco.Data[5] = 0;
                vco.Data[6] = 0;
                vco.Data[7] = 0;

                VCI_Transmit(4,0,0,&vco,1);
            }

        } break;

        case 1:{

             for(; TwoMode<28; TwoMode++)
              {
                vco.ID =  MOTOR_ADDRESS_BASE_ID + (TwoMode+1);
                vco.RemoteFlag = 0;
                vco.ExternFlag = 0;
                vco.DataLen = 8;

                vco.Data[0] =  device_typedef.Motor_AdjSite[TwoMode] <<8;
                vco.Data[1] =  device_typedef.Motor_AdjSite[TwoMode];
                vco.Data[2] = 0;
                vco.Data[3] = 0;
                vco.Data[4] = 0;
                vco.Data[5] = 0;
                vco.Data[6] = 0;
                vco.Data[7] = 0;

                VCI_Transmit(4,0,0,&vco,1);
            }

       } break;

    }

         vco.ID = MOTOR_SYNC_MESSAGE_ID ;
         VCI_Transmit(4,0,0,&vco,1);

}


/*单区模式清零位置*/
void manualOperation::on_pushButton_clear_pressed()
{
    uint8_t count;

    for( count=2; count<13; count++ )
    {
        device_typedef.Motor_AdjSite[count]&=0;
    }
    device_typedef.WString = "0";
    ui->motor3_adj->setText(device_typedef.WString);
    ui->motor4_adj->setText(device_typedef.WString);
    ui->motor5_adj->setText(device_typedef.WString);
    ui->motor6_adj->setText(device_typedef.WString);
    ui->motor7_adj->setText(device_typedef.WString);
    ui->motor8_adj->setText(device_typedef.WString);
    ui->motor9_adj->setText(device_typedef.WString);
    ui->motor10_adj->setText(device_typedef.WString);
    ui->motor11_adj->setText(device_typedef.WString);
    ui->motor12_adj->setText(device_typedef.WString);
    ui->motor13_adj->setText(device_typedef.WString);

    for( count=17; count<28; count++ )
    {
        device_typedef.Motor_AdjSite[count]&=0;
    }
    device_typedef.WString = "0";
    ui->motor18_adj->setText(device_typedef.WString);
    ui->motor19_adj->setText(device_typedef.WString);
    ui->motor20_adj->setText(device_typedef.WString);
    ui->motor21_adj->setText(device_typedef.WString);
    ui->motor22_adj->setText(device_typedef.WString);
    ui->motor23_adj->setText(device_typedef.WString);
    ui->motor24_adj->setText(device_typedef.WString);
    ui->motor25_adj->setText(device_typedef.WString);
    ui->motor26_adj->setText(device_typedef.WString);
    ui->motor27_adj->setText(device_typedef.WString);
    ui->motor28_adj->setText(device_typedef.WString);
}


void manualOperation::on_motor18_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor18_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor18_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}

void manualOperation::on_motor19_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor19_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor19_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor20_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor20_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor20_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor21_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor21_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor21_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor22_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor22_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor22_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}

void manualOperation::on_motor23_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor23_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor23_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}



void manualOperation::on_motor24_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor24_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor24_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}
void manualOperation::on_motor25_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor25_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor25_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}
void manualOperation::on_motor26_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor26_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor26_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}
void manualOperation::on_motor27_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor27_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor27_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}
void manualOperation::on_motor28_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor28_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor28_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}



void manualOperation::on_motor3_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor3_open_button->setStyleSheet(
                       "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                       "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor3_open_button->setStyleSheet(
                       "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                       "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}

void manualOperation::on_motor4_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor4_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor4_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}
void manualOperation::on_motor5_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor5_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor5_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}
void manualOperation::on_motor6_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor6_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor6_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}
void manualOperation::on_motor7_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor7_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor7_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}
void manualOperation::on_motor8_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor8_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor8_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}
void manualOperation::on_motor9_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor9_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor9_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}
void manualOperation::on_motor10_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor10_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor10_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}
void manualOperation::on_motor11_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor11_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor11_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}
void manualOperation::on_motor12_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor12_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor12_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}
void manualOperation::on_motor13_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor13_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor13_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}





void manualOperation::on_pushButton_modeArae1_clicked()
{
     ui->stackedWidget2->setCurrentIndex(0);
     ui->pushButton_modeArae1->setStyleSheet(
                 "QPushButton {"
                                "background-color: rgb(0, 0, 160);"
                                "color: rgb(255, 255, 255);}"
                 "QPushButton:hover {"
                                "background-color: rgb(170, 255, 255);"
                                "color: rgb(0, 0, 0);}"
                 "QPushButton:pressed  {"
                                "background-color: rgb(0, 0, 160);"
                                "color: rgb(255, 255, 255);}"
                 );
     ui->pushButton_modeArae2->setStyleSheet(
                 "QPushButton {"
                     "background-color: rgb(255, 255, 255);"
                     "color: rgb(0, 0, 0);}"
                 "QPushButton:hover {"
                     "background-color: rgb(170, 255, 255);"
                     "color: rgb(0, 0, 0);}"
                 "QPushButton:pressed  {"
                     "background-color: rgb(0, 0, 160);"
                     "color: rgb(0, 0, 0);}"
                 );
}
void manualOperation::on_pushButton_modeArae2_clicked()
{
    ui->stackedWidget2->setCurrentIndex(1);
    ui->pushButton_modeArae1->setStyleSheet(
                "QPushButton {"
                    "background-color: rgb(255, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:hover {"
                    "background-color: rgb(170, 255, 255);"
                    "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                    "background-color: rgb(0, 0, 160);"
                    "color: rgb(0, 0, 0);}"
                );
    ui->pushButton_modeArae2->setStyleSheet(
                "QPushButton {"
                               "background-color: rgb(0, 0, 160);"
                               "color: rgb(255, 255, 255);}"
                "QPushButton:hover {"
                               "background-color: rgb(170, 255, 255);"
                               "color: rgb(0, 0, 0);}"
                "QPushButton:pressed  {"
                               "background-color: rgb(0, 0, 160);"
                               "color: rgb(255, 255, 255);}"
                );
}

/*zhidong*/
void manualOperation::on_all_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->motor3_open_button->setValue(false);
        ui->motor4_open_button->setValue(false);
        ui->motor5_open_button->setValue(false);
        ui->motor6_open_button->setValue(false);
        ui->motor7_open_button->setValue(false);
        ui->motor8_open_button->setValue(false);
        ui->motor9_open_button->setValue(false);
        ui->motor10_open_button->setValue(false);
        ui->motor11_open_button->setValue(false);
        ui->motor12_open_button->setValue(false);
        ui->motor13_open_button->setValue(false);

        ui->motor18_open_button->setValue(false);
        ui->motor19_open_button->setValue(false);
        ui->motor20_open_button->setValue(false);
        ui->motor21_open_button->setValue(false);
        ui->motor22_open_button->setValue(false);
        ui->motor23_open_button->setValue(false);
        ui->motor24_open_button->setValue(false);
        ui->motor25_open_button->setValue(false);
        ui->motor26_open_button->setValue(false);
        ui->motor27_open_button->setValue(false);
        ui->motor28_open_button->setValue(false);

        ui->all_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );

        ui->label_heard->show();
        ui->label_autor->hide();
    }
    else
    {
        ui->motor3_open_button->setValue(true);
        ui->motor4_open_button->setValue(true);
        ui->motor5_open_button->setValue(true);
        ui->motor6_open_button->setValue(true);
        ui->motor7_open_button->setValue(true);
        ui->motor8_open_button->setValue(true);
        ui->motor9_open_button->setValue(true);
        ui->motor10_open_button->setValue(true);
        ui->motor11_open_button->setValue(true);
        ui->motor12_open_button->setValue(true);
        ui->motor13_open_button->setValue(true);

        ui->motor18_open_button->setValue(true);
        ui->motor19_open_button->setValue(true);
        ui->motor20_open_button->setValue(true);
        ui->motor21_open_button->setValue(true);
        ui->motor22_open_button->setValue(true);
        ui->motor23_open_button->setValue(true);
        ui->motor24_open_button->setValue(true);
        ui->motor25_open_button->setValue(true);
        ui->motor26_open_button->setValue(true);
        ui->motor27_open_button->setValue(true);
        ui->motor28_open_button->setValue(true);

        ui->all_open_button->setStyleSheet("QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                                           "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );

        ui->label_heard->hide();
        ui->label_autor->show();

    }
}


void manualOperation::on_motor3_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor3_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor3_open_button2->setStyleSheet(
                       "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                       "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}

void manualOperation::on_motor4_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor4_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor4_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}




void manualOperation::on_motor5_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor5_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor5_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor6_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor6_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor6_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor7_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor7_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor7_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor8_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor8_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor8_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor9_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor9_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor9_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor10_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor10_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor10_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor11_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor11_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor11_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor12_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor12_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor12_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor13_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor13_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor13_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor18_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor18_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor18_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor19_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor19_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor19_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor20_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor20_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor20_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor21_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor21_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor21_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor22_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor22_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor22_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor23_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor23_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor23_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor24_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor24_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor24_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor25_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor25_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor25_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor26_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor26_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor26_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor27_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor27_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor27_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor28_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->motor28_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor28_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_all_open_button2_valueChanged(int value)
{
    if(!value)
    {
        ui->all_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
        ui->label_heard2->show();
        ui->label_autor2->hide();
    }
    else
    {
        ui->all_open_button2->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
        ui->label_heard2->hide();
        ui->label_autor2->show();
    }

    switch(value)
    {
    case 0:{

           ui->motor3_open_button2->setValue(false);
           ui->motor4_open_button2->setValue(false);
           ui->motor5_open_button2->setValue(false);
           ui->motor6_open_button2->setValue(false);
           ui->motor7_open_button2->setValue(false);
           ui->motor8_open_button2->setValue(false);
           ui->motor9_open_button2->setValue(false);
           ui->motor10_open_button2->setValue(false);
           ui->motor11_open_button2->setValue(false);
           ui->motor12_open_button2->setValue(false);
           ui->motor13_open_button2->setValue(false);

           ui->motor18_open_button2->setValue(false);
           ui->motor19_open_button2->setValue(false);
           ui->motor20_open_button2->setValue(false);
           ui->motor21_open_button2->setValue(false);
           ui->motor22_open_button2->setValue(false);
           ui->motor23_open_button2->setValue(false);
           ui->motor24_open_button2->setValue(false);
           ui->motor25_open_button2->setValue(false);
           ui->motor26_open_button2->setValue(false);
           ui->motor27_open_button2->setValue(false);
           ui->motor28_open_button2->setValue(false);

    }break;
    case 1:{

            ui->motor3_open_button2->setValue(true);
            ui->motor4_open_button2->setValue(true);
            ui->motor5_open_button2->setValue(true);
            ui->motor6_open_button2->setValue(true);
            ui->motor7_open_button2->setValue(true);
            ui->motor8_open_button2->setValue(true);
            ui->motor9_open_button2->setValue(true);
            ui->motor10_open_button2->setValue(true);
            ui->motor11_open_button2->setValue(true);
            ui->motor12_open_button2->setValue(true);
            ui->motor13_open_button2->setValue(true);

            ui->motor18_open_button2->setValue(true);
            ui->motor19_open_button2->setValue(true);
            ui->motor20_open_button2->setValue(true);
            ui->motor21_open_button2->setValue(true);
            ui->motor22_open_button2->setValue(true);
            ui->motor23_open_button2->setValue(true);
            ui->motor24_open_button2->setValue(true);
            ui->motor25_open_button2->setValue(true);
            ui->motor26_open_button2->setValue(true);
            ui->motor27_open_button2->setValue(true);
            ui->motor28_open_button2->setValue(true);

    }break;
    default:{}break;
    }


}




void manualOperation::on_motor3_add_button2_pressed()
{
         if(!ui->motor3_open_button2->value())
         return;
         device_typedef.WString = ui->motor3_adj2->text();
         device_typedef.Wint = device_typedef.WString.toInt();
         device_typedef.Wint +=1;
         if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
         device_typedef.Motor_AdjSite[2] = device_typedef.Wint;
         device_typedef.WString.setNum(device_typedef.Wint);
         ui->motor3_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor3_sub_button2_pressed()
{
        if(!ui->motor3_open_button2->value())
        return;
        device_typedef.WString = ui->motor3_adj2->text();
        device_typedef.Wint = device_typedef.WString.toInt();
        device_typedef.Wint -=1;
        if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
        device_typedef.Motor_AdjSite[2] = device_typedef.Wint;
        device_typedef.WString.setNum(device_typedef.Wint);
        ui->motor3_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor4_add_button2_pressed()
{
       if(!ui->motor4_open_button2->value())
        return;
       device_typedef.WString = ui->motor4_adj2->text();
       device_typedef.Wint = device_typedef.WString.toInt();
       device_typedef.Wint +=1;
       if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
       device_typedef.Motor_AdjSite[3] = device_typedef.Wint;
       device_typedef.WString.setNum(device_typedef.Wint);
       ui->motor4_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor4_sub_button2_pressed()
{
         if(!ui->motor4_open_button2->value())
         return;
        device_typedef.WString = ui->motor4_adj2->text();
        device_typedef.Wint = device_typedef.WString.toInt();
        device_typedef.Wint -=1;
        if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
        device_typedef.Motor_AdjSite[3] = device_typedef.Wint;
        device_typedef.WString.setNum(device_typedef.Wint);
        ui->motor4_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor5_add_button2_pressed()
{
    if(!ui->motor5_open_button2->value())
     return;
       device_typedef.WString = ui->motor5_adj2->text();
       device_typedef.Wint = device_typedef.WString.toInt();
       device_typedef.Wint +=1;
       if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
       device_typedef.Motor_AdjSite[4] = device_typedef.Wint;
       device_typedef.WString.setNum(device_typedef.Wint);
       ui->motor5_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor5_sub_button2_pressed()
{
    if(!ui->motor5_open_button2->value())
     return;
        device_typedef.WString = ui->motor5_adj2->text();
        device_typedef.Wint = device_typedef.WString.toInt();
        device_typedef.Wint -=1;
        if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
        device_typedef.Motor_AdjSite[4] = device_typedef.Wint;
        device_typedef.WString.setNum(device_typedef.Wint);
        ui->motor5_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor6_add_button2_pressed()
{
    if(!ui->motor6_open_button2->value())
     return;
       device_typedef.WString = ui->motor6_adj2->text();
       device_typedef.Wint = device_typedef.WString.toInt();
       device_typedef.Wint +=1;
       if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
       device_typedef.Motor_AdjSite[5] = device_typedef.Wint;
       device_typedef.WString.setNum(device_typedef.Wint);
       ui->motor6_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor6_sub_button2_pressed()
{
    if(!ui->motor6_open_button2->value())
     return;
        device_typedef.WString = ui->motor6_adj2->text();
        device_typedef.Wint = device_typedef.WString.toInt();
        device_typedef.Wint -=1;
        if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
        device_typedef.Motor_AdjSite[5] = device_typedef.Wint;
        device_typedef.WString.setNum(device_typedef.Wint);
        ui->motor6_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor7_add_button2_pressed()
{
    if(!ui->motor7_open_button2->value())
     return;
       device_typedef.WString = ui->motor7_adj2->text();
       device_typedef.Wint = device_typedef.WString.toInt();
       device_typedef.Wint +=1;
       if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
       device_typedef.Motor_AdjSite[6] = device_typedef.Wint;
       device_typedef.WString.setNum(device_typedef.Wint);
       ui->motor7_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor7_sub_button2_pressed()
{
    if(!ui->motor7_open_button2->value())
     return;
        device_typedef.WString = ui->motor7_adj2->text();
        device_typedef.Wint = device_typedef.WString.toInt();
        device_typedef.Wint -=1;
        if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
        device_typedef.Motor_AdjSite[6] = device_typedef.Wint;
        device_typedef.WString.setNum(device_typedef.Wint);
        ui->motor7_adj2->setText(device_typedef.WString);
}

void manualOperation::on_motor8_add_button2_pressed()
{
    if(!ui->motor8_open_button2->value())
     return;
      device_typedef.WString = ui->motor8_adj2->text();
      device_typedef.Wint = device_typedef.WString.toInt();
      device_typedef.Wint +=1;
      if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
      device_typedef.Motor_AdjSite[7] = device_typedef.Wint;
      device_typedef.WString.setNum(device_typedef.Wint);
      ui->motor8_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor8_sub_button2_pressed()
{
    if(!ui->motor8_open_button2->value())
     return;
      device_typedef.WString = ui->motor8_adj2->text();
      device_typedef.Wint = device_typedef.WString.toInt();
      device_typedef.Wint -=1;
      if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
      device_typedef.Motor_AdjSite[7] = device_typedef.Wint;
      device_typedef.WString.setNum(device_typedef.Wint);
      ui->motor8_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor9_add_button2_pressed()
{
    if(!ui->motor9_open_button2->value())
     return;
    device_typedef.WString = ui->motor9_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[8] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor9_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor9_sub_button2_pressed()
{
    if(!ui->motor9_open_button2->value())
     return;
    device_typedef.WString = ui->motor9_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[8] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor9_adj2->setText(device_typedef.WString);
}



void manualOperation::on_motor10_add_button2_pressed()
{
    if(!ui->motor10_open_button2->value())
     return;
    device_typedef.WString = ui->motor10_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[9] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor10_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor10_sub_button2_pressed()
{
    if(!ui->motor10_open_button2->value())
     return;
    device_typedef.WString = ui->motor10_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[9] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor10_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor11_add_button2_pressed()
{
    if(!ui->motor11_open_button2->value())
     return;
    device_typedef.WString = ui->motor11_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[10] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor11_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor11_sub_button2_pressed()
{
    if(!ui->motor11_open_button2->value())
     return;
    device_typedef.WString = ui->motor11_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[10] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor11_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor12_add_button2_pressed()
{
    if(!ui->motor12_open_button2->value())
     return;
    device_typedef.WString = ui->motor12_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[11] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor12_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor12_sub_button2_pressed()
{
    if(!ui->motor12_open_button2->value())
     return;
    device_typedef.WString = ui->motor12_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[11] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor12_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor13_add_button2_pressed()
{
    if(!ui->motor13_open_button2->value())
     return;
    device_typedef.WString = ui->motor13_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[12] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor13_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor13_sub_button2_pressed()
{
    if(!ui->motor13_open_button2->value())
     return;
    device_typedef.WString = ui->motor13_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[12] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor13_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor18_add_button2_pressed()
{
    if(!ui->motor18_open_button2->value())
     return;
    device_typedef.WString = ui->motor18_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[17] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor18_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor18_sub_button2_pressed()
{
    if(!ui->motor18_open_button2->value())
     return;
    device_typedef.WString = ui->motor18_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[17] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor18_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor19_add_button2_pressed()
{
    if(!ui->motor19_open_button2->value())
     return;
    device_typedef.WString = ui->motor19_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[18] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor19_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor19_sub_button2_pressed()
{
    if(!ui->motor19_open_button2->value())
     return;
    device_typedef.WString = ui->motor19_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[18] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor19_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor20_add_button2_pressed()
{
    if(!ui->motor20_open_button2->value())
     return;
    device_typedef.WString = ui->motor20_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[19] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor20_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor20_sub_button2_pressed()
{
    if(!ui->motor20_open_button2->value())
     return;
    device_typedef.WString = ui->motor20_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[19] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor20_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor21_add_button2_pressed()
{
    if(!ui->motor21_open_button2->value())
     return;
    device_typedef.WString = ui->motor21_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[20] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor21_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor21_sub_button2_pressed()
{
    if(!ui->motor21_open_button2->value())
     return;
    device_typedef.WString = ui->motor21_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[20] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor21_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor22_add_button2_pressed()
{
    if(!ui->motor22_open_button2->value())
     return;
    device_typedef.WString = ui->motor22_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[21] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor22_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor22_sub_button2_pressed()
{
    if(!ui->motor22_open_button2->value())
     return;
    device_typedef.WString = ui->motor22_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[21] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor22_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor23_add_button2_pressed()
{
    if(!ui->motor23_open_button2->value())
     return;
    device_typedef.WString = ui->motor23_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[22] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor23_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor23_sub_button2_pressed()
{
    if(!ui->motor23_open_button2->value())
     return;
    device_typedef.WString = ui->motor23_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[22] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor23_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor24_add_button2_pressed()
{
    if(!ui->motor24_open_button2->value())
     return;
    device_typedef.WString = ui->motor24_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[23] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor24_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor24_sub_button2_pressed()
{
    if(!ui->motor24_open_button2->value())
     return;
    device_typedef.WString = ui->motor24_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[23] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor24_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor25_add_button2_pressed()
{
    if(!ui->motor25_open_button2->value())
     return;
    device_typedef.WString = ui->motor25_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[24] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor25_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor25_sub_button2_pressed()
{
    if(!ui->motor25_open_button2->value())
     return;
    device_typedef.WString = ui->motor25_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[24] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor25_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor26_add_button2_pressed()
{
    if(!ui->motor26_open_button2->value())
     return;
    device_typedef.WString = ui->motor26_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[25] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor26_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor26_sub_button2_pressed()
{
    if(!ui->motor26_open_button2->value())
     return;
    device_typedef.WString = ui->motor26_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[25] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor26_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor27_add_button2_pressed()
{
    if(!ui->motor27_open_button2->value())
     return;
    device_typedef.WString = ui->motor27_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[26] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor27_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor27_sub_button2_pressed()
{
    if(!ui->motor27_open_button2->value())
     return;
    device_typedef.WString = ui->motor27_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[26] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor27_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor28_add_button2_pressed()
{
    if(!ui->motor28_open_button2->value())
     return;
    device_typedef.WString = ui->motor28_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[27] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor28_adj2->setText(device_typedef.WString);
}


void manualOperation::on_motor28_sub_button2_pressed()
{
    if(!ui->motor28_open_button2->value())
     return;
    device_typedef.WString = ui->motor28_adj2->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[27] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor28_adj2->setText(device_typedef.WString);
}


void manualOperation::on_pushButton_siteWrite2_pressed()
{
       VCI_CAN_OBJ vco;

       uint8_t areaSw=0;


      if(!openStart)
      {
          CAN_WarningMessage_Show();
      }
      else
      {

          switch(areaSw)
          {

              case 0:{

                   for(uint8_t OneMode = 2; OneMode<13; OneMode++)
                   {
                      vco.ID = MOTOR_ADDRESS_BASE_ID + (OneMode+1);
                      vco.RemoteFlag = 0;
                      vco.ExternFlag = 0;
                      vco.DataLen = 8;

                      vco.Data[0] =  device_typedef.Motor_AdjSite[OneMode] <<8;
                      vco.Data[1] =  device_typedef.Motor_AdjSite[OneMode];
                      vco.Data[2] = 0;
                      vco.Data[3] = 0;
                      vco.Data[4] = 0;
                      vco.Data[5] = 0;
                      vco.Data[6] = 0;
                      vco.Data[7] = 0;

                      VCI_Transmit(4,0,0,&vco,1);
                  }
                  areaSw =+1;
              } ;

              case 1:{

                   for(uint8_t TwoMode = 17; TwoMode<28; TwoMode++)
                    {
                      vco.ID =  MOTOR_ADDRESS_BASE_ID + (TwoMode+1);
                      vco.RemoteFlag = 0;
                      vco.ExternFlag = 0;
                      vco.DataLen = 8;

                      vco.Data[0] =  device_typedef.Motor_AdjSite[TwoMode] <<8;
                      vco.Data[1] =  device_typedef.Motor_AdjSite[TwoMode];
                      vco.Data[2] = 0;
                      vco.Data[3] = 0;
                      vco.Data[4] = 0;
                      vco.Data[5] = 0;
                      vco.Data[6] = 0;
                      vco.Data[7] = 0;

                      VCI_Transmit(4,0,0,&vco,1);
                  }

             } ;

      }

          vco.ID = MOTOR_SYNC_MESSAGE_ID ;
          VCI_Transmit(4,0,0,&vco,1);

    }
}

void manualOperation::on_pushButton_clear2_pressed()
{
    uint8_t count=0;
    for(;count<28;count++)
    {
        device_typedef.Motor_AdjSite[count]&=0;
    }
    device_typedef.WString = "0";
    ui->motor3_adj2->setText(device_typedef.WString);
    ui->motor4_adj2->setText(device_typedef.WString);
    ui->motor5_adj2->setText(device_typedef.WString);
    ui->motor6_adj2->setText(device_typedef.WString);
    ui->motor7_adj2->setText(device_typedef.WString);
    ui->motor8_adj2->setText(device_typedef.WString);
    ui->motor9_adj2->setText(device_typedef.WString);
    ui->motor10_adj2->setText(device_typedef.WString);
    ui->motor11_adj2->setText(device_typedef.WString);
    ui->motor12_adj2->setText(device_typedef.WString);
    ui->motor13_adj2->setText(device_typedef.WString);

    ui->motor18_adj2->setText(device_typedef.WString);
    ui->motor19_adj2->setText(device_typedef.WString);
    ui->motor20_adj2->setText(device_typedef.WString);
    ui->motor21_adj2->setText(device_typedef.WString);
    ui->motor22_adj2->setText(device_typedef.WString);
    ui->motor23_adj2->setText(device_typedef.WString);
    ui->motor24_adj2->setText(device_typedef.WString);
    ui->motor25_adj2->setText(device_typedef.WString);
    ui->motor26_adj2->setText(device_typedef.WString);
    ui->motor27_adj2->setText(device_typedef.WString);
    ui->motor28_adj2->setText(device_typedef.WString);

}



void manualOperation::on_motor1_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor1_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor1_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor2_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor2_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor2_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor3_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor3_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor3_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor4_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor4_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor4_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor5_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor5_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor5_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor6_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor6_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor6_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor7_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor7_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor7_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor8_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor8_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor8_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor9_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor9_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor9_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor10_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor10_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor10_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}



void manualOperation::on_motor11_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor11_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor11_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor12_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor12_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor12_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor13_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor13_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor13_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor14_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor14_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor14_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor15_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor15_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor15_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor16_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor16_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor16_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor17_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor17_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor17_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor18_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor18_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor18_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor19_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor19_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor19_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor20_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor20_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor20_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor21_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor21_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor21_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor22_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor22_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor22_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor23_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor23_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor23_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor24_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor24_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor24_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor25_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor25_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor25_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor26_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor26_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor26_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor27_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor27_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor27_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor28_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor28_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor28_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor29_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor29_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor29_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
}


void manualOperation::on_motor30_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->motor30_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }
    else
    {
        ui->motor30_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
    }

}





void manualOperation::on_all_open_button3_valueChanged(int value)
{
    if(!value)
    {
        ui->all_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );

        ui->label_heard3->show();
        ui->label_autor3->hide();

    }
    else
    {
        ui->all_open_button3->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );

        ui->label_heard3->hide();
        ui->label_autor3->show();
    }

    switch(value)
    {
       case 1:{

                   ui->motor1_open_button3->setValue(true);
                   ui->motor2_open_button3->setValue(true);
                   ui->motor3_open_button3->setValue(true);
                   ui->motor4_open_button3->setValue(true);
                   ui->motor5_open_button3->setValue(true);
                   ui->motor6_open_button3->setValue(true);
                   ui->motor7_open_button3->setValue(true);
                   ui->motor8_open_button3->setValue(true);
                   ui->motor9_open_button3->setValue(true);
                   ui->motor10_open_button3->setValue(true);
                   ui->motor11_open_button3->setValue(true);
                   ui->motor12_open_button3->setValue(true);
                   ui->motor13_open_button3->setValue(true);
                   ui->motor14_open_button3->setValue(true);
                   ui->motor15_open_button3->setValue(true);
                   ui->motor16_open_button3->setValue(true);
                   ui->motor17_open_button3->setValue(true);
                   ui->motor18_open_button3->setValue(true);
                   ui->motor19_open_button3->setValue(true);
                   ui->motor20_open_button3->setValue(true);
                   ui->motor21_open_button3->setValue(true);
                   ui->motor22_open_button3->setValue(true);
                   ui->motor23_open_button3->setValue(true);
                   ui->motor24_open_button3->setValue(true);
                   ui->motor25_open_button3->setValue(true);
                   ui->motor26_open_button3->setValue(true);
                   ui->motor27_open_button3->setValue(true);
                   ui->motor28_open_button3->setValue(true);
                   ui->motor29_open_button3->setValue(true);
                   ui->motor30_open_button3->setValue(true);


    }break;
       case 0:{

                        ui->motor1_open_button3->setValue(false);
                        ui->motor2_open_button3->setValue(false);
                        ui->motor3_open_button3->setValue(false);
                        ui->motor4_open_button3->setValue(false);
                        ui->motor5_open_button3->setValue(false);
                        ui->motor6_open_button3->setValue(false);
                        ui->motor7_open_button3->setValue(false);
                        ui->motor8_open_button3->setValue(false);
                        ui->motor9_open_button3->setValue(false);
                        ui->motor10_open_button3->setValue(false);
                        ui->motor11_open_button3->setValue(false);
                        ui->motor12_open_button3->setValue(false);
                        ui->motor13_open_button3->setValue(false);
                        ui->motor14_open_button3->setValue(false);
                        ui->motor15_open_button3->setValue(false);
                        ui->motor16_open_button3->setValue(false);
                        ui->motor17_open_button3->setValue(false);
                        ui->motor18_open_button3->setValue(false);
                        ui->motor19_open_button3->setValue(false);
                        ui->motor20_open_button3->setValue(false);
                        ui->motor21_open_button3->setValue(false);
                        ui->motor22_open_button3->setValue(false);
                        ui->motor23_open_button3->setValue(false);
                        ui->motor24_open_button3->setValue(false);
                        ui->motor25_open_button3->setValue(false);
                        ui->motor26_open_button3->setValue(false);
                        ui->motor27_open_button3->setValue(false);
                        ui->motor28_open_button3->setValue(false);
                        ui->motor29_open_button3->setValue(false);
                        ui->motor30_open_button3->setValue(false);

    }break;
       default:;break;
    }

}

void manualOperation::on_stackedWidget_currentChanged(int arg1)
{
        switch(arg1) {
             case  0:{
                   DanMode_dataSlave();
        }break;   //.单膜区模式
             case  1:{
                   AllMode_dataSlave();
        }break;   //.全膜区模式
             case  2:{
                   HightMode_dataSlave();
        }break;  //.高级模式
             case  3:{
        }break;  //.电机状态
        default:{}break;
        }
}


void manualOperation::DanMode_dataSlave(void)
{
       uint8_t i=2;
       uint8_t j=17;

       for(; i<13; i++)
       {
           device_typedef.Wint =  device_typedef.Motor_AdjSite[i];
           device_typedef.WString.setNum(device_typedef.Wint);

           switch(i)
           {
           case 2:{ui->motor3_adj->setText(device_typedef.WString);}break;
           case 3:{ui->motor4_adj->setText(device_typedef.WString);}break;
           case 4:{ui->motor5_adj->setText(device_typedef.WString);}break;
           case 5:{ui->motor6_adj->setText(device_typedef.WString);}break;
           case 6:{ui->motor7_adj->setText(device_typedef.WString);}break;
           case 7:{ui->motor8_adj->setText(device_typedef.WString);}break;
           case 8:{ui->motor9_adj->setText(device_typedef.WString);}break;
           case 9:{ui->motor10_adj->setText(device_typedef.WString);}break;
           case 10:{ui->motor11_adj->setText(device_typedef.WString);}break;
           case 11:{ui->motor12_adj->setText(device_typedef.WString);}break;
           case 12:{ui->motor13_adj->setText(device_typedef.WString);}break;
           default:{}break;
           }
       }

       for(; j<28; j++)
       {
           device_typedef.Wint =  device_typedef.Motor_AdjSite[j];
           device_typedef.WString.setNum(device_typedef.Wint);

           switch(j)
           {
           case 17:{ui->motor18_adj->setText(device_typedef.WString);}break;
           case 18:{ui->motor19_adj->setText(device_typedef.WString);}break;
           case 19:{ui->motor20_adj->setText(device_typedef.WString);}break;
           case 20:{ui->motor21_adj->setText(device_typedef.WString);}break;
           case 21:{ui->motor22_adj->setText(device_typedef.WString);}break;
           case 22:{ui->motor23_adj->setText(device_typedef.WString);}break;
           case 23:{ui->motor24_adj->setText(device_typedef.WString);}break;
           case 24:{ui->motor25_adj->setText(device_typedef.WString);}break;
           case 25:{ui->motor26_adj->setText(device_typedef.WString);}break;
           case 26:{ui->motor27_adj->setText(device_typedef.WString);}break;
           case 27:{ui->motor28_adj->setText(device_typedef.WString);}break;
           default:{}break;
           }
       }

}


void manualOperation::AllMode_dataSlave(void)
{
    uint8_t i=2;
    uint8_t j=17;

    for(; i<13; i++)
    {
        device_typedef.Wint =  device_typedef.Motor_AdjSite[i];
        device_typedef.WString.setNum(device_typedef.Wint);

        switch(i)
        {
        case 2:{ui->motor3_adj2->setText(device_typedef.WString);}break;
        case 3:{ui->motor4_adj2->setText(device_typedef.WString);}break;
        case 4:{ui->motor5_adj2->setText(device_typedef.WString);}break;
        case 5:{ui->motor6_adj2->setText(device_typedef.WString);}break;
        case 6:{ui->motor7_adj2->setText(device_typedef.WString);}break;
        case 7:{ui->motor8_adj2->setText(device_typedef.WString);}break;
        case 8:{ui->motor9_adj2->setText(device_typedef.WString);}break;
        case 9:{ui->motor10_adj2->setText(device_typedef.WString);}break;
        case 10:{ui->motor11_adj2->setText(device_typedef.WString);}break;
        case 11:{ui->motor12_adj2->setText(device_typedef.WString);}break;
        case 12:{ui->motor13_adj2->setText(device_typedef.WString);}break;
        default:{}break;
        }
    }

    for(; j<28; j++)
    {
        device_typedef.Wint =  device_typedef.Motor_AdjSite[j];
        device_typedef.WString.setNum(device_typedef.Wint);

        switch(j)
        {
        case 17:{ui->motor18_adj2->setText(device_typedef.WString);}break;
        case 18:{ui->motor19_adj2->setText(device_typedef.WString);}break;
        case 19:{ui->motor20_adj2->setText(device_typedef.WString);}break;
        case 20:{ui->motor21_adj2->setText(device_typedef.WString);}break;
        case 21:{ui->motor22_adj2->setText(device_typedef.WString);}break;
        case 22:{ui->motor23_adj2->setText(device_typedef.WString);}break;
        case 23:{ui->motor24_adj2->setText(device_typedef.WString);}break;
        case 24:{ui->motor25_adj2->setText(device_typedef.WString);}break;
        case 25:{ui->motor26_adj2->setText(device_typedef.WString);}break;
        case 26:{ui->motor27_adj2->setText(device_typedef.WString);}break;
        case 27:{ui->motor28_adj2->setText(device_typedef.WString);}break;
        default:{}break;
        }
    }

}


void manualOperation::HightMode_dataSlave(void)
{
    uint8_t i;


    for(i=0; i<30; i++)
    {
        device_typedef.Wint =  device_typedef.Motor_AdjSite[i];
        device_typedef.WString.setNum(device_typedef.Wint);

        switch(i)
        {
        case 0:{ui->motor1_adj3->setText(device_typedef.WString);}break;
        case 1:{ui->motor2_adj3->setText(device_typedef.WString);}break;
        case 2:{ui->motor3_adj3->setText(device_typedef.WString);}break;
        case 3:{ui->motor4_adj3->setText(device_typedef.WString);}break;
        case 4:{ui->motor5_adj3->setText(device_typedef.WString);}break;
        case 5:{ui->motor6_adj3->setText(device_typedef.WString);}break;
        case 6:{ui->motor7_adj3->setText(device_typedef.WString);}break;
        case 7:{ui->motor8_adj3->setText(device_typedef.WString);}break;
        case 8:{ui->motor9_adj3->setText(device_typedef.WString);}break;
        case 9:{ui->motor10_adj3->setText(device_typedef.WString);}break;
        case 10:{ui->motor11_adj3->setText(device_typedef.WString);}break;
        case 11:{ui->motor12_adj3->setText(device_typedef.WString);}break;
        case 12:{ui->motor13_adj3->setText(device_typedef.WString);}break;
        case 13:{ui->motor14_adj3->setText(device_typedef.WString);}break;
        case 14:{ui->motor15_adj3->setText(device_typedef.WString);}break;
        case 15:{ui->motor16_adj3->setText(device_typedef.WString);}break;
        case 16:{ui->motor17_adj3->setText(device_typedef.WString);}break;
        case 17:{ui->motor18_adj3->setText(device_typedef.WString);}break;
        case 18:{ui->motor19_adj3->setText(device_typedef.WString);}break;
        case 19:{ui->motor20_adj3->setText(device_typedef.WString);}break;
        case 20:{ui->motor21_adj3->setText(device_typedef.WString);}break;
        case 21:{ui->motor22_adj3->setText(device_typedef.WString);}break;
        case 22:{ui->motor23_adj3->setText(device_typedef.WString);}break;
        case 23:{ui->motor24_adj3->setText(device_typedef.WString);}break;
        case 24:{ui->motor25_adj3->setText(device_typedef.WString);}break;
        case 25:{ui->motor26_adj3->setText(device_typedef.WString);}break;
        case 26:{ui->motor27_adj3->setText(device_typedef.WString);}break;
        case 27:{ui->motor28_adj3->setText(device_typedef.WString);}break;
        case 28:{ui->motor29_adj3->setText(device_typedef.WString);}break;
        case 29:{ui->motor30_adj3->setText(device_typedef.WString);}break;
        default:{}break;
        }
    }

}





void manualOperation::on_motor1_add_button3_pressed()
{
    if(!ui->motor1_open_button3->value())
     return;
    device_typedef.WString = ui->motor1_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[0] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor1_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor1_sub_button3_pressed()
{
    if(!ui->motor1_open_button3->value())
     return;
    device_typedef.WString = ui->motor1_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[0] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor1_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor2_add_button3_pressed()
{
    if(!ui->motor2_open_button3->value())
     return;
    device_typedef.WString = ui->motor2_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[1] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor2_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor2_sub_button3_pressed()
{
    if(!ui->motor2_open_button3->value())
     return;
    device_typedef.WString = ui->motor2_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[1] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor2_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor3_add_button3_pressed()
{
    if(!ui->motor3_open_button3->value())
     return;
    device_typedef.WString = ui->motor3_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[2] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor3_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor3_sub_button3_pressed()
{
    if(!ui->motor3_open_button3->value())
     return;
    device_typedef.WString = ui->motor3_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[2] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor3_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor4_add_button3_pressed()
{
    if(!ui->motor4_open_button3->value())
     return;
    device_typedef.WString = ui->motor4_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[3] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor4_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor4_sub_button3_pressed()
{
    if(!ui->motor4_open_button3->value())
     return;
    device_typedef.WString = ui->motor4_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[3] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor4_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor5_add_button3_pressed()
{
    if(!ui->motor5_open_button3->value())
     return;
    device_typedef.WString = ui->motor5_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[4] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor5_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor5_sub_button3_pressed()
{
    if(!ui->motor5_open_button3->value())
     return;
    device_typedef.WString = ui->motor5_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[4] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor5_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor6_add_button3_pressed()
{
    if(!ui->motor6_open_button3->value())
     return;
    device_typedef.WString = ui->motor6_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[5] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor6_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor6_sub_button3_pressed()
{
    if(!ui->motor6_open_button3->value())
     return;
    device_typedef.WString = ui->motor6_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[5] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor6_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor7_add_button3_pressed()
{
    if(!ui->motor7_open_button3->value())
     return;
    device_typedef.WString = ui->motor7_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[6] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor7_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor7_sub_button3_pressed()
{
    if(!ui->motor7_open_button3->value())
     return;
    device_typedef.WString = ui->motor7_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[6] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor7_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor8_add_button3_pressed()
{
    if(!ui->motor8_open_button3->value())
     return;
    device_typedef.WString = ui->motor8_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[7] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor8_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor8_sub_button3_pressed()
{
    if(!ui->motor8_open_button3->value())
     return;
    device_typedef.WString = ui->motor8_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[7] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor8_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor9_add_button3_pressed()
{
    if(!ui->motor9_open_button3->value())
     return;
    device_typedef.WString = ui->motor9_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[8] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor9_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor9_sub_button3_pressed()
{
    if(!ui->motor9_open_button3->value())
     return;
    device_typedef.WString = ui->motor9_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[8] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor9_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor10_add_button3_pressed()
{
    if(!ui->motor10_open_button3->value())
     return;
    device_typedef.WString = ui->motor10_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[9] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor10_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor10_sub_button3_pressed()
{
    if(!ui->motor10_open_button3->value())
     return;
    device_typedef.WString = ui->motor10_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[9] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor10_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor11_add_button3_pressed()
{
    if(!ui->motor11_open_button3->value())
     return;
    device_typedef.WString = ui->motor11_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[10] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor11_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor11_sub_button3_pressed()
{
    if(!ui->motor11_open_button3->value())
     return;
    device_typedef.WString = ui->motor11_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[10] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor11_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor12_add_button3_pressed()
{
    if(!ui->motor12_open_button3->value())
     return;
    device_typedef.WString = ui->motor12_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[11] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor12_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor12_sub_button3_pressed()
{
    if(!ui->motor12_open_button3->value())
     return;
    device_typedef.WString = ui->motor12_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[11] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor12_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor13_add_button3_pressed()
{
    if(!ui->motor13_open_button3->value())
     return;
    device_typedef.WString = ui->motor13_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[12] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor13_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor13_sub_button3_pressed()
{
    if(!ui->motor13_open_button3->value())
     return;
    device_typedef.WString = ui->motor13_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[12] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor13_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor14_add_button3_pressed()
{
    if(!ui->motor14_open_button3->value())
     return;
    device_typedef.WString = ui->motor14_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[13] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor14_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor14_sub_button3_pressed()
{
    if(!ui->motor14_open_button3->value())
     return;
    device_typedef.WString = ui->motor14_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[13] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor14_adj3->setText(device_typedef.WString);

}


void manualOperation::on_motor15_add_button3_pressed()
{
    if(!ui->motor15_open_button3->value())
     return;
    device_typedef.WString = ui->motor15_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[14] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor15_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor15_sub_button3_pressed()
{
    if(!ui->motor15_open_button3->value())
     return;
    device_typedef.WString = ui->motor15_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[14] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor15_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor16_add_button3_pressed()
{
    if(!ui->motor16_open_button3->value())
     return;
    device_typedef.WString = ui->motor16_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[15] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor16_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor16_sub_button3_pressed()
{
    if(!ui->motor16_open_button3->value())
     return;
    device_typedef.WString = ui->motor16_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[15] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor16_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor17_add_button3_pressed()
{
    if(!ui->motor17_open_button3->value())
     return;
    device_typedef.WString = ui->motor17_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[16] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor17_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor17_sub_button3_pressed()
{
    if(!ui->motor17_open_button3->value())
     return;
    device_typedef.WString = ui->motor17_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[16] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor17_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor18_add_button3_pressed()
{
    if(!ui->motor18_open_button3->value())
     return;
    device_typedef.WString = ui->motor18_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[17] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor18_adj3->setText(device_typedef.WString);

}


void manualOperation::on_motor18_sub_button3_pressed()
{
    if(!ui->motor18_open_button3->value())
     return;
    device_typedef.WString = ui->motor18_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[17] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor18_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor19_add_button3_pressed()
{
    if(!ui->motor19_open_button3->value())
     return;
    device_typedef.WString = ui->motor19_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[18] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor19_adj3->setText(device_typedef.WString);

}


void manualOperation::on_motor19_sub_button3_pressed()
{
    if(!ui->motor19_open_button3->value())
     return;
    device_typedef.WString = ui->motor19_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[18] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor19_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor20_add_button3_pressed()
{
    if(!ui->motor20_open_button3->value())
     return;
    device_typedef.WString = ui->motor20_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[19] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor20_adj3->setText(device_typedef.WString);

}


void manualOperation::on_motor20_sub_button3_pressed()
{
    if(!ui->motor20_open_button3->value())
     return;
    device_typedef.WString = ui->motor20_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[19] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor20_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor21_add_button3_pressed()
{
    if(!ui->motor21_open_button3->value())
     return;
    device_typedef.WString = ui->motor21_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[20] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor21_adj3->setText(device_typedef.WString);

}


void manualOperation::on_motor21_sub_button3_pressed()
{
    if(!ui->motor21_open_button3->value())
     return;
    device_typedef.WString = ui->motor21_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[20] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor21_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor22_add_button3_pressed()
{
    if(!ui->motor22_open_button3->value())
     return;
    device_typedef.WString = ui->motor22_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[21] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor22_adj3->setText(device_typedef.WString);

}


void manualOperation::on_motor22_sub_button3_pressed()
{
    if(!ui->motor22_open_button3->value())
     return;
    device_typedef.WString = ui->motor22_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[21] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor22_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor23_add_button3_pressed()
{
    if(!ui->motor23_open_button3->value())
     return;
    device_typedef.WString = ui->motor23_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[22] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor23_adj3->setText(device_typedef.WString);

}


void manualOperation::on_motor23_sub_button3_pressed()
{
    if(!ui->motor23_open_button3->value())
     return;
    device_typedef.WString = ui->motor23_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[22] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor23_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor24_add_button3_pressed()
{
    if(!ui->motor24_open_button3->value())
     return;
    device_typedef.WString = ui->motor24_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[23] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor24_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor24_sub_button3_pressed()
{
    if(!ui->motor24_open_button3->value())
     return;
    device_typedef.WString = ui->motor24_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[23] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor24_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor25_add_button3_pressed()
{
    if(!ui->motor25_open_button3->value())
     return;
    device_typedef.WString = ui->motor25_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[24] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor25_adj3->setText(device_typedef.WString);

}


void manualOperation::on_motor25_sub_button3_pressed()
{
    if(!ui->motor25_open_button3->value())
     return;
    device_typedef.WString = ui->motor25_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[24] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor25_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor26_add_button3_pressed()
{
    if(!ui->motor26_open_button3->value())
     return;
    device_typedef.WString = ui->motor26_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[25] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor26_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor26_sub_button3_pressed()
{
    if(!ui->motor26_open_button3->value())
     return;
    device_typedef.WString = ui->motor26_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[25] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor26_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor27_add_button3_pressed()
{
    if(!ui->motor27_open_button3->value())
     return;
    device_typedef.WString = ui->motor27_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[26] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor27_adj3->setText(device_typedef.WString);

}


void manualOperation::on_motor27_sub_button3_pressed()
{
    if(!ui->motor27_open_button3->value())
     return;
    device_typedef.WString = ui->motor27_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[26] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor27_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor28_add_button3_pressed()
{
    if(!ui->motor28_open_button3->value())
     return;
    device_typedef.WString = ui->motor28_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[27] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor28_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor28_sub_button3_pressed()
{
    if(!ui->motor28_open_button3->value())
     return;
    device_typedef.WString = ui->motor28_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[27] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor28_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor29_add_button3_pressed()
{
    if(!ui->motor29_open_button3->value())
     return;
    device_typedef.WString = ui->motor29_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[28] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor29_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor29_sub_button3_pressed()
{
    if(!ui->motor29_open_button3->value())
     return;
    device_typedef.WString = ui->motor29_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[28] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor29_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor30_add_button3_pressed()
{
    if(!ui->motor30_open_button3->value())
     return;
    device_typedef.WString = ui->motor30_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint +=1;
    if(device_typedef.Wint>=2000){ device_typedef.Wint=2000; }
    device_typedef.Motor_AdjSite[29] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor30_adj3->setText(device_typedef.WString);
}


void manualOperation::on_motor30_sub_button3_pressed()
{
    if(!ui->motor30_open_button3->value())
     return;
    device_typedef.WString = ui->motor30_adj3->text();
    device_typedef.Wint = device_typedef.WString.toInt();
    device_typedef.Wint -=1;
    if(device_typedef.Wint<=0){ device_typedef.Wint=0; }
    device_typedef.Motor_AdjSite[29] = device_typedef.Wint;
    device_typedef.WString.setNum(device_typedef.Wint);
    ui->motor30_adj3->setText(device_typedef.WString);
}


void manualOperation::on_hightMode_siteWrite_pressed()
{
     if(!openStart)
     {
         CAN_WarningMessage_Show();
     }
     else
    {
          device_typedef.Wint = ui->comboBox_2->currentIndex();


           if(device_typedef.Wint == 2)
           {
               for(uint8_t i=0;  i<30;  i++)
               {
                               vco.ID = MOTOR_ADDRESS_BASE_ID + (i+1) ;
                               vco.RemoteFlag = 0;
                               vco.ExternFlag = 0;
                               vco.DataLen = 8;
                               vco.Data[0] = device_typedef.Motor_AdjSite[i] <<8;
                               vco.Data[1] = device_typedef.Motor_AdjSite[i];
                               vco.Data[2] = 0;
                               vco.Data[3] = 0;
                               vco.Data[4] = 0;
                               vco.Data[5] = 0;
                               vco.Data[6] = 0;
                               vco.Data[7] = 0;
                               VCI_Transmit(4,0,0,&vco,1);
               }
               vco.ID = MOTOR_SYNC_MESSAGE_ID ;
               VCI_Transmit(4,0,0,&vco,1);
           }
     }
}

void manualOperation::HightModeSend(void)
{
    uint8_t i;
    VCI_CAN_OBJ vco;


           for(i=0; i<30; i++)
           {
            vco.ID = i+1;
            vco.RemoteFlag = 0;
            vco.ExternFlag = 0;
            vco.DataLen = 8;

            vco.Data[0] =  device_typedef.Motor_AdjSite[i] <<8;
            vco.Data[1] =  device_typedef.Motor_AdjSite[i];
            vco.Data[2] = 0;
            vco.Data[3] = 0;
            vco.Data[4] = 0;
            vco.Data[5] = 0;
            vco.Data[6] = 0;
            vco.Data[7] = 0;

             VCI_Transmit(4,0,0,&vco,1);

           }
}




void manualOperation::on_comboBox_onlymode_currentIndexChanged(int index)
{
    switch(index){
    case 0:{

        ui->stackedWidget_onlymode->setCurrentIndex(0);

    }break;
    case 1:{

        ui->stackedWidget_onlymode->setCurrentIndex(1);

    }break;
    default:break;
    }
}


void manualOperation::on_comboBox_allmode_currentIndexChanged(int index)
{
    switch(index){
    case 0:{

        ui->stackedWidget_allmode->setCurrentIndex(0);

    }break;
    case 1:{

        ui->stackedWidget_allmode->setCurrentIndex(1);

    }break;
    default:break;
    }
}


void manualOperation::on_comboBox_hightmode_currentIndexChanged(int index)
{
    switch(index){
    case 0:{

        ui->stackedWidget_hightmode->setCurrentIndex(0);

    }break;
    case 1:{

        ui->stackedWidget_hightmode->setCurrentIndex(1);

    }break;
    default:break;
    }
}


void manualOperation::on_AutoSiteWrite_open_button_valueChanged(int value)
{
    if(!value)
    {
        ui->AutoSiteWrite_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: #949494; border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
        ui->label_close->show();
        ui->label_open->hide();
    }
    else
    {
        ui->AutoSiteWrite_open_button->setStyleSheet(
                    "QSlider::groove:horizontal{ border: none; background-color: rgb(0,170,0); border-radius: 8px; }"
                    "QSlider::handle:horizontal{ width: 16px; height: 20px; background-color: white; border-radius:8px; }"
                    );
        ui->label_close->hide();
        ui->label_open->show();
    }
}



void manualOperation:: FaceReal_DataChart()               /*面密度仪实时数据*/
{
    ui->gridLayout_faceReal->removeWidget(facereal_chartview);
    facereal_chartview = new QChartView(FaceRealData_Dealwith());
    ui->gridLayout_faceReal->addWidget(facereal_chartview);
}

QChart *manualOperation::FaceRealData_Dealwith() const
{
    QChart *facereal_view = new QChart();

    //QBarSet *bar = new QBarSet("面密度仪实时数据");
    //*bar << 371.6 << 371.6 << 370.6 << 371.6 << 370.6 << 371.6 << 370.6 << 371.6 << 370.6 << 371.6
      //<< 370.6 << 371.6 << 370.6 << 371.6 << 370.6 << 371.6 << 370.6 << 371.6 << 370.6 << 371.6
      //<< 372.6 << 375.6 << 376.6 << 377.6 << 377.6 << 377.6 << 370.6 << 378.6;
    //bar->setColor(QColor(0,162,232));

    /**/
    QBarSeries *series = new QBarSeries();
    //series->append(bar);
    series->setLabelsFormat("@value");
    series->setBarWidth(1);
    series->setLabelsVisible(1);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    facereal_view->addSeries(series);
    facereal_view->setAnimationOptions(QChart::SeriesAnimations);
    /*y*/
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(371.50,379.50);
    axisY->setTickCount(5);
    axisY->setGridLineVisible(1);
    series->attachAxis(axisY);
    facereal_view->addAxis(axisY,Qt::AlignLeft);

    return facereal_view;
}



void manualOperation::FaceReal_TendencyChart()       /*面密度仪趋势图*/
{
    ui->gridLayout_TendencyChart->removeWidget(FACE_REAL_TendencyChart);
    FACE_REAL_TendencyChart = new QChartView(FaceData_TendencyChart_Dealwith());
    ui->gridLayout_TendencyChart->addWidget(FACE_REAL_TendencyChart);
}

QChart *manualOperation::FaceData_TendencyChart_Dealwith () const
{
    QLineSeries *series = new QLineSeries();

    series->append(0, 6);
    series->append(1, 7);
    series->append(2, 8);
    series->append(3, 2);
    series->append(4, 3);
    series->append(5, 5);
    series->append(6, 8);

    QChart *chart = new QChart();

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple Line Chart Example");

    QChartView *chartView = new QChartView(chart);
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chart;
}

void manualOperation::on_stackedWidget_onlymode_currentChanged(int arg1)
{
         if(arg1 == 0)
         {
             FaceReal_DataChart() ;             /*面密度仪实时数据*/
         }
         else
         {
             FaceReal_TendencyChart();       /*面密度仪趋势图*/
         }
}



void manualOperation:: FaceReal_DataChart2()               /*面密度仪实时数据*/
{
    ui->gridLayout_faceReal2->removeWidget(facereal_chartview2);
    facereal_chartview2 = new QChartView(FaceRealData_Dealwith());
    ui->gridLayout_faceReal2->addWidget(facereal_chartview2);
}

void manualOperation::FaceReal_TendencyChart2()       /*面密度仪趋势图*/
{
    ui->gridLayout_TendencyChart2->removeWidget(FACE_REAL_TendencyChart2);
    FACE_REAL_TendencyChart2 = new QChartView(FaceData_TendencyChart_Dealwith());
    ui->gridLayout_TendencyChart2->addWidget(FACE_REAL_TendencyChart2);
}

void manualOperation::on_stackedWidget_allmode_currentChanged(int arg1)
{
        if(arg1 == 0)
        {
             FaceReal_DataChart2();                /*面密度仪实时数据图*/
        }
        else
        {
            FaceReal_TendencyChart2();      /*面密度仪趋势图*/
        }
}



void manualOperation:: FaceReal_DataChart3()               /*面密度仪实时数据*/
{
    ui->gridLayout_faceReal3->removeWidget(facereal_chartview3);
    facereal_chartview3 = new QChartView(FaceRealData_Dealwith());
    ui->gridLayout_faceReal3->addWidget(facereal_chartview3);
}

void manualOperation::FaceReal_TendencyChart3()       /*面密度仪趋势图*/
{
    ui->gridLayout_TendencyChart3->removeWidget(FACE_REAL_TendencyChart3);
    FACE_REAL_TendencyChart3 = new QChartView(FaceData_TendencyChart_Dealwith());
    ui->gridLayout_TendencyChart3->addWidget(FACE_REAL_TendencyChart3);
}

void manualOperation::on_stackedWidget_hightmode_currentChanged(int arg1)
{
    if(arg1 == 0)
    {
         FaceReal_DataChart3();                /*面密度仪实时数据图*/
    }
    else
    {
        FaceReal_TendencyChart3();      /*面密度仪趋势图*/
    }
}


void manualOperation::on_pushButton_clear3_pressed()
{

    uint8_t count=0;

    for( ; count<30; count++ )
    {
        device_typedef.Motor_AdjSite[count]&=0;
    }

    device_typedef.WString = "0";

    ui->motor1_adj3->setText(device_typedef.WString);
    ui->motor2_adj3->setText(device_typedef.WString);
    ui->motor3_adj3->setText(device_typedef.WString);
    ui->motor4_adj3->setText(device_typedef.WString);
    ui->motor5_adj3->setText(device_typedef.WString);
    ui->motor6_adj3->setText(device_typedef.WString);
    ui->motor7_adj3->setText(device_typedef.WString);
    ui->motor8_adj3->setText(device_typedef.WString);
    ui->motor9_adj3->setText(device_typedef.WString);
    ui->motor10_adj3->setText(device_typedef.WString);

    ui->motor11_adj3->setText(device_typedef.WString);
    ui->motor12_adj3->setText(device_typedef.WString);
    ui->motor13_adj3->setText(device_typedef.WString);
    ui->motor14_adj3->setText(device_typedef.WString);
    ui->motor15_adj3->setText(device_typedef.WString);
    ui->motor16_adj3->setText(device_typedef.WString);
    ui->motor17_adj3->setText(device_typedef.WString);
    ui->motor18_adj3->setText(device_typedef.WString);
    ui->motor19_adj3->setText(device_typedef.WString);
    ui->motor20_adj3->setText(device_typedef.WString);

    ui->motor21_adj3->setText(device_typedef.WString);
    ui->motor22_adj3->setText(device_typedef.WString);
    ui->motor23_adj3->setText(device_typedef.WString);
    ui->motor24_adj3->setText(device_typedef.WString);
    ui->motor25_adj3->setText(device_typedef.WString);
    ui->motor26_adj3->setText(device_typedef.WString);
    ui->motor27_adj3->setText(device_typedef.WString);
    ui->motor28_adj3->setText(device_typedef.WString);
    ui->motor29_adj3->setText(device_typedef.WString);
    ui->motor30_adj3->setText(device_typedef.WString);

}


