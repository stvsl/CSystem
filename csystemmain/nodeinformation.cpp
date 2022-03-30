#include "nodeinformation.h"
#include "ui_nodeinformation.h"
#include <QGraphicsDropShadowEffect>
#include <csystemmain/csystemmain.h>
#include <QStringList>
#include <QStringListModel>
#include <QTableWidgetItem>

QGraphicsDropShadowEffect *shadow1;
QGraphicsDropShadowEffect *shadow2;
QGraphicsDropShadowEffect *shadow3;

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
    // 阴影效果
    shadow3 = new QGraphicsDropShadowEffect(ui->label);
    shadow3->setOffset(0, 0);
    shadow3->setColor(QColor(125, 164, 255, 80));
    shadow3->setBlurRadius(10);
    ui->label->setGraphicsEffect(shadow3);
    QStringList nodelist;
    // 初始化结点列表
    for (int i = 0; i < CSystemMain::nodeInfoList->size(); i++)
    {
        nodelist.append(CSystemMain::nodeInfoList->at(i).id);
    }
    // 调整表格显示
    ui->NodeList->setModel(new QStringListModel(nodelist));
    ui->nodeinfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //自适应宽度
    ui->configwidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //
    ui->nodeinfo->setSelectionBehavior(QAbstractItemView::SelectRows);                //整行选中
    ui->configwidget->setSelectionBehavior(QAbstractItemView::SelectRows);            //
    ui->nodeinfo->setEditTriggers(QAbstractItemView::NoEditTriggers);                 //禁止编辑
    ui->configwidget->setEditTriggers(QAbstractItemView::NoEditTriggers);             //
    ui->nodeinfo->setDragDropMode(QAbstractItemView::NoDragDrop);                     //禁止拖拽
    ui->configwidget->setDragDropMode(QAbstractItemView::NoDragDrop);                 //
    ui->nodeinfo->verticalHeader()->setVisible(false);                                //隐藏垂直表头
    ui->configwidget->verticalHeader()->setVisible(false);                            //
    ui->nodeinfo->horizontalHeader()->setHighlightSections(false);                    //去除选中高亮
    ui->configwidget->horizontalHeader()->setHighlightSections(false);                //
    ui->nodeinfo->verticalHeader()->setDefaultSectionSize(12);                        //设置行高
}
nodeinformation::~nodeinformation()
{
    delete ui;
    delete shadow1;
    delete shadow2;
    delete shadow3;
}

void nodeinformation::on_NodeList_clicked(const QModelIndex &index)
{
    // 清空QListView内对象
    ui->resplist->clear();
    ui->nodeinfo->clearContents();
    ui->configwidget->clearContents();
    ui->locateinfo->clear();
    ui->selflist->clear();
    // 设置表格行数
    ui->nodeinfo->setRowCount(25);
    ui->configwidget->setRowCount(14);
    // 获取点击的节点编号
    QString nodeid = ui->NodeList->model()->data(index).toString();
    nodeid.remove(QRegExp("\\s"));
    // 查找对应节点数据
    int i = 0;
    for (i = 0; i < CSystemMain::nodeDataList->size(); i++)
    {
        if (CSystemMain::nodeDataList->at(i).id == nodeid)
        {
            // 填充表格
            ui->nodeinfo->setItem(0, 0, new QTableWidgetItem("PH直接排放上限"));
            ui->nodeinfo->setItem(0, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).PhDirectHigh)));
            ui->nodeinfo->setItem(0, 3, new QTableWidgetItem("PH直接排放下限"));
            ui->nodeinfo->setItem(0, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).PhDirectLow)));
            ui->nodeinfo->setItem(1, 0, new QTableWidgetItem("PH间接排放上限"));
            ui->nodeinfo->setItem(1, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).PhIndirectHigh)));
            ui->nodeinfo->setItem(1, 3, new QTableWidgetItem("PH间接排放下限"));
            ui->nodeinfo->setItem(1, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).PhIndirectLow)));
            ui->nodeinfo->setItem(2, 0, new QTableWidgetItem("化学需氧量(直接)"));
            ui->nodeinfo->setItem(2, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).CODDirect)));
            ui->nodeinfo->setItem(2, 3, new QTableWidgetItem("化学需氧量(间接)"));
            ui->nodeinfo->setItem(2, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).CODIndirect)));
            ui->nodeinfo->setItem(3, 0, new QTableWidgetItem("总磷(直接)"));
            ui->nodeinfo->setItem(3, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).TPDirect)));
            ui->nodeinfo->setItem(3, 3, new QTableWidgetItem("总磷(间接)"));
            ui->nodeinfo->setItem(3, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).TPIndirect)));
            ui->nodeinfo->setItem(4, 0, new QTableWidgetItem("总氮(直接)"));
            ui->nodeinfo->setItem(4, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).TNDirect)));
            ui->nodeinfo->setItem(4, 3, new QTableWidgetItem("总氮(间接)"));
            ui->nodeinfo->setItem(4, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).IPIndirect)));
            ui->nodeinfo->setItem(5, 0, new QTableWidgetItem("氨氮(直接)"));
            ui->nodeinfo->setItem(5, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).ANDirect)));
            ui->nodeinfo->setItem(5, 3, new QTableWidgetItem("氨氮(间接)"));
            ui->nodeinfo->setItem(5, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).ANINDirect)));
            ui->nodeinfo->setItem(6, 0, new QTableWidgetItem("石油类(直接)"));
            ui->nodeinfo->setItem(6, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).OCCDirect)));
            ui->nodeinfo->setItem(6, 3, new QTableWidgetItem("石油类(间接)"));
            ui->nodeinfo->setItem(6, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).OCCIndirect)));
            ui->nodeinfo->setItem(7, 0, new QTableWidgetItem("悬浮物采选(直接)"));
            ui->nodeinfo->setItem(7, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).FSCDirectT)));
            ui->nodeinfo->setItem(7, 3, new QTableWidgetItem("悬浮物采选(间接)"));
            ui->nodeinfo->setItem(7, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).FSCIndirectT)));
            ui->nodeinfo->setItem(8, 0, new QTableWidgetItem("悬浮物其它(直接)"));
            ui->nodeinfo->setItem(8, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).FSCDirectO)));
            ui->nodeinfo->setItem(8, 3, new QTableWidgetItem("悬浮物其它(间接)"));
            ui->nodeinfo->setItem(8, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).FSCIndirectO)));
            ui->nodeinfo->setItem(8, 0, new QTableWidgetItem("硫化物(直接)"));
            ui->nodeinfo->setItem(8, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).SADirect)));
            ui->nodeinfo->setItem(8, 3, new QTableWidgetItem("硫化物(间接)"));
            ui->nodeinfo->setItem(8, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).SAIndirect)));
            ui->nodeinfo->setItem(9, 0, new QTableWidgetItem("氟化物(直接)"));
            ui->nodeinfo->setItem(9, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).FDirect)));
            ui->nodeinfo->setItem(9, 3, new QTableWidgetItem("氟化物(间接)"));
            ui->nodeinfo->setItem(9, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).FIndirect)));
            ui->nodeinfo->setItem(10, 0, new QTableWidgetItem("总铜"));
            ui->nodeinfo->setItem(10, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Cu)));
            ui->nodeinfo->setItem(10, 3, new QTableWidgetItem("总锌"));
            ui->nodeinfo->setItem(10, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Zn)));
            ui->nodeinfo->setItem(11, 0, new QTableWidgetItem("总锡"));
            ui->nodeinfo->setItem(11, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Sn)));
            ui->nodeinfo->setItem(11, 3, new QTableWidgetItem("总锑"));
            ui->nodeinfo->setItem(11, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Sb)));
            ui->nodeinfo->setItem(12, 0, new QTableWidgetItem("总汞"));
            ui->nodeinfo->setItem(12, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Hg)));
            ui->nodeinfo->setItem(12, 3, new QTableWidgetItem("总镉"));
            ui->nodeinfo->setItem(12, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Cd)));
            ui->nodeinfo->setItem(13, 0, new QTableWidgetItem("总铅"));
            ui->nodeinfo->setItem(13, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Pb)));
            ui->nodeinfo->setItem(13, 3, new QTableWidgetItem("总砷"));
            ui->nodeinfo->setItem(13, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).As)));
            ui->nodeinfo->setItem(14, 0, new QTableWidgetItem("六价铬"));
            ui->nodeinfo->setItem(14, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Cr6)));
            ui->nodeinfo->setItem(14, 3, new QTableWidgetItem("气体浓度"));
            ui->nodeinfo->setItem(14, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Gc)));
            ui->nodeinfo->setItem(15, 0, new QTableWidgetItem("浊度"));
            ui->nodeinfo->setItem(15, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Density)));
            ui->nodeinfo->setItem(15, 3, new QTableWidgetItem("电导率"));
            ui->nodeinfo->setItem(15, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Conductivity)));
            ui->nodeinfo->setItem(16, 0, new QTableWidgetItem("重金属"));
            ui->nodeinfo->setItem(16, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Mc)));
            ui->nodeinfo->setItem(16, 3, new QTableWidgetItem("溶解性固体"));
            ui->nodeinfo->setItem(16, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Sc)));
            ui->nodeinfo->setItem(17, 0, new QTableWidgetItem("总有机碳"));
            ui->nodeinfo->setItem(17, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Toc)));
            ui->nodeinfo->setItem(17, 3, new QTableWidgetItem("五日生化需氧量直接"));
            ui->nodeinfo->setItem(17, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).BOD5Direct)));
            ui->nodeinfo->setItem(18, 0, new QTableWidgetItem("五日生化需氧量间接"));
            ui->nodeinfo->setItem(18, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).BOD5Indirect)));
            ui->nodeinfo->setItem(18, 3, new QTableWidgetItem("生物需氧量"));
            ui->nodeinfo->setItem(18, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).BOD)));
            ui->nodeinfo->setItem(19, 0, new QTableWidgetItem("总磷直接"));
            ui->nodeinfo->setItem(19, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).PDirect)));
            ui->nodeinfo->setItem(19, 3, new QTableWidgetItem("细菌总数"));
            ui->nodeinfo->setItem(19, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).BC)));
            ui->nodeinfo->setItem(20, 0, new QTableWidgetItem("大肠杆菌数"));
            ui->nodeinfo->setItem(20, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).SLC)));
            ui->nodeinfo->setItem(20, 3, new QTableWidgetItem("色度直接"));
            ui->nodeinfo->setItem(20, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).COLORDirect)));
            ui->nodeinfo->setItem(21, 0, new QTableWidgetItem("色度间接"));
            ui->nodeinfo->setItem(21, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).COLORIndirect)));
            ui->nodeinfo->setItem(21, 3, new QTableWidgetItem("动植物油直接"));
            ui->nodeinfo->setItem(21, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).AFDirect)));
            ui->nodeinfo->setItem(22, 0, new QTableWidgetItem("动植物油间接"));
            ui->nodeinfo->setItem(22, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).AFINDirect)));
            ui->nodeinfo->setItem(22, 3, new QTableWidgetItem("氯离子直接"));
            ui->nodeinfo->setItem(22, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).CLDirect)));
            ui->nodeinfo->setItem(23, 0, new QTableWidgetItem("氯离子间接"));
            ui->nodeinfo->setItem(23, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).CLIndirect)));
            ui->nodeinfo->setItem(23, 3, new QTableWidgetItem("总磷间接"));
            ui->nodeinfo->setItem(23, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).PINDirect)));
            ui->nodeinfo->setItem(24, 0, new QTableWidgetItem("总铬"));
            ui->nodeinfo->setItem(24, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Cr)));
            ui->nodeinfo->setItem(24, 3, new QTableWidgetItem("单位"));
            ui->nodeinfo->setItem(24, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Ton)));
            break;
        }
    }
    // // 居中显示
    // for (int i = 0; i < 6; i++)
    // {
    //     for (int j = 0; j < 23; j++)
    //     {
    //         ui->nodeinfo->item(i, j)->setTextAlignment(Qt::AlignCenter);
    //     }
    // }
    QStringList resplist;
    resplist << "   机构号:    " + CSystemMain::nodeInfoList->at(i).belong;
    resplist << "   企业名称:  " + CSystemMain::nodeInfoList->at(i).COMNAME;
    resplist << "   负责人:    " + CSystemMain::nodeInfoList->at(i).principal;
    resplist << "   安装人:    " + CSystemMain::nodeInfoList->at(i).installer + "                 维护人:    " + CSystemMain::nodeInfoList->at(i).maintainer;
    resplist << "   执行标准:  " + CSystemMain::nodeInfoList->at(i).STANDARD;
    ui->resplist->addItems(resplist);

    ui->configwidget->setItem(0, 0, new QTableWidgetItem("特殊气体浓度"));
    ui->configwidget->setItem(0, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(0) == 0 ? "否" : "是"));
    ui->configwidget->setItem(1, 0, new QTableWidgetItem("温度"));
    ui->configwidget->setItem(1, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(1) == 0 ? "否" : "是"));
    ui->configwidget->setItem(2, 0, new QTableWidgetItem("PH"));
    ui->configwidget->setItem(2, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(2) == 0 ? "否" : "是"));
    ui->configwidget->setItem(3, 0, new QTableWidgetItem("浊度"));
    ui->configwidget->setItem(3, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(3) == 0 ? "否" : "是"));
    ui->configwidget->setItem(4, 0, new QTableWidgetItem("电导率"));
    ui->configwidget->setItem(4, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(4) == 0 ? "否" : "是"));
    ui->configwidget->setItem(5, 0, new QTableWidgetItem("含氧量"));
    ui->configwidget->setItem(5, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(5) == 0 ? "否" : "是"));
    ui->configwidget->setItem(6, 0, new QTableWidgetItem("重金属"));
    ui->configwidget->setItem(6, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(6) == 0 ? "否" : "是"));
    ui->configwidget->setItem(7, 0, new QTableWidgetItem("溶解性固体"));
    ui->configwidget->setItem(7, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(7) == 0 ? "否" : "是"));
    ui->configwidget->setItem(8, 0, new QTableWidgetItem("悬浮性固体"));
    ui->configwidget->setItem(8, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(8) == 0 ? "否" : "是"));
    ui->configwidget->setItem(9, 0, new QTableWidgetItem("总氮"));
    ui->configwidget->setItem(9, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(9) == 0 ? "否" : "是"));
    ui->configwidget->setItem(10, 0, new QTableWidgetItem("总磷"));
    ui->configwidget->setItem(10, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(10) == 0 ? "否" : "是"));
    ui->configwidget->setItem(11, 0, new QTableWidgetItem("总有机碳"));
    ui->configwidget->setItem(11, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(11) == 0 ? "否" : "是"));
    ui->configwidget->setItem(12, 0, new QTableWidgetItem("生物需氧量"));
    ui->configwidget->setItem(12, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(12) == 0 ? "否" : "是"));
    ui->configwidget->setItem(13, 0, new QTableWidgetItem("化学需氧量"));
    ui->configwidget->setItem(13, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(13) == 0 ? "否" : "是"));
    ui->configwidget->setItem(14, 0, new QTableWidgetItem("细菌总数"));
    ui->configwidget->setItem(14, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(14) == 0 ? "否" : "是"));
    ui->configwidget->setItem(15, 0, new QTableWidgetItem("大肠杆菌数"));
    ui->configwidget->setItem(15, 1, new QTableWidgetItem(CSystemMain::nodeInfoList->at(i).dataConfig.at(15) == 0 ? "否" : "是"));

    // 居中
    for (int i = 0; i < ui->configwidget->rowCount(); i++)
    {
        for (int j = 0; j < ui->configwidget->columnCount(); j++)
        {
            ui->configwidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QStringList locatelist;
    locatelist << " 经度(伪):    " + QString::number(CSystemMain::nodeInfoList->at(i).lo);
    locatelist << " 纬度(伪):    " + QString::number(CSystemMain::nodeInfoList->at(i).li);
    locatelist << " 地址:          " + CSystemMain::nodeInfoList->at(i).locate;
    ui->locateinfo->addItems(locatelist);

    QStringList selflist;
    selflist << "   安装日期:               " + CSystemMain::nodeInfoList->at(i).installDate.toString("yyyy-MM-dd-hh-mm-ss");
    selflist << "   上次更新日期:       " + CSystemMain::nodeInfoList->at(i).lastUpload.toString("yyyy-MM-dd-hh-mm-ss");
    selflist << "   上次自检日期:       " + CSystemMain::nodeInfoList->at(i).selfDate.toString("yyyy-MM-dd-hh-mm-ss");
    selflist << "   自检结果:               " + CSystemMain::nodeInfoList->at(i).selfInfo;
    ui->selflist->addItems(selflist);
}
