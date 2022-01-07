#include "mapsetting.h"
#include "ui_mapsetting.h"

MapSetting::MapSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapSetting)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

MapSetting::~MapSetting()
{
    delete ui;
}
