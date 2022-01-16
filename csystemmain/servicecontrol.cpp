#include "servicecontrol.h"
#include "ui_servicecontrol.h"

ServiceControl::ServiceControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServiceControl)
{
    ui->setupUi(this);
}

ServiceControl::~ServiceControl()
{
    delete ui;
}
