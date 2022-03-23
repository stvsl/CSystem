#include "nodeinformation.h"
#include "ui_nodeinformation.h"
#include <QGraphicsDropShadowEffect>
#include <csystemmain/csystemmain.h>
#include <QStringList>
#include <QStringListModel>
#include <QTableWidgetItem>

QGraphicsDropShadowEffect *shadow1;
QGraphicsDropShadowEffect *shadow2;

nodeinformation::nodeinformation(QWidget *parent) : QWidget(parent),
                                                    ui(new Ui::nodeinformation)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    // 阴影效果
    shadow1 = new QGraphicsDropShadowEffect(ui->nodeinfogroup1);
    shadow1->setOffset(0, 0);
    shadow1->setColor(QColor(0, 0, 0, 60));
    shadow1->setBlurRadius(20);
    ui->nodeinfogroup1->setGraphicsEffect(shadow1);
    shadow2 = new QGraphicsDropShadowEffect(ui->nodeinfogroup2);
    shadow2->setOffset(0, 0);
    shadow2->setColor(QColor(125, 164, 255, 60));
    shadow2->setBlurRadius(20);
    ui->nodeinfogroup2->setGraphicsEffect(shadow2);
    QStringList nodelist;
    // 初始化结点列表
    for (int i = 0; i < CSystemMain::nodeInfoList->size(); i++)
    {
        nodelist.append(CSystemMain::nodeInfoList->at(i).id);
    }
    // 调整表格显示
    ui->NodeList->setModel(new QStringListModel(nodelist));
    ui->nodeinfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应宽度
    ui->nodeinfo->setSelectionBehavior(QAbstractItemView::SelectRows);            //整行选中
    ui->nodeinfo->setEditTriggers(QAbstractItemView::NoEditTriggers);             //禁止编辑
    ui->nodeinfo->setDragDropMode(QAbstractItemView::NoDragDrop);                 //禁止拖拽
    ui->nodeinfo->verticalHeader()->setVisible(false);                            //隐藏垂直表头
    ui->nodeinfo->horizontalHeader()->setHighlightSections(false);                //去除选中高亮
}
nodeinformation::~nodeinformation()
{
    delete ui;
    delete shadow1;
    delete shadow2;
}

void nodeinformation::on_NodeList_clicked(const QModelIndex &index)
{
    // 清空表格
    ui->nodeinfo->clearContents();
    // 设置表格行数
    ui->nodeinfo->setRowCount(12);
    // 获取点击的节点编号
    QString nodeid = ui->NodeList->model()->data(index).toString();
    nodeid.remove(QRegExp("\\s"));
    // 查找对应节点数据
    for (int i = 0; i < CSystemMain::nodeDataList->size(); i++)
    {
        if (CSystemMain::nodeDataList->at(i).id == nodeid)
        {
            // 填充表格
            // 向nodeinfo表格中填充数据
            ui->nodeinfo->setItem(0, 0, new QTableWidgetItem("PH直接排放上限"));
            ui->nodeinfo->setItem(0, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).PhDirectHigh)));
            ui->nodeinfo->setItem(0, 4, new QTableWidgetItem("PH直接排放下限"));
            ui->nodeinfo->setItem(0, 5, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).PhDirectLow)));
            qDebug() << "OK";
        }
    }
}
