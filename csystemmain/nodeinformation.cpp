#include "nodeinformation.h"
#include "ui_nodeinformation.h"

nodeinformation::nodeinformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nodeinformation)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

nodeinformation::~nodeinformation()
{
    delete ui;
}
