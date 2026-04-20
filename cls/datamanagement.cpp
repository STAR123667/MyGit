#include "datamanagement.h"
#include "ui_datamanagement.h"

datamanagement::datamanagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::datamanagement)
{
    ui->setupUi(this);
}

datamanagement::~datamanagement()
{
    delete ui;
}

void datamanagement::on_pushButton_1_pressed()
{
     ui->stackedWidget->setCurrentIndex(0);
}


void datamanagement::on_pushButton_2_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
}

