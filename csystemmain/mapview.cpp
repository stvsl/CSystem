#include "mapview.h"
#include "ui_mapview.h"

MapView::MapView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapView)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->webView->setUrl(QUrl("https://www.baidu.com"));
}

MapView::~MapView()
{
    delete ui;
}
