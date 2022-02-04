#include "mapview.h"
#include "ui_mapview.h"

MapView::MapView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapView)
{
    //远程debug
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "1112");
    //融合进程
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--single-process");
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->mapSearcher->addAction(QIcon(":/icon/source/icon/搜索.png"),QLineEdit::TrailingPosition);
    ui->webView->setUrl(QUrl("http://stvsljl.com/pages/default/map"));
    channel = new QWebChannel(this);                    //通讯对象
    channel->registerObject(QString("trans"),this);     //通信介质注册
    ui->webView->page()->setWebChannel(channel);        //通讯附加
}

MapView::~MapView()
{
    delete channel;
    delete ui;
}

void MapView::on_PositionReset_clicked()
{
    emit setCenter();
}

//地图搜索功能实现
void MapView::on_mapSearcher_editingFinished()
{
    QString str = ui->mapSearcher->text();
    if(str[0] == nullptr){
        ui->mapSearcher->setText("输入无效");
    }else{
        emit searchP(str);
    }
}

//结点搜索功能实现
void MapView::on_node_Searcher_editingFinished()
{
    QString str = ui->nodeSearcher->text();
    //TODO搜索结点
}

