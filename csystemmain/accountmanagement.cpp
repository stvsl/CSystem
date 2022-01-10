#include "accountmanagement.h"
#include "ui_accountmanagement.h"

AccountManagement::AccountManagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountManagement)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

AccountManagement::~AccountManagement()
{
    delete ui;
}
