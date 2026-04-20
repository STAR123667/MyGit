#include "systemmanagement.h"
#include "ui_systemmanagement.h"

systemmanagement::systemmanagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::systemmanagement)
{
    ui->setupUi(this);
}

systemmanagement::~systemmanagement()
{
    delete ui;
}
