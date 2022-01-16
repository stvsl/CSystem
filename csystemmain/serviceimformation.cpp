#include "serviceimformation.h"
#include "ui_serviceimformation.h"

ServiceImformation::ServiceImformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServiceImformation)
{
    ui->setupUi(this);
}

ServiceImformation::~ServiceImformation()
{
    delete ui;
}
