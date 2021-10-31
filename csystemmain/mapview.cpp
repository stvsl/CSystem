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
    QWebChannel *channel = new QWebChannel(this);         //定义QWebChannel负责
    channel->registerObject(QString("person"),this);    //QWebChannel对Widget类，注册一个person的通信介质
    ui->webView->page()->setWebChannel(channel);
}

MapView::~MapView()
{
    delete ui;
}

void MapView::on_PositionReset_clicked()
{
    ui->webView->page()->runJavaScript("set");
}
