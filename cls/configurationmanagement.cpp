#include "configurationmanagement.h"
#include "ui_configurationmanagement.h"

configurationmanagement::configurationmanagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::configurationmanagement)
{
    ui->setupUi(this);

    /**/
    ui->stackedWidget->setCurrentIndex(0);
    on_gongyi_pushButton_clicked();

}

configurationmanagement::~configurationmanagement()
{
    delete ui;
}


void configurationmanagement::on_gongyi_pushButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);

     ui->gongyi_pushButton->setStyleSheet(
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
     ui->deviceConfing_pushButton->setStyleSheet(
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
     ui->autoConfing_pushButton->setStyleSheet(
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
     ui->fuzhuConfingpushButton->setStyleSheet(
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
     ui->testConfing_pushButton->setStyleSheet(
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
     ui->tubujiConfing_pushButton->setStyleSheet(
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
     ui->wrrogConfing_pushButton->setStyleSheet(
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


void configurationmanagement::on_deviceConfing_pushButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);

     ui->gongyi_pushButton->setStyleSheet(
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
     ui->deviceConfing_pushButton->setStyleSheet(
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
     ui->autoConfing_pushButton->setStyleSheet(
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
     ui->fuzhuConfingpushButton->setStyleSheet(
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
     ui->testConfing_pushButton->setStyleSheet(
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
     ui->tubujiConfing_pushButton->setStyleSheet(
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
     ui->wrrogConfing_pushButton->setStyleSheet(
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


void configurationmanagement::on_autoConfing_pushButton_clicked()
{
      ui->stackedWidget->setCurrentIndex(2);

      ui->gongyi_pushButton->setStyleSheet(
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
      ui->deviceConfing_pushButton->setStyleSheet(
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
      ui->autoConfing_pushButton->setStyleSheet(
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
      ui->fuzhuConfingpushButton->setStyleSheet(
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
      ui->testConfing_pushButton->setStyleSheet(
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
      ui->tubujiConfing_pushButton->setStyleSheet(
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
      ui->wrrogConfing_pushButton->setStyleSheet(
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


void configurationmanagement::on_fuzhuConfingpushButton_clicked()
{
      ui->stackedWidget->setCurrentIndex(3);

      ui->gongyi_pushButton->setStyleSheet(
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
      ui->deviceConfing_pushButton->setStyleSheet(
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
      ui->autoConfing_pushButton->setStyleSheet(
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
      ui->fuzhuConfingpushButton->setStyleSheet(
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
      ui->testConfing_pushButton->setStyleSheet(
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
      ui->tubujiConfing_pushButton->setStyleSheet(
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
      ui->wrrogConfing_pushButton->setStyleSheet(
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


void configurationmanagement::on_testConfing_pushButton_clicked()
{
      ui->stackedWidget->setCurrentIndex(4);

      ui->gongyi_pushButton->setStyleSheet(
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
      ui->deviceConfing_pushButton->setStyleSheet(
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
      ui->autoConfing_pushButton->setStyleSheet(
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
      ui->fuzhuConfingpushButton->setStyleSheet(
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
      ui->testConfing_pushButton->setStyleSheet(
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
      ui->tubujiConfing_pushButton->setStyleSheet(
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
      ui->wrrogConfing_pushButton->setStyleSheet(
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


void configurationmanagement::on_tubujiConfing_pushButton_clicked()
{
      ui->stackedWidget->setCurrentIndex(5);

      ui->gongyi_pushButton->setStyleSheet(
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
      ui->deviceConfing_pushButton->setStyleSheet(
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
      ui->autoConfing_pushButton->setStyleSheet(
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
      ui->fuzhuConfingpushButton->setStyleSheet(
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
      ui->testConfing_pushButton->setStyleSheet(
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
      ui->tubujiConfing_pushButton->setStyleSheet(
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
      ui->wrrogConfing_pushButton->setStyleSheet(
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


void configurationmanagement::on_wrrogConfing_pushButton_clicked()
{
      ui->stackedWidget->setCurrentIndex(6);

      ui->gongyi_pushButton->setStyleSheet(
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
      ui->deviceConfing_pushButton->setStyleSheet(
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
      ui->autoConfing_pushButton->setStyleSheet(
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
      ui->fuzhuConfingpushButton->setStyleSheet(
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
      ui->testConfing_pushButton->setStyleSheet(
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
      ui->tubujiConfing_pushButton->setStyleSheet(
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
      ui->wrrogConfing_pushButton->setStyleSheet(
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



