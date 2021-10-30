#include "mapview.h"
#include "ui_mapview.h"

MapView::MapView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapView)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->webView->setUrl(QUrl("file:///" + QDir::currentPath()+ "/Map/map.html"));
}

MapView::~MapView()
{
    delete ui;
}

void MapView::on_PositionReset_clicked()
{

}
