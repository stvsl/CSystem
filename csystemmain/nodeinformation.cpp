#include "nodeinformation.h"
#include "ui_nodeinformation.h"
#include <QGraphicsDropShadowEffect>
#include <csystemmain/csystemmain.h>
#include <QStringList>
#include <QStringListModel>
#include <QTableWidgetItem>
#include <QStackedBarSeries>
#include <QBarSet>
#include <QHorizontalBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QBarSeries>
#include <QSplineSeries>
#include <QScatterSeries>
#include <QPieSeries>
#include <QDateTime>
#include <QFileDialog>

QGraphicsDropShadowEffect *shadow1;
QGraphicsDropShadowEffect *shadow2;
QGraphicsDropShadowEffect *shadow3;
QGraphicsDropShadowEffect *shadow4;

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
    // 阴影效果
    shadow4 = new QGraphicsDropShadowEffect(ui->modSwitch_btn);
    shadow4->setOffset(0, 0);
    shadow4->setColor(QColor(125, 164, 255, 80));
    shadow4->setBlurRadius(10);
    ui->modSwitch_btn->setGraphicsEffect(shadow4);
    ui->webEngineView->setUrl(QUrl("http://127.0.0.1:10241/pages/default/map"));
    channel_ni = new QWebChannel(this);                   //通讯对象
    channel_ni->registerObject("trans", this);            //通信介质注册
    ui->webEngineView->page()->setWebChannel(channel_ni); //通讯附加
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
    ui->nodeinfo->verticalHeader()->setDefaultSectionSize(25);                        //设置表格默认行高
    if (CSystemMain::nodeinfluxData_temp == nullptr || CSystemMain::nodePro_temp == nullptr || CSystemMain::standard == nullptr)
    {
        try
        {
            NodeInterface nif;
            // 获取时间戳
            QString startTime = QString::number(QDateTime::currentDateTimeUtc().addMonths(-4).toTime_t());
            QString endTime = QString::number(QDateTime::currentDateTimeUtc().toTime_t());
            // 获取数据
            CSystemMain::nodeinfluxData_temp = nif.getNodeInfluxData(startTime, endTime);
            CSystemMain::nodePro_temp = nif.getNodeProData(startTime, endTime);
            CSystemMain::standard = nif.getStandard(CSystemMain::nodeInfoList->at(0).STANDARD);
        }
        catch (...)
        {
            QMessageBox::warning(this, "警告", "获取数据失败，请检查网络连接！");
        }
    }
    // 自动点击第一个
    ui->NodeList->setCurrentIndex(ui->NodeList->model()->index(0, 0));
    on_NodeList_clicked(ui->NodeList->currentIndex());
}
nodeinformation::~nodeinformation()
{
    delete ui;
    delete shadow1;
    delete shadow2;
    delete shadow3;
    delete shadow4;
}

void nodeinformation::on_NodeList_clicked(const QModelIndex &index)
{
    // 清空原有数据
    ui->resplist->clear();
    ui->nodeinfo->clearContents();
    ui->configwidget->clearContents();
    ui->locateinfo->clear();
    ui->selflist->clear();
    ui->graphicsView->chart()->removeAllSeries();
    ui->graphicsViewIron->chart()->removeAllSeries();
    ui->graphicsViewOther1->chart()->removeAllSeries();
    ui->graphicsViewOther2->chart()->removeAllSeries();
    ui->graphicsViewOther3->chart()->removeAllSeries();
    ui->graphView_Diag1->chart()->removeAllSeries();
    ui->graphicsViewDiag2->chart()->removeAllSeries();
    ui->graphicsViewDiag3->chart()->removeAllSeries();
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
            ui->nodeinfo->setItem(0, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->PhDirectHigh)));
            ui->nodeinfo->setItem(0, 3, new QTableWidgetItem("PH直接排放下限"));
            ui->nodeinfo->setItem(0, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).PhDirectLow)));
            ui->nodeinfo->setItem(0, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->PhDirectLow)));
            ui->nodeinfo->setItem(1, 0, new QTableWidgetItem("PH间接排放上限"));
            ui->nodeinfo->setItem(1, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).PhIndirectHigh)));
            ui->nodeinfo->setItem(1, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->PhIndirectHigh)));
            ui->nodeinfo->setItem(1, 3, new QTableWidgetItem("PH间接排放下限"));
            ui->nodeinfo->setItem(1, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).PhIndirectLow)));
            ui->nodeinfo->setItem(1, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->PhDirectLow)));
            ui->nodeinfo->setItem(2, 0, new QTableWidgetItem("化学需氧量(直接)"));
            ui->nodeinfo->setItem(2, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).CODDirect)));
            ui->nodeinfo->setItem(2, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->CODDirect)));
            ui->nodeinfo->setItem(2, 3, new QTableWidgetItem("化学需氧量(间接)"));
            ui->nodeinfo->setItem(2, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).CODIndirect)));
            ui->nodeinfo->setItem(2, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->CODIndirect)));
            ui->nodeinfo->setItem(3, 0, new QTableWidgetItem("总磷(直接)"));
            ui->nodeinfo->setItem(3, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).TPDirect)));
            ui->nodeinfo->setItem(3, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->TPDirect)));
            ui->nodeinfo->setItem(3, 3, new QTableWidgetItem("总磷(间接)"));
            ui->nodeinfo->setItem(3, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).TPIndirect)));
            ui->nodeinfo->setItem(3, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->TPIndirect)));
            ui->nodeinfo->setItem(4, 0, new QTableWidgetItem("总氮(直接)"));
            ui->nodeinfo->setItem(4, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).TNDirect)));
            ui->nodeinfo->setItem(4, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->TNDirect)));
            ui->nodeinfo->setItem(4, 3, new QTableWidgetItem("总氮(间接)"));
            ui->nodeinfo->setItem(4, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).IPIndirect)));
            ui->nodeinfo->setItem(4, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->IPIndirect)));
            ui->nodeinfo->setItem(5, 0, new QTableWidgetItem("氨氮(直接)"));
            ui->nodeinfo->setItem(5, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).ANDirect)));
            ui->nodeinfo->setItem(5, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->ANDirect)));
            ui->nodeinfo->setItem(5, 3, new QTableWidgetItem("氨氮(间接)"));
            ui->nodeinfo->setItem(5, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).ANINDirect)));
            ui->nodeinfo->setItem(5, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->ANINDirect)));
            ui->nodeinfo->setItem(6, 0, new QTableWidgetItem("石油类(直接)"));
            ui->nodeinfo->setItem(6, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).OCCDirect)));
            ui->nodeinfo->setItem(6, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->OCCDirect)));
            ui->nodeinfo->setItem(6, 3, new QTableWidgetItem("石油类(间接)"));
            ui->nodeinfo->setItem(6, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).OCCIndirect)));
            ui->nodeinfo->setItem(6, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->OCCIndirect)));
            ui->nodeinfo->setItem(7, 0, new QTableWidgetItem("悬浮物采选(直接)"));
            ui->nodeinfo->setItem(7, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).FSCDirectT)));
            ui->nodeinfo->setItem(7, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->FSCDirectT)));
            ui->nodeinfo->setItem(7, 3, new QTableWidgetItem("悬浮物采选(间接)"));
            ui->nodeinfo->setItem(7, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).FSCIndirectT)));
            ui->nodeinfo->setItem(7, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->FSCIndirectT)));
            ui->nodeinfo->setItem(8, 0, new QTableWidgetItem("悬浮物其它(直接)"));
            ui->nodeinfo->setItem(8, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).FSCDirectO)));
            ui->nodeinfo->setItem(8, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->FSCDirectO)));
            ui->nodeinfo->setItem(8, 3, new QTableWidgetItem("悬浮物其它(间接)"));
            ui->nodeinfo->setItem(8, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).FSCIndirectO)));
            ui->nodeinfo->setItem(8, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->FSCIndirectO)));
            ui->nodeinfo->setItem(8, 0, new QTableWidgetItem("硫化物(直接)"));
            ui->nodeinfo->setItem(8, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).SADirect)));
            ui->nodeinfo->setItem(8, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->SADirect)));
            ui->nodeinfo->setItem(8, 3, new QTableWidgetItem("硫化物(间接)"));
            ui->nodeinfo->setItem(8, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).SAIndirect)));
            ui->nodeinfo->setItem(8, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->SAIndirect)));
            ui->nodeinfo->setItem(9, 0, new QTableWidgetItem("氟化物(直接)"));
            ui->nodeinfo->setItem(9, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).FDirect)));
            ui->nodeinfo->setItem(9, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->FDirect)));
            ui->nodeinfo->setItem(9, 3, new QTableWidgetItem("氟化物(间接)"));
            ui->nodeinfo->setItem(9, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).FIndirect)));
            ui->nodeinfo->setItem(9, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->FIndirect)));
            ui->nodeinfo->setItem(10, 0, new QTableWidgetItem("总铜"));
            ui->nodeinfo->setItem(10, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Cu)));
            ui->nodeinfo->setItem(10, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->Cu)));
            ui->nodeinfo->setItem(10, 3, new QTableWidgetItem("总锌"));
            ui->nodeinfo->setItem(10, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Zn)));
            ui->nodeinfo->setItem(10, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->Zn)));
            ui->nodeinfo->setItem(11, 0, new QTableWidgetItem("总锡"));
            ui->nodeinfo->setItem(11, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Sn)));
            ui->nodeinfo->setItem(11, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->Sn)));
            ui->nodeinfo->setItem(11, 3, new QTableWidgetItem("总锑"));
            ui->nodeinfo->setItem(11, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Sb)));
            ui->nodeinfo->setItem(11, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->Sb)));
            ui->nodeinfo->setItem(12, 0, new QTableWidgetItem("总汞"));
            ui->nodeinfo->setItem(12, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Hg)));
            ui->nodeinfo->setItem(12, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->Hg)));
            ui->nodeinfo->setItem(12, 3, new QTableWidgetItem("总镉"));
            ui->nodeinfo->setItem(12, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Cd)));
            ui->nodeinfo->setItem(12, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->Cd)));
            ui->nodeinfo->setItem(13, 0, new QTableWidgetItem("总铅"));
            ui->nodeinfo->setItem(13, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Pb)));
            ui->nodeinfo->setItem(13, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->Pb)));
            ui->nodeinfo->setItem(13, 3, new QTableWidgetItem("总砷"));
            ui->nodeinfo->setItem(13, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).As)));
            ui->nodeinfo->setItem(13, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->As)));
            ui->nodeinfo->setItem(14, 0, new QTableWidgetItem("六价铬"));
            ui->nodeinfo->setItem(14, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Cr6)));
            ui->nodeinfo->setItem(14, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->Cr6)));
            ui->nodeinfo->setItem(14, 3, new QTableWidgetItem("气体浓度"));
            ui->nodeinfo->setItem(14, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Gc)));
            ui->nodeinfo->setItem(14, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->Gc)));
            ui->nodeinfo->setItem(15, 0, new QTableWidgetItem("浊度"));
            ui->nodeinfo->setItem(15, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Density)));
            ui->nodeinfo->setItem(15, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->Density)));
            ui->nodeinfo->setItem(15, 3, new QTableWidgetItem("电导率"));
            ui->nodeinfo->setItem(15, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Conductivity)));
            ui->nodeinfo->setItem(15, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->Conductivity)));
            ui->nodeinfo->setItem(16, 0, new QTableWidgetItem("重金属"));
            ui->nodeinfo->setItem(16, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Mc)));
            ui->nodeinfo->setItem(16, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->Mc)));
            ui->nodeinfo->setItem(16, 3, new QTableWidgetItem("溶解性固体"));
            ui->nodeinfo->setItem(16, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Sc)));
            ui->nodeinfo->setItem(16, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->Sc)));
            ui->nodeinfo->setItem(17, 0, new QTableWidgetItem("总有机碳"));
            ui->nodeinfo->setItem(17, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Toc)));
            ui->nodeinfo->setItem(17, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->Toc)));
            ui->nodeinfo->setItem(17, 3, new QTableWidgetItem("五日生化需氧量直接"));
            ui->nodeinfo->setItem(17, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).BOD5Direct)));
            ui->nodeinfo->setItem(17, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->BOD5Direct)));
            ui->nodeinfo->setItem(18, 0, new QTableWidgetItem("五日生化需氧量间接"));
            ui->nodeinfo->setItem(18, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).BOD5Indirect)));
            ui->nodeinfo->setItem(18, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->BOD5Indirect)));
            ui->nodeinfo->setItem(18, 3, new QTableWidgetItem("生物需氧量"));
            ui->nodeinfo->setItem(18, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).BOD)));
            ui->nodeinfo->setItem(18, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->BOD)));
            ui->nodeinfo->setItem(19, 0, new QTableWidgetItem("总磷直接"));
            ui->nodeinfo->setItem(19, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).PDirect)));
            ui->nodeinfo->setItem(19, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->PDirect)));
            ui->nodeinfo->setItem(19, 3, new QTableWidgetItem("细菌总数"));
            ui->nodeinfo->setItem(19, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).BC)));
            ui->nodeinfo->setItem(19, 5, new QTableWidgetItem(QString::number(500)));
            ui->nodeinfo->setItem(20, 0, new QTableWidgetItem("大肠杆菌数"));
            ui->nodeinfo->setItem(20, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).SLC)));
            ui->nodeinfo->setItem(20, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->Slc)));
            ui->nodeinfo->setItem(20, 3, new QTableWidgetItem("色度直接"));
            ui->nodeinfo->setItem(20, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).COLORDirect)));
            ui->nodeinfo->setItem(20, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->COLORDirect)));
            ui->nodeinfo->setItem(21, 0, new QTableWidgetItem("色度间接"));
            ui->nodeinfo->setItem(21, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).COLORIndirect)));
            ui->nodeinfo->setItem(21, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->COLORIndirect)));
            ui->nodeinfo->setItem(21, 3, new QTableWidgetItem("动植物油直接"));
            ui->nodeinfo->setItem(21, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).AFDirect)));
            ui->nodeinfo->setItem(21, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->AFDirect)));
            ui->nodeinfo->setItem(22, 0, new QTableWidgetItem("动植物油间接"));
            ui->nodeinfo->setItem(22, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).AFINDirect)));
            ui->nodeinfo->setItem(22, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->AFINDirect)));
            ui->nodeinfo->setItem(22, 3, new QTableWidgetItem("氯离子直接"));
            ui->nodeinfo->setItem(22, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).CLDirect)));
            ui->nodeinfo->setItem(22, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->CLDirect)));
            ui->nodeinfo->setItem(23, 0, new QTableWidgetItem("氯离子间接"));
            ui->nodeinfo->setItem(23, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).CLIndirect)));
            ui->nodeinfo->setItem(23, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->CLIndirect)));
            ui->nodeinfo->setItem(23, 3, new QTableWidgetItem("总磷间接"));
            ui->nodeinfo->setItem(23, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).PINDirect)));
            ui->nodeinfo->setItem(23, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->PINDirect)));
            ui->nodeinfo->setItem(24, 0, new QTableWidgetItem("总铬"));
            ui->nodeinfo->setItem(24, 1, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Cr)));
            ui->nodeinfo->setItem(24, 2, new QTableWidgetItem(QString::number(CSystemMain::standard->Cr)));
            ui->nodeinfo->setItem(24, 3, new QTableWidgetItem("单位"));
            ui->nodeinfo->setItem(24, 4, new QTableWidgetItem(QString::number(CSystemMain::nodeDataList->at(index.row()).Ton)));
            ui->nodeinfo->setItem(24, 5, new QTableWidgetItem(QString::number(CSystemMain::standard->Ton)));
            // 绘制折线图
            QtCharts::QSplineSeries *series0ph = new QtCharts::QSplineSeries();
            series0ph->setPen(QPen(QColor(0, 152, 255)));
            for (int i = 0; i <= 10; i++)
            {
                series0ph->append(i, CSystemMain::nodeinfluxData_temp->at(i).pH);
            }
            series0ph->setName("PH");
            series0ph->setUseOpenGL(true);

            QtCharts::QSplineSeries *series0temp = new QtCharts::QSplineSeries();
            series0temp->setPen(QPen(QColor(33, 95, 215)));
            for (int i = 0; i <= 10; i++)
            {
                series0temp->append(i, CSystemMain::nodeinfluxData_temp->at(i).COD);
            }
            series0temp->setName("温度");
            series0temp->setUseOpenGL(true);

            QtCharts::QSplineSeries *series0gas = new QtCharts::QSplineSeries();
            series0gas->setPen(QPen(QColor(11, 191, 182)));
            for (int i = 0; i <= 10; i++)
            {
                series0gas->append(i, CSystemMain::nodeinfluxData_temp->at(i).gasConcentration);
            }
            series0gas->setName("气体浓度");
            series0gas->setUseOpenGL(true);

            QtCharts::QSplineSeries *series0cod = new QtCharts::QSplineSeries();
            series0cod->setPen(QPen(QColor(117, 222, 141)));
            for (int i = 0; i <= 10; i++)
            {
                series0cod->append(i, CSystemMain::nodeinfluxData_temp->at(i).COD);
            }
            series0cod->setName("电导率");
            series0cod->setUseOpenGL(true);

            QtCharts::QSplineSeries *series0den = new QtCharts::QSplineSeries();
            series0den->setPen(QPen(QColor(15, 132, 52)));
            for (int i = 0; i <= 10; i++)
            {
                series0den->append(i, CSystemMain::nodeinfluxData_temp->at(i).density);
            }
            series0den->setName("浊度");
            series0den->setUseOpenGL(true);

            QtCharts::QSplineSeries *series0oxy = new QtCharts::QSplineSeries();
            series0oxy->setPen(QPen(QColor(237, 180, 0)));
            for (int i = 0; i <= 10; i++)
            {
                series0oxy->append(i, CSystemMain::nodeinfluxData_temp->at(i).oxygenConcentration);
            }
            series0oxy->setName("含氧量");
            series0oxy->setUseOpenGL(true);

            QtCharts::QChart *chart = new QtCharts::QChart();
            chart->addSeries(series0ph);
            chart->addSeries(series0temp);
            chart->addSeries(series0gas);
            chart->addSeries(series0cod);
            chart->addSeries(series0den);
            chart->addSeries(series0oxy);
            chart->legend()->setAlignment(Qt::AlignRight);
            chart->createDefaultAxes();
            chart->axisX()->setVisible(false);
            chart->legend()->setFont(QFont("Times New Roman", 10));
            chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
            ui->graphicsView->setChart(chart);
            ui->graphicsView->setRenderHint(QPainter::Antialiasing);

            // 居中显示
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 25; j++)
                {
                    ui->nodeinfo->item(j, i)->setTextAlignment(Qt::AlignCenter);
                }
            }

            // 重金属水平条形图
            QtCharts::QBarSet *set0 = new QtCharts::QBarSet("总铜");
            *set0 << CSystemMain::nodeDataList->at(index.row()).Cu;
            QtCharts::QBarSet *set1 = new QtCharts::QBarSet("总锌");
            *set1 << CSystemMain::nodeDataList->at(index.row()).Zn;
            QtCharts::QBarSet *set2 = new QtCharts::QBarSet("总锡");
            *set2 << CSystemMain::nodeDataList->at(index.row()).Sn;
            QtCharts::QBarSet *set3 = new QtCharts::QBarSet("总锑");
            *set3 << CSystemMain::nodeDataList->at(index.row()).Sb;
            QtCharts::QBarSet *set4 = new QtCharts::QBarSet("总汞");
            *set4 << CSystemMain::nodeDataList->at(index.row()).Hg;
            QtCharts::QBarSet *set5 = new QtCharts::QBarSet("总镉");
            *set5 << CSystemMain::nodeDataList->at(index.row()).Cd;
            QtCharts::QBarSet *set6 = new QtCharts::QBarSet("总铅");
            *set6 << CSystemMain::nodeDataList->at(index.row()).Pb;
            QtCharts::QBarSet *set7 = new QtCharts::QBarSet("总砷");
            *set7 << CSystemMain::nodeDataList->at(index.row()).As;
            QtCharts::QBarSet *set8 = new QtCharts::QBarSet("六价铬");
            *set8 << CSystemMain::nodeDataList->at(index.row()).Cr6;
            QtCharts::QBarSet *set9 = new QtCharts::QBarSet("总铬");
            *set9 << CSystemMain::nodeDataList->at(index.row()).Cr;
            QtCharts::QHorizontalBarSeries *series11 = new QtCharts::QHorizontalBarSeries();
            series11->append(set0);
            series11->append(set1);
            series11->append(set2);
            series11->append(set3);
            series11->append(set4);
            series11->append(set5);
            series11->append(set6);
            series11->append(set7);
            series11->append(set8);
            series11->append(set9);
            series11->setBarWidth(0.9);
            series11->useOpenGL();
            series11->setLabelsPosition(QtCharts::QAbstractBarSeries::LabelsOutsideEnd);
            QtCharts::QChart *chart11 = new QtCharts::QChart();
            chart11->addSeries(series11);
            QtCharts::QValueAxis *axisX11 = new QtCharts::QValueAxis();
            axisX11->setRange(0, 4);
            series11->attachAxis(axisX11);
            chart11->setAxisX(axisX11, series11);
            chart11->legend()->setAlignment(Qt::AlignRight);
            chart11->legend()->setFont(QFont("Times New Roman", 10));
            chart11->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
            ui->graphicsViewIron->setChart(chart11);
            ui->graphicsViewIron->setRenderHint(QPainter::Antialiasing);

            QtCharts::QBarSet *set20 = new QtCharts::QBarSet("色度");
            *set20 << CSystemMain::nodeDataList->at(index.row()).COLORDirect;
            QtCharts::QBarSet *set21 = new QtCharts::QBarSet("悬浮物");
            *set21 << CSystemMain::nodeDataList->at(index.row()).FSCDirectO;
            QtCharts::QBarSet *set22 = new QtCharts::QBarSet("五日生化");
            *set22 << CSystemMain::nodeDataList->at(index.row()).BOD5Direct;
            QtCharts::QBarSet *set23 = new QtCharts::QBarSet("动植物油");
            *set23 << CSystemMain::nodeDataList->at(index.row()).AFINDirect;
            QtCharts::QBarSet *set24 = new QtCharts::QBarSet("硫化物");
            *set24 << CSystemMain::nodeDataList->at(index.row()).SADirect;
            QtCharts::QBarSet *set25 = new QtCharts::QBarSet("氨氮");
            *set25 << CSystemMain::nodeDataList->at(index.row()).ANDirect;
            QtCharts::QBarSet *set26 = new QtCharts::QBarSet("总氮");
            *set26 << CSystemMain::nodeDataList->at(index.row()).TNDirect;
            QtCharts::QBarSet *set27 = new QtCharts::QBarSet("总磷");
            *set27 << CSystemMain::nodeDataList->at(index.row()).TPDirect;
            QtCharts::QBarSeries *series21 = new QtCharts::QBarSeries();
            series21->append(set20);
            series21->append(set21);
            series21->append(set22);
            series21->append(set23);
            series21->append(set24);
            series21->append(set25);
            series21->append(set26);
            series21->append(set27);
            series21->setBarWidth(0.9);
            series21->setLabelsPosition(QtCharts::QAbstractBarSeries::LabelsOutsideEnd);
            QtCharts::QChart *chart21 = new QtCharts::QChart();
            chart21->addSeries(series21);
            QtCharts::QValueAxis *axisY21 = new QtCharts::QValueAxis();
            axisY21->setRange(0, 30);
            series21->attachAxis(axisY21);
            chart21->setAxisY(axisY21, series21);
            chart21->legend()->setAlignment(Qt::AlignRight);
            chart21->legend()->setFont(QFont("Times New Roman", 10));
            chart21->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
            chart21->setTitle("直观污染核心指标");
            ui->graphicsViewOther1->setRenderHint(QPainter::Antialiasing);
            ui->graphicsViewOther1->setChart(chart21);

            QtCharts::QBarSet *set30 = new QtCharts::QBarSet("COD");
            *set30 << CSystemMain::nodeDataList->at(index.row()).CODDirect;
            QtCharts::QBarSet *set31 = new QtCharts::QBarSet("COD*");
            *set31 << CSystemMain::nodeDataList->at(index.row()).CODIndirect;
            QtCharts::QBarSet *set32 = new QtCharts::QBarSet("BOD5");
            *set32 << CSystemMain::nodeDataList->at(index.row()).BOD5Direct;
            QtCharts::QBarSet *set33 = new QtCharts::QBarSet("BOD5*");
            *set33 << CSystemMain::nodeDataList->at(index.row()).BOD5Indirect;
            QtCharts::QBarSet *set34 = new QtCharts::QBarSet("BOD");
            *set34 << CSystemMain::nodeDataList->at(index.row()).BOD;
            QtCharts::QBarSeries *series31 = new QtCharts::QBarSeries();
            series31->append(set30);
            series31->append(set31);
            series31->append(set32);
            series31->append(set33);
            series31->append(set34);
            series31->setBarWidth(0.6);
            series31->setLabelsPosition(QtCharts::QAbstractBarSeries::LabelsOutsideEnd);
            QtCharts::QChart *chart31 = new QtCharts::QChart();
            chart31->addSeries(series31);
            QtCharts::QValueAxis *axisX31 = new QtCharts::QValueAxis();
            axisX31->setRange(0, 200);
            series31->attachAxis(axisX31);
            chart31->setAxisY(axisX31, series31);
            chart31->legend()->setAlignment(Qt::AlignRight);
            chart31->legend()->setFont(QFont("Times New Roman", 10));
            chart31->setTitle("生化核心指标");
            chart31->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
            ui->graphicsViewOther2->setChart(chart31);
            ui->graphicsViewOther2->setRenderHint(QPainter::Antialiasing);

            // 散点图
            QtCharts::QChart *chart40 = new QtCharts::QChart();
            QtCharts::QScatterSeries *series41 = new QtCharts::QScatterSeries(chart40);
            series41->setMarkerShape(QtCharts::QScatterSeries::MarkerShapeCircle);
            series41->setMarkerSize(12);
            series41->setColor(QColor(Qt::red));
            series41->setName("自然");
            series41->setVisible();
            series41->append(CSystemMain::nodeDataList->at(index.row()).FSCDirectO, CSystemMain::nodeDataList->at(index.row()).FSCIndirectO);
            series41->append(CSystemMain::nodeDataList->at(index.row()).PhDirectHigh, CSystemMain::nodeDataList->at(index.row()).PhDirectHigh);
            series41->append(CSystemMain::nodeDataList->at(index.row()).SLC / 5, CSystemMain::nodeDataList->at(index.row()).SLC / 5);
            series41->append(CSystemMain::nodeDataList->at(index.row()).Sc, CSystemMain::nodeDataList->at(index.row()).Conductivity);
            QtCharts::QScatterSeries *series42 = new QtCharts::QScatterSeries(chart40);
            series42->setMarkerShape(QtCharts::QScatterSeries::MarkerShapeCircle);
            series42->setMarkerSize(12);
            series42->setColor(QColor(Qt::green));
            series42->setName("生化");
            series42->append(CSystemMain::nodeDataList->at(index.row()).BOD5Direct, CSystemMain::nodeDataList->at(index.row()).BOD5Indirect);
            series42->append(CSystemMain::nodeDataList->at(index.row()).CODIndirect, CSystemMain::nodeDataList->at(index.row()).CODDirect);
            QtCharts::QScatterSeries *series43 = new QtCharts::QScatterSeries(chart40);
            series43->setMarkerShape(QtCharts::QScatterSeries::MarkerShapeCircle);
            series43->setMarkerSize(12);
            series43->setColor(QColor(Qt::blue));
            series43->setName("重金属");
            series43->append(CSystemMain::nodeDataList->at(index.row()).Cu * 60, CSystemMain::nodeDataList->at(index.row()).Zn * 60);
            series43->append(CSystemMain::nodeDataList->at(index.row()).Hg * 60, CSystemMain::nodeDataList->at(index.row()).Cd * 60);
            series43->append(CSystemMain::nodeDataList->at(index.row()).Cr * 60, CSystemMain::nodeDataList->at(index.row()).Pb * 60);
            QtCharts::QScatterSeries *series44 = new QtCharts::QScatterSeries(chart40);
            series44->setMarkerShape(QtCharts::QScatterSeries::MarkerShapeCircle);
            series44->setMarkerSize(12);
            series44->setColor(QColor(Qt::yellow));
            series44->setName("有机物");
            series44->append(CSystemMain::nodeDataList->at(index.row()).TNDirect * 5, CSystemMain::nodeDataList->at(index.row()).TNDirect * 5);
            series44->append(CSystemMain::nodeDataList->at(index.row()).ANDirect * 3, CSystemMain::nodeDataList->at(index.row()).ANINDirect * 3);
            series44->append(CSystemMain::nodeDataList->at(index.row()).AFDirect * 5, CSystemMain::nodeDataList->at(index.row()).AFINDirect * 5);
            chart40->addSeries(series41);
            chart40->addSeries(series42);
            chart40->addSeries(series43);
            chart40->addSeries(series44);
            chart40->setTitle("指标散点分析");
            chart40->createDefaultAxes();
            chart40->legend()->setAlignment(Qt::AlignRight);
            chart40->legend()->setFont(QFont("Times New Roman", 10));
            chart40->setAnimationOptions(QtCharts::QChart::AllAnimations);
            ui->graphicsViewOther3->setChart(chart40);

            // 饼图
            QtCharts::QChart *chart50 = new QtCharts::QChart();
            QtCharts::QPieSlice *slice51 = new QtCharts::QPieSlice(chart50);
            slice51->setLabel("生物需氧量" + QString::number(CSystemMain::nodeDataList->at(i).BOD5Direct));
            slice51->setValue(CSystemMain::nodeDataList->at(index.row()).BOD5Direct);
            slice51->setColor(QColor(Qt::red));
            QtCharts::QPieSlice *slice52 = new QtCharts::QPieSlice(chart50);
            slice52->setLabel("化学需氧量" + QString::number(CSystemMain::nodeDataList->at(i).BOD5Indirect));
            slice52->setValue(CSystemMain::nodeDataList->at(index.row()).CODDirect);
            slice52->setColor(QColor(Qt::green));
            QtCharts::QPieSlice *slice53 = new QtCharts::QPieSlice(chart50);
            slice53->setLabel("生物需氧量*" + QString::number(CSystemMain::nodeDataList->at(i).CODDirect));
            slice53->setValue(CSystemMain::nodeDataList->at(index.row()).BOD5Indirect);
            slice53->setColor(QColor(Qt::blue));
            QtCharts::QPieSlice *slice54 = new QtCharts::QPieSlice(chart50);
            slice54->setLabel("化学需氧量*" + QString::number(CSystemMain::nodeDataList->at(i).CODIndirect));
            slice54->setValue(CSystemMain::nodeDataList->at(index.row()).CODIndirect);
            slice54->setColor(QColor(Qt::yellow));
            QtCharts::QPieSeries *series50 = new QtCharts::QPieSeries(chart50);
            series50->append(slice51);
            series50->append(slice52);
            series50->append(slice53);
            series50->append(slice54);
            series50->setLabelsVisible();
            series50->setLabelsPosition(QtCharts::QPieSlice::LabelOutside);
            series50->setPieSize(0.5);
            series50->setPieStartAngle(12);
            series50->setPieEndAngle(372);
            chart50->legend()->hide();
            chart50->addSeries(series50);
            chart50->setTitle("需氧量总占比");
            chart50->setAnimationOptions(QtCharts::QChart::AllAnimations);
            chart50->setMargins(QMargins(0, 0, 0, 0));
            ui->graphView_Diag1->setChart(chart50);
            ui->graphView_Diag1->setRenderHint(QPainter::Antialiasing);

            // 饼图
            QtCharts::QChart *chart60 = new QtCharts::QChart();
            QtCharts::QPieSlice *slice61 = new QtCharts::QPieSlice(chart60);
            slice61->setValue(CSystemMain::nodeInfoList->at(i).selfDate.toTime_t() / 3);
            slice61->setColor(QColor(Qt::red));
            QtCharts::QPieSlice *slice62 = new QtCharts::QPieSlice(chart60);
            slice62->setValue(QDateTime::currentDateTimeUtc().toTime_t() - CSystemMain::nodeInfoList->at(i).selfDate.toTime_t() * 2);
            slice62->setColor(QColor(Qt::green));
            QtCharts::QPieSeries *series60 = new QtCharts::QPieSeries(chart60);
            series60->append(slice61);
            series60->append(slice62);
            series60->setLabelsVisible(false);
            series60->setPieSize(0.8);
            series60->setHoleSize(0.5);
            chart60->legend()->hide();
            chart60->addSeries(series60);
            chart60->setTitle("节点健康度");
            chart60->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
            ui->graphicsViewDiag2->setChart(chart60);
            ui->graphicsViewDiag2->setRenderHint(QPainter::Antialiasing);

            // 饼图
            QtCharts::QChart *chart70 = new QtCharts::QChart();
            QtCharts::QPieSlice *slice71 = new QtCharts::QPieSlice(chart70);
            slice71->setLabel("上次上传时间" + QString::number(CSystemMain::nodeDataList->at(i).BOD5Direct));
            slice71->setValue(CSystemMain::nodeInfoList->at(index.row()).lastUpload.toTime_t() / 3);
            slice71->setColor(QColor("#7da6ff"));
            QtCharts::QPieSlice *slice72 = new QtCharts::QPieSlice(chart70);
            slice72->setLabel("当前时间" + QString::number(QDateTime::currentDateTimeUtc().toTime_t() - CSystemMain::nodeInfoList->at(i).lastUpload.toTime_t() * 3));
            slice72->setColor(QColor("#ffd680"));
            QtCharts::QPieSeries *series70 = new QtCharts::QPieSeries(chart70);
            series70->append(slice71);
            series70->append(slice72);
            series70->setLabelsVisible(false);
            series70->setLabelsPosition(QtCharts::QPieSlice::LabelOutside);
            series70->setPieSize(0.8);
            series70->setHoleSize(0.5);
            chart70->legend()->hide();
            chart70->addSeries(series70);
            chart70->setTitle("传感数据可信度");
            chart70->setAnimationOptions(QtCharts::QChart::AllAnimations);
            ui->graphicsViewDiag3->setChart(chart70);
            ui->graphicsViewDiag3->setRenderHint(QPainter::Antialiasing);

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
            float x = CSystemMain::nodeInfoList->at(i).lo;
            float y = CSystemMain::nodeInfoList->at(i).li;
            QTimer::singleShot(500, this, [=]()
                               {
                                emit setCenter(x, y);
                                // 表格模板,防止挤压
                                QString info = "位置信息:" + CSystemMain::nodeInfoList->at(i).locate;
                                emit addPoint(info, x, y,""); });
            break;
        }
    }
}

void nodeinformation::on_modSwitch_btn_clicked()
{
    // 判断当前文字
    if (ui->modSwitch_btn->text() == "可视化浏览")
    {
        ui->modSwitch_btn->setText("数据浏览");
        ui->stackSwitcher->setCurrentIndex(1);
        emit setCenter(CSystemMain::nodeInfoList->at(0).lo, CSystemMain::nodeInfoList->at(0).li);
    }
    else
    {
        ui->modSwitch_btn->setText("可视化浏览");
        ui->stackSwitcher->setCurrentIndex(0);
    }
}

void nodeinformation::on_pathSelect_btn_clicked()
{
    // 弹出文件夹选择框
    QString path = QFileDialog::getExistingDirectory(this, "选择文件夹", "./");
    if (path.isEmpty())
    {
        QMessageBox::information(this, "提示", "未选择文件");
        return;
    }
    ui->pathInput->setText(path + "/output" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".txt");
}

void nodeinformation::on_output_btn_clicked()
{
    // 判断文件路径是否为空
    if (ui->pathInput->text().isEmpty())
    {
        QMessageBox::information(this, "提示", "未选择文件路径");
        return;
    }
    else if (ui->dataInfo->isChecked() == false && ui->dataInfo->isChecked() == false && ui->locateInfo->isChecked() == false && ui->selfInfo->isChecked() == false)
    {
        QMessageBox::information(this, "提示", "未选择导出范围");
        return;
    }
    else
    {
        // 创建文件
        QFile file(ui->pathInput->text());
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            // 判断是否导出数据
            if (ui->dataInfo->isChecked())
            {
                out << QString("节点配置信息:").toUtf8() << endl;
                for (int i = 0; i < ui->configwidget->rowCount(); i++)
                {
                    for (int j = 0; j < ui->configwidget->columnCount(); j++)
                    {
                        out << ui->configwidget->item(i, j)->text() << " ";
                    }
                    out << endl;
                }
            }
            // 判断是否导出位置信息
            if (ui->locateInfo->isChecked())
            {
                out << QString("节点位置信息:").toUtf8() << endl;
                for (int i = 0; i < ui->locateinfo->count(); i++)
                {
                    out << ui->locateinfo->item(i)->text() << endl;
                }
            }
            // 判断是否导出自检信息
            if (ui->selfInfo->isChecked())
            {
                out << QString("节点自检信息:").toUtf8() << endl;
                for (int i = 0; i < ui->selflist->count(); i++)
                {
                    out << ui->selflist->item(i)->text() << endl;
                }
            }
            file.close();
            QMessageBox::information(this, "提示", "导出成功");
        }
        else
        {
            QMessageBox::information(this, "提示", "导出失败");
        }
    }
}

void nodeinformation::on_chear_btn_clicked()
{
    ui->pathInput->clear();
}
