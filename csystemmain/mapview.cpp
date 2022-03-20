#include "mapview.h"
#include "ui_mapview.h"
#include "configManager/configmanager.h"
#include <QWebEngineSettings>
#include <configManager/mapconfig.h>
#include <QTimer>
#include <QDebug>
#include <QEventLoop>
#include "csystemmain/csystemmain.h"
#include "cacheManager/CacheManager.h"

MapView::MapView(QWidget *parent) : QWidget(parent),
                                    ui(new Ui::MapView)
{
    //远程debug
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "1112");
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->webView->setUrl(QUrl("http://127.0.0.1:10241/pages/default/map"));
    channel = new QWebChannel(this);                 //通讯对象
    channel->registerObject(QString("trans"), this); //通信介质注册
    ui->webView->page()->setWebChannel(channel);     //通讯附加
    // 设置坐标居中（1.15秒后执行）
    QTimer ::singleShot(1150, this, SLOT(on_PositionReset_clicked()));
}

MapView::~MapView()
{
    delete channel;
    delete ui;
}

void MapView::init()
{
    // 遍历CSystemMain::nodeInfoList
    // 将节点信息添加到地图上
    for (int i = 0; i < CSystemMain::nodeInfoList->size(); i++)
    {
        // 表格模板
        QString info = "<table class=\" table - ui \">"
                       "<tr>"
                       "<td>ID</td>"
                       "<td>" +
                       CSystemMain::nodeInfoList->at(i).id + "</td>"
                                                             "</tr>"
                                                             "<tr>"
                                                             "<td>所属信息</td>"
                                                             "<td>" +
                       CSystemMain::nodeInfoList->at(i).belong + "</td>"
                                                                 "</tr>"
                                                                 "<tr>"
                                                                 "<td>数据上传日期</td>"
                                                                 "<td>" +
                       CSystemMain::nodeInfoList->at(i).lastUpload.toString() + "</td>"
                                                                                "</tr>"
                                                                                "<tr>"
                                                                                "<td>自检日期</td>"
                                                                                "<td>" +
                       CSystemMain::nodeInfoList->at(i).selfDate.toString() + "</td>"
                                                                              "</tr>"
                                                                              "</table>";
        float x = CSystemMain::nodeInfoList->at(i).lo;
        float y = CSystemMain::nodeInfoList->at(i).li;
        addPoint(info, x, y);
    }
}

void MapView::on_PositionReset_clicked()
{
    emit setCenter(MAP_CONFIG::X, MAP_CONFIG::Y);
}

//地图搜索功能实现
void MapView::on_mapSearcher_editingFinished()
{
    QString str = ui->mapSearcher->text();
    if (str[0] == nullptr)
    {
        ui->mapSearcher->setText("输入无效");
    }
    else
    {
        emit searchP(str);
    }
}

//结点搜索功能实现
void MapView::on_node_Searcher_editingFinished()
{
    QString str = ui->nodeSearcher->text();
    // TODO搜索结点
}
