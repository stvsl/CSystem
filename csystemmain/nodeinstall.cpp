#include "nodeinstall.h"
#include "ui_nodeinstall.h"

NodeInstall::NodeInstall(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NodeInstall)
{
    ui->setupUi(this);
}

NodeInstall::~NodeInstall()
{
    delete ui;
}
