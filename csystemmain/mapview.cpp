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
#include <QStringList>
#include <QStringListModel>
#include <QTableWidgetItem>
#include <QGraphicsDropShadowEffect>

MapView::MapView(QWidget *parent) : QWidget(parent),
                                    ui(new Ui::MapView)
{
    // debug
    // qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "1112");
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->webView->setUrl(QUrl("http://127.0.0.1:10241/pages/default/map"));

    channel = new QWebChannel(this);             //通讯对象
    channel->registerObject("trans", this);      //通信介质注册
    ui->webView->page()->setWebChannel(channel); //通讯附加
    ui->nodeinfoview->setHorizontalHeaderLabels(QStringList() << "监测项目"
                                                              << "检测值");
    ui->nodeinfoview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应宽度
    ui->nodeinfoview->setSelectionBehavior(QAbstractItemView::SelectRows);            //整行选中
    ui->nodeinfoview->setEditTriggers(QAbstractItemView::NoEditTriggers);             //禁止编辑
    ui->nodeinfoview->setDragDropMode(QAbstractItemView::NoDragDrop);                 //禁止拖拽
    ui->nodeinfoview->verticalHeader()->setVisible(false);                            //隐藏表头
    ui->nodeinfoview->setSelectionBehavior(QAbstractItemView::SelectRows);            //整行选中
    ui->nodeinfoview->horizontalHeader()->setHighlightSections(false);                //去除选中时的高亮
    // 阴影效果
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(ui->label);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(125, 164, 255, 80));
    shadow_effect->setBlurRadius(10);
    ui->label->setGraphicsEffect(shadow_effect);
}

MapView::~MapView()
{
    delete channel;
    delete ui;
}

void MapView::init()
{
    QStringList list;
    // 遍历CSystemMain::nodeInfoList
    // 将节点信息添加到地图上
    for (int i = 0; i < CSystemMain::nodeInfoList->size(); i++)
    {
        // 表格模板,防止挤压
        QString info = "<table class=\"table - ui\"style = \"width: 350px; \" >"
                       "<tr>"
                       "<td>节点编号</td>"
                       "<td>" +
                       CSystemMain::nodeInfoList->at(i).id + "</td>" +
                       "</tr>"
                       "<tr>"
                       "<td>节点归属</td>"
                       "<td>" +
                       CSystemMain::nodeInfoList->at(i).COMNAME + "</td>" +
                       "</tr>"
                       "<tr>"
                       "<td>数据上传日期</td>"
                       "<td>" +
                       CSystemMain::nodeInfoList->at(i).lastUpload.toString("yyyy-MM-dd-hh-mm-ss") + "</td>" +
                       "</tr>"
                       "<tr>"
                       "<td>数据上传时间</td>"
                       "<td>" +
                       CSystemMain::nodeInfoList->at(i).selfDate.toString("yyyy-MM-dd-hh-mm-ss") + "</td>" +
                       "</tr>"
                       "</table>";
        float x = CSystemMain::nodeInfoList->at(i).lo;
        float y = CSystemMain::nodeInfoList->at(i).li;
        addPoint(info, x, y);
        list.append("   " + CSystemMain::nodeInfoList->at(i).id);
    }
    ui->NodeList->setModel(new QStringListModel(list));
    QTimer ::singleShot(1400, [=]()
                        { emit setCenter(MAP_CONFIG::X, MAP_CONFIG::Y); });
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
void MapView::on_nodeSearcher_editingFinished()
{
    QString str = ui->nodeSearcher->text();
    // 判断输入是否为空
    if (str[0] == nullptr)
    {
        ui->nodeSearcher->setText("输入无效");
    }
    else
    {
        bool flag = false;
        // 检索节点ID
        for (int i = 0; i < CSystemMain::nodeInfoList->size(); i++)
        {
            if (str == CSystemMain::nodeInfoList->at(i).id)
            {
                ui->NodeList->setCurrentIndex(ui->NodeList->model()->index(i, 0));
                on_NodeList_clicked(ui->NodeList->currentIndex());
                flag = true;
                break;
            }
        }
        if (flag == false)
        {
            ui->nodeSearcher->setText("未找到该节点");
        }
        else
        {
            ui->nodeSearcher->setText("搜索成功!");
        }
    }
    QTimer::singleShot(2000, [=]()
                       { ui->nodeSearcher->clear(); });
}

void MapView::on_NodeList_clicked(const QModelIndex &index)
{
    // 清空表格
    ui->nodeinfoview->clearContents();
    ui->nodeinfoview->setRowCount(16);
    // 获取点击的结点编号
    QString id = ui->NodeList->model()->data(index).toString();
    // 去除空格
    id.remove(QRegExp("\\s"));
    // 在节点列表中查找结点
    for (int i = 0; i < CSystemMain::nodeInfoList->size(); i++)
    {
        if (id == CSystemMain::nodeInfoList->at(i).id)
        {
            // 获取结点坐标
            float x = CSystemMain::nodeInfoList->at(i).lo;
            float y = CSystemMain::nodeInfoList->at(i).li;
            // 设置地图中心
            emit setCenter(x, y);
            // 填充表格
            ui->nodeinfoview->setItem(0, 0, new QTableWidgetItem("气体浓度："));
            ui->nodeinfoview->setItem(0, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).gasConcentration)));
            ui->nodeinfoview->setItem(1, 0, new QTableWidgetItem("温度："));
            ui->nodeinfoview->setItem(1, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).temperature)));
            ui->nodeinfoview->setItem(2, 0, new QTableWidgetItem("PH："));
            ui->nodeinfoview->setItem(2, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).pH)));
            ui->nodeinfoview->setItem(3, 0, new QTableWidgetItem("浊度："));
            ui->nodeinfoview->setItem(3, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).density)));
            ui->nodeinfoview->setItem(4, 0, new QTableWidgetItem("电导率："));
            ui->nodeinfoview->setItem(4, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).conductivity)));
            ui->nodeinfoview->setItem(5, 0, new QTableWidgetItem("含氧量："));
            ui->nodeinfoview->setItem(5, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).oxygenConcentration)));
            ui->nodeinfoview->setItem(6, 0, new QTableWidgetItem("重金属："));
            ui->nodeinfoview->setItem(6, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).metalConcentration)));
            ui->nodeinfoview->setItem(7, 0, new QTableWidgetItem("溶解性固体："));
            ui->nodeinfoview->setItem(7, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).SC)));
            ui->nodeinfoview->setItem(8, 0, new QTableWidgetItem("悬浮性固体："));
            ui->nodeinfoview->setItem(8, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).FSC)));
            ui->nodeinfoview->setItem(9, 0, new QTableWidgetItem("总氮："));
            ui->nodeinfoview->setItem(9, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).TN)));
            ui->nodeinfoview->setItem(10, 0, new QTableWidgetItem("总磷："));
            ui->nodeinfoview->setItem(10, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).TP)));
            ui->nodeinfoview->setItem(11, 0, new QTableWidgetItem("总有机碳："));
            ui->nodeinfoview->setItem(11, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).TOC)));
            ui->nodeinfoview->setItem(12, 0, new QTableWidgetItem("生物需氧量："));
            ui->nodeinfoview->setItem(12, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).BOD)));
            ui->nodeinfoview->setItem(13, 0, new QTableWidgetItem("化学需氧量："));
            ui->nodeinfoview->setItem(13, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).COD)));
            ui->nodeinfoview->setItem(14, 0, new QTableWidgetItem("细菌总数："));
            ui->nodeinfoview->setItem(14, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).BC)));
            ui->nodeinfoview->setItem(15, 0, new QTableWidgetItem("大肠杆菌数："));
            ui->nodeinfoview->setItem(15, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeInfoList->at(i).SLC)));
        }
    }
}

void MapView::on_NodeList_doubleClicked(const QModelIndex &index)
{
    // 获取点击的结点编号
    QString id = ui->NodeList->model()->data(index).toString();
    id.remove(QRegExp("\\s"));
    // 在节点列表中查找结点
    int i = 0;
    for (i = 0; i < CSystemMain::nodeInfoList->size(); i++)
    {
        if (id == CSystemMain::nodeInfoList->at(i).id)
        {
            float x = CSystemMain::nodeInfoList->at(i).lo;
            float y = CSystemMain::nodeInfoList->at(i).li;
            // 设置地图中心
            QTimer timer;
            timer.singleShot(1500, [=]()
                             { emit setCenter(x, y); });
            timer.start();
        }
    }
}
