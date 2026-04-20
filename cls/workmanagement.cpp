#include "workmanagement.h"
#include "ui_workmanagement.h"

workmanagement::workmanagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::workmanagement)
{
    ui->setupUi(this);
}

workmanagement::~workmanagement()
{
    delete ui;
}
