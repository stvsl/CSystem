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
    // 表格设置组
    ui->fluxTable->setSelectionBehavior(QAbstractItemView::SelectRows);            //整行选中
    ui->fluxTable->setEditTriggers(QAbstractItemView::NoEditTriggers);             //禁止编辑
    ui->fluxTable->setDragDropMode(QAbstractItemView::NoDragDrop);                 //禁止拖拽
    ui->fluxTable->setSelectionMode(QAbstractItemView::SingleSelection);           //只能选中一行
    ui->fluxTable->horizontalHeader()->setHighlightSections(false);                //点击表头不高亮
    ui->fluxTable->verticalHeader()->setHighlightSections(false);                  //点击表头不高亮
    ui->fluxTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //设置表格列宽度自适应
    ui->fluxTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->fluxTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->proTable->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中
    ui->proTable->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止编辑
    ui->proTable->setDragDropMode(QAbstractItemView::NoDragDrop);       //禁止拖拽
    ui->proTable->setSelectionMode(QAbstractItemView::SingleSelection); //只能选中一行
    ui->proTable->horizontalHeader()->setHighlightSections(false);      //点击表头不高亮
    ui->proTable->verticalHeader()->setHighlightSections(false);        //点击表头不高亮
    ui->proTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->proTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    initTable();
}

DataView::~DataView()
{
    delete ui;
}

void DataView::initTable()
{
    // 清空表格
    ui->fluxTable->clearContents();
    ui->proTable->clearContents();
    // 设置表格行数
    ui->fluxTable->setRowCount(CSystemMain::nodeinfluxData_temp->size());
    ui->proTable->setRowCount(CSystemMain::nodePro_temp->size());
    for (int i = 0; i < CSystemMain::nodeinfluxData_temp->size(); i++)
    {
        ui->fluxTable->setItem(i, 0, new QTableWidgetItem(CSystemMain::nodeinfluxData_temp->at(i).time.mid(0, 19)));
        ui->fluxTable->setItem(i, 1, new QTableWidgetItem(CSystemMain::nodeinfluxData_temp->at(i).id));
        ui->fluxTable->setItem(i, 2, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).gasConcentration, 'f', 2)));
        ui->fluxTable->setItem(i, 3, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).temperature, 'f', 2)));
        ui->fluxTable->setItem(i, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).pH, 'f', 2)));
        ui->fluxTable->setItem(i, 5, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).density, 'f', 2)));
        ui->fluxTable->setItem(i, 6, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).conductivity, 'f', 2)));
        ui->fluxTable->setItem(i, 7, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).oxygenConcentration, 'f', 2)));
        ui->fluxTable->setItem(i, 8, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).metalConcentration, 'f', 2)));
        ui->fluxTable->setItem(i, 9, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).SC, 'f', 2)));
        ui->fluxTable->setItem(i, 10, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).FSC, 'f', 2)));
        ui->fluxTable->setItem(i, 11, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).TN, 'f', 2)));
        ui->fluxTable->setItem(i, 12, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).TP, 'f', 2)));
        ui->fluxTable->setItem(i, 13, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).TOC, 'f', 2)));
        ui->fluxTable->setItem(i, 14, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).BOD, 'f', 2)));
        ui->fluxTable->setItem(i, 15, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).COD, 'f', 2)));
        ui->fluxTable->setItem(i, 16, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).BC)));
        ui->fluxTable->setItem(i, 17, new QTableWidgetItem(QString::number(CSystemMain::nodeinfluxData_temp->at(i).SLC)));
        // 居中
        for (int j = 0; j < ui->fluxTable->columnCount(); j++)
        {
            ui->fluxTable->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    for (int i = 0; i < CSystemMain::nodePro_temp->size(); i++)
    {
        ui->proTable->setItem(i, 0, new QTableWidgetItem(CSystemMain::nodePro_temp->at(i).Time.mid(0, 19)));
        ui->proTable->setItem(i, 1, new QTableWidgetItem(CSystemMain::nodePro_temp->at(i).id));
        ui->proTable->setItem(i, 2, new QTableWidgetItem(QString::number((CSystemMain::nodePro_temp->at(i).PhDirectHigh + CSystemMain::nodePro_temp->at(i).PhDirectLow) / 2, 'f', 2) + "/" + QString::number((CSystemMain::nodePro_temp->at(i).PhIndirectHigh + CSystemMain::nodePro_temp->at(i).PhIndirectLow) / 2, 'f', 2)));
        ui->proTable->setItem(i, 3, new QTableWidgetItem((QString::number(CSystemMain::nodePro_temp->at(i).CODDirect, 'f', 2) + "/" + QString::number(CSystemMain::nodePro_temp->at(i).CODIndirect, 'f', 2))));
        ui->proTable->setItem(i, 4, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).TPDirect, 'f', 2) + "/" + QString::number((CSystemMain::nodePro_temp->at(i).TPIndirect), 'f', 2)));
        ui->proTable->setItem(i, 5, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).TNDirect, 'f', 2) + "/" + QString::number((CSystemMain::nodePro_temp->at(i).IPIndirect), 'f', 2)));
        ui->proTable->setItem(i, 6, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).ANDirect, 'f', 2) + "/" + QString::number((CSystemMain::nodePro_temp->at(i).AFINDirect), 'f', 2)));

        ui->proTable->setItem(i, 7, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).OCCDirect, 'f', 2) + "/" + QString::number(CSystemMain::nodePro_temp->at(i).OCCIndirect, 'f', 2)));
        ui->proTable->setItem(i, 8, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).FSCDirectT, 'f', 2) + "/" + QString::number(CSystemMain::nodePro_temp->at(i).FSCIndirectT, 'f', 2)));
        ui->proTable->setItem(i, 9, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).FSCDirectO, 'f', 2) + "/" + QString::number(CSystemMain::nodePro_temp->at(i).FSCIndirectO, 'f', 2)));
        ui->proTable->setItem(i, 10, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).SADirect, 'f', 2) + "/" + QString::number(CSystemMain::nodePro_temp->at(i).SAIndirect, 'f', 2)));
        ui->proTable->setItem(i, 11, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).FDirect, 'f', 2) + "/" + QString::number(CSystemMain::nodePro_temp->at(i).FIndirect, 'f', 2)));
        ui->proTable->setItem(i, 12, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Cu, 'f', 2)));
        ui->proTable->setItem(i, 13, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Zn, 'f', 2)));
        ui->proTable->setItem(i, 14, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Sn, 'f', 2)));
        ui->proTable->setItem(i, 15, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Sb, 'f', 2)));
        ui->proTable->setItem(i, 16, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Hg, 'f', 2)));
        ui->proTable->setItem(i, 17, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Cd, 'f', 2)));
        ui->proTable->setItem(i, 18, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Pb, 'f', 2)));
        ui->proTable->setItem(i, 19, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).As, 'f', 2)));
        ui->proTable->setItem(i, 20, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Cr6, 'f', 2)));
        ui->proTable->setItem(i, 21, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Gc, 'f', 2)));
        ui->proTable->setItem(i, 22, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Density, 'f', 2)));
        ui->proTable->setItem(i, 23, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Conductivity, 'f', 2)));
        ui->proTable->setItem(i, 24, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Mc, 'f', 2)));
        ui->proTable->setItem(i, 25, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Sc, 'f', 2)));
        ui->proTable->setItem(i, 26, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Toc, 'f', 2)));
        ui->proTable->setItem(i, 27, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).BOD5Direct, 'f', 2) + "/" + QString::number(CSystemMain::nodePro_temp->at(i).BOD5Indirect, 'f', 2)));
        ui->proTable->setItem(i, 28, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).BOD, 'f', 2)));
        ui->proTable->setItem(i, 29, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).PDirect, 'f', 2) + "/" + QString::number(CSystemMain::nodePro_temp->at(i).PINDirect, 'f', 2)));
        ui->proTable->setItem(i, 30, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).BC, 'f', 2)));
        ui->proTable->setItem(i, 31, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).SLC, 'f', 2)));
        ui->proTable->setItem(i, 32, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).COLORDirect, 'f', 2) + "/" + QString::number(CSystemMain::nodePro_temp->at(i).COLORIndirect, 'f', 2)));
        ui->proTable->setItem(i, 33, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).AFDirect, 'f', 2) + "/" + QString::number(CSystemMain::nodePro_temp->at(i).AFINDirect, 'f', 2)));
        ui->proTable->setItem(i, 34, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).CLDirect, 'f', 2) + "/" + QString::number(CSystemMain::nodePro_temp->at(i).CLIndirect, 'f', 2)));
        ui->proTable->setItem(i, 35, new QTableWidgetItem(QString::number(CSystemMain::nodePro_temp->at(i).Cr, 'f', 2)));
    }
}