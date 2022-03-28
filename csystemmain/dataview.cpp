#include "dataview.h"
#include "ui_dataview.h"
#include <QGraphicsDropShadowEffect>
#include <csystemmain/csystemmain.h>
#include <netWorkUtils/nodeinterface.h>

QGraphicsDropShadowEffect *shadow_effect;

DataView::DataView(QWidget *parent) : QWidget(parent),
                                      ui(new Ui::DataView)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    // 阴影效果
    shadow_effect = new QGraphicsDropShadowEffect(ui->tabWidget);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(125, 164, 255, 100));
    shadow_effect->setBlurRadius(10);
    ui->tabWidget->setGraphicsEffect(shadow_effect);
    if (CSystemMain::nodeinfluxData_temp == nullptr)
    {
        NodeInterface nif;
        // 获取时间戳
        QString startTime = QString::number(QDateTime::currentDateTime().addMonths(-4).toTime_t());
        QString endTime = QString::number(QDateTime::currentDateTime().toTime_t());
        // 获取数据
        CSystemMain::nodeinfluxData_temp = nif.getNodeInfluxData(startTime, endTime);
        CSystemMain::nodePro_temp = nif.getNodeProData(startTime, endTime);
    }
    // 初始化表格
    initTable();
}

DataView::~DataView()
{
    delete ui;
}

void DataView::initTable()
{
}