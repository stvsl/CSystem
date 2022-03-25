#include "csystemmain.h"
#include "ui_csystemmain.h"
#include <QDebug>
#include <QStringListModel>
#include <QGraphicsDropShadowEffect>
#include <QTimer>

//菜单项指针
QStandardItem *MAP_VIEW = new QStandardItem("全局信息");           // status 1
QStandardItem *Node_Information = new QStandardItem("节点详情");   // status 2
QStandardItem *DATA_VIEW = new QStandardItem("数据浏览");          // status 3
QStandardItem *MAP_SETTING = new QStandardItem("地图设置");        // status 4
QStandardItem *SYSTEM_SETTING = new QStandardItem("系统设置");     // status 5
QStandardItem *NODE_INSTALL = new QStandardItem("节点配置");       // status 6
QStandardItem *ACCOUNT_MANAGEMENT = new QStandardItem("账户管理"); // status 7

QGraphicsBlurEffect *blurEffect;
QPropertyAnimation *animationload;
QPropertyAnimation *animationsidebar;
QPropertyAnimation *animationbootombar;
QPropertyAnimation *animationbottombarhide;
QGraphicsDropShadowEffect *effectsidebar;
QGraphicsDropShadowEffect *effectsgroupbox1;
QGraphicsDropShadowEffect *effectsgroupbox2;
QGraphicsDropShadowEffect *effectsgroupbox3;
QGraphicsDropShadowEffect *effectsgroupbox4;
QGraphicsDropShadowEffect *effectsgroupbox5;
QGraphicsDropShadowEffect *effectsbottombar;

QVector<NodeInfo> *CSystemMain::nodeInfoList;
QVector<NodeData> *CSystemMain::nodeDataList;

QStringList global_list;
QStringList warn_list;
QStringList disaster_list;

int bottombarindex = 0;

CSystemMain::CSystemMain(QWidget *parent) : QMainWindow(parent),
                                            ui(new Ui::CSystemMain)
{
    ui->setupUi(this);
    // 初始化菜单栏
    MAP_VIEW->setIcon(QIcon(":/icon/icon/全局信息.png"));
    Node_Information->setIcon(QIcon(":/icon/icon/节点详情.png"));
    DATA_VIEW->setIcon(QIcon(":/icon/icon/数据浏览.png"));
    MAP_SETTING->setIcon(QIcon(":/icon/icon/地图设置.png"));
    SYSTEM_SETTING->setIcon(QIcon(":/icon/icon/系统设置.png"));
    NODE_INSTALL->setIcon(QIcon(":/icon/icon/节点配置.png"));
    ACCOUNT_MANAGEMENT->setIcon(QIcon(":/icon/icon/账户管理.png"));

    // 毛玻璃效果
    blurEffect = new QGraphicsBlurEffect(ui->bottombar);
    blurEffect->setBlurRadius(1);
    ui->bottombar->setGraphicsEffect(blurEffect);

    // 渐入动画
    animationload = new QPropertyAnimation(this, "windowOpacity");
    animationload->setDuration(900);
    animationload->setStartValue(0);
    animationload->setEndValue(1);
    animationload->setEasingCurve(QEasingCurve::InQuad);
    animationload->start(QAbstractAnimation::DeleteWhenStopped);
    // 从左侧渐出动画
    animationsidebar = new QPropertyAnimation(ui->SideBar, "geometry");
    animationsidebar->setDuration(1500);
    animationsidebar->setStartValue(QRect(0, 0, 0, 1021));
    animationsidebar->setEndValue(QRect(0, 0, 231, 1021));
    animationsidebar->setEasingCurve(QEasingCurve::InQuart);
    animationsidebar->start(QAbstractAnimation::DeleteWhenStopped);
    // 底部渐入动画
    animationbootombar = new QPropertyAnimation(ui->widget_2, "geometry");
    animationbootombar->setDuration(1500);
    animationbootombar->setStartValue(QRect(230, 1024, 1691, 124));
    animationbootombar->setEndValue(QRect(230, 900, 1691, 124));
    animationbootombar->setEasingCurve(QEasingCurve::InQuart);
    animationbootombar->start();
    // 底部渐出动画
    animationbottombarhide = new QPropertyAnimation(ui->widget_2, "geometry");
    animationbottombarhide->setDuration(200);
    animationbottombarhide->setStartValue(QRect(230, 900, 1691, 124));
    animationbottombarhide->setEndValue(QRect(230, 1024, 1691, 124));
    animationbottombarhide->setEasingCurve(QEasingCurve::InQuart);
    // 阴影效果处理
    effectsidebar = new QGraphicsDropShadowEffect(ui->SideBar);
    effectsidebar->setOffset(0, 0);                    //设置阴影距离
    effectsidebar->setColor(QColor(17, 37, 158, 120)); //设置阴影颜色
    effectsidebar->setBlurRadius(20);                  //设置阴影圆角
    ui->SideBar->setStyleSheet("background-color:#FFFFFF;");
    ui->SideBar->setGraphicsEffect(effectsidebar);
    effectsbottombar = new QGraphicsDropShadowEffect(ui->widget_2);
    effectsbottombar->setOffset(0, 0);               //设置阴影距离
    effectsbottombar->setColor(QColor(0, 0, 0, 20)); //设置阴影颜色
    effectsbottombar->setBlurRadius(20);             //设置阴影圆角
    ui->widget_2->setGraphicsEffect(effectsbottombar);
    effectsgroupbox1 = new QGraphicsDropShadowEffect(ui->groupBox);
    effectsgroupbox1->setOffset(0, 0);                   //设置阴影距离
    effectsgroupbox1->setColor(QColor(2, 143, 208, 60)); //设置阴影颜色
    effectsgroupbox1->setBlurRadius(30);                 //设置阴影圆角
    ui->groupBox->setGraphicsEffect(effectsgroupbox1);
    effectsgroupbox2 = new QGraphicsDropShadowEffect(ui->groupBox_2);
    effectsgroupbox2->setOffset(0, 0);                     //设置阴影距离
    effectsgroupbox2->setColor(QColor(255, 100, 100, 60)); //设置阴影颜色
    effectsgroupbox2->setBlurRadius(30);                   //设置阴影圆角
    ui->groupBox_2->setGraphicsEffect(effectsgroupbox2);
    effectsgroupbox3 = new QGraphicsDropShadowEffect(ui->groupBox_3);
    effectsgroupbox3->setOffset(0, 0);                    //设置阴影距离
    effectsgroupbox3->setColor(QColor(255, 230, 28, 60)); //设置阴影颜色
    effectsgroupbox3->setBlurRadius(30);                  //设置阴影圆角
    ui->groupBox_3->setGraphicsEffect(effectsgroupbox3);
    effectsgroupbox4 = new QGraphicsDropShadowEffect(ui->groupBox_4);
    effectsgroupbox4->setOffset(0, 0);                    //设置阴影距离
    effectsgroupbox4->setColor(QColor(2, 143, 210, 120)); //设置阴影颜色
    effectsgroupbox4->setBlurRadius(30);                  //设置阴影圆角
    ui->groupBox_4->setGraphicsEffect(effectsgroupbox4);
    effectsgroupbox5 = new QGraphicsDropShadowEffect(ui->groupBox_5);
    effectsgroupbox5->setOffset(0, 0);                    //设置阴影距离
    effectsgroupbox5->setColor(QColor(2, 143, 210, 120)); //设置阴影颜色
    effectsgroupbox5->setBlurRadius(30);                  //设置阴影圆角
    ui->groupBox_5->setGraphicsEffect(effectsgroupbox5);

    // 初始化菜单管理模块
    this->initialization();
    ui->side_menu->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

CSystemMain::~CSystemMain()
{
    delete ui;
    delete blurEffect;
    delete MAP_VIEW;
    delete Node_Information;
    delete DATA_VIEW;
    delete MAP_SETTING;
    delete SYSTEM_SETTING;
    delete NODE_INSTALL;
    delete ACCOUNT_MANAGEMENT;
}

void CSystemMain::initialization()
{
    // 判断用户类型
    if (CONFIG_CORE::USER_TYPE == 0)
    {
        ui->Global_Info->setFrameShape(QFrame::NoFrame);
        ui->Global_Info->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->Global_Info->setSelectionMode(QAbstractItemView::NoSelection);
        //默认打开信息概览窗口
        CSystemMain::WINDOW_MAP_VIEW = new MapView(ui->widget);
        CSystemMain::WINDOW_MAP_VIEW->show();
        CSystemMain::widgetstatus = 1;
        //绑定菜单
        CSystemMain::USER_DEFAULT = new QStandardItemModel();
        CSystemMain::USER_DEFAULT->appendRow(MAP_VIEW);
        CSystemMain::USER_DEFAULT->appendRow(Node_Information);
        CSystemMain::USER_DEFAULT->appendRow(DATA_VIEW);
        CSystemMain::USER_DEFAULT->appendRow(MAP_SETTING);
        CSystemMain::USER_DEFAULT->appendRow(SYSTEM_SETTING);
        CSystemMain::USER_DEFAULT->appendRow(NODE_INSTALL);
        CSystemMain::USER_DEFAULT->appendRow(ACCOUNT_MANAGEMENT);
        ui->side_menu->setModel(CSystemMain::USER_DEFAULT);
    }
}

void CSystemMain::on_side_menu_clicked(const QModelIndex &index)
{
    animationbootombar->setDuration(200);

    //关闭之前显示的界面
    switch (CSystemMain::widgetstatus)
    {
    case 1:
        CSystemMain::WINDOW_MAP_VIEW->close();
        break;
    case 2:
        CSystemMain::WINDOW_NODE_INFORMATION->close();
        break;
    case 3:
        CSystemMain::WINDOW_DATA_VIEW->close();
        break;
    case 4:
        CSystemMain::WINDOW_MAP_SETTING->close();
        break;
    case 5:
        CSystemMain::WINDOW_SYSTEM_SETTING->close();
        break;
    case 6:
        CSystemMain::WINDOW_NODE_INSTALL->close();
        animationbottombarhide->start();
        break;
    case 7:
        CSystemMain::WINDOW_ACCOUNT_MANAGEMENT->close();
        animationbottombarhide->start();
        break;
    }

    //打开新的界面并显示，同时设置局部状态为对应状态
    if (index.data().toString() == "全局信息")
    {
        CSystemMain::WINDOW_MAP_VIEW = new MapView(ui->widget);
        CSystemMain::WINDOW_MAP_VIEW->show();
        this->ui->bottombar->setCurrentWidget(ui->page1);
        if (CSystemMain::widgetstatus > 5)
        {
            animationbootombar->start();
        }
        CSystemMain::widgetstatus = 1;
        QTimer::singleShot(300, this, SLOT(showEvent()));
    }
    else if (index.data().toString() == "节点详情")
    {
        CSystemMain::WINDOW_NODE_INFORMATION = new nodeinformation(ui->widget);
        CSystemMain::WINDOW_NODE_INFORMATION->show();
        if (CSystemMain::widgetstatus > 5)
        {
            animationbootombar->start();
        }
        CSystemMain::widgetstatus = 2;
        this->ui->bottombar->setCurrentWidget(ui->page1);
    }
    else if (index.data().toString() == "数据浏览")
    {
        CSystemMain::WINDOW_DATA_VIEW = new DataView(ui->widget);
        CSystemMain::WINDOW_DATA_VIEW->show();
        if (CSystemMain::widgetstatus > 5)
        {
            animationbootombar->start();
        }
        CSystemMain::widgetstatus = 3;
        this->ui->bottombar->setCurrentWidget(ui->page1);
    }
    else if (index.data().toString() == "地图设置")
    {
        CSystemMain::WINDOW_MAP_SETTING = new MapSetting(ui->widget);
        CSystemMain::WINDOW_MAP_SETTING->show();
        if (CSystemMain::widgetstatus > 5)
        {
            animationbootombar->start();
        }
        CSystemMain::widgetstatus = 4;
        this->ui->bottombar->setCurrentWidget(ui->page1);
    }
    else if (index.data().toString() == "系统设置")
    {
        CSystemMain::WINDOW_SYSTEM_SETTING = new SystemSetting(ui->widget);
        CSystemMain::WINDOW_SYSTEM_SETTING->show();
        if (CSystemMain::widgetstatus > 5)
        {
            animationbootombar->start();
        }
        CSystemMain::widgetstatus = 5;
        this->ui->bottombar->setCurrentWidget(ui->page1);
    }
    else if (index.data().toString() == "节点配置")
    {
        animationbottombarhide->start();
        CSystemMain::WINDOW_NODE_INSTALL = new NodeInstall(ui->widget);
        CSystemMain::WINDOW_NODE_INSTALL->show();
        CSystemMain::widgetstatus = 6;
        bottombarindex = 2;
        QTimer::singleShot(190, animationbootombar, SLOT(start()));
        QTimer::singleShot(180, this, SLOT(bottombarchanged()));
    }
    else if (index.data().toString() == "账户管理")
    {
        animationbottombarhide->start();
        CSystemMain::WINDOW_ACCOUNT_MANAGEMENT = new AccountManagement(ui->widget);
        CSystemMain::WINDOW_ACCOUNT_MANAGEMENT->show();
        CSystemMain::widgetstatus = 7;
        bottombarindex = 3;
        QTimer::singleShot(190, animationbootombar, SLOT(start()));
        QTimer::singleShot(180, this, SLOT(bottombarchanged()));
    }
}

void CSystemMain::bottombarchanged()
{
    switch (bottombarindex)
    {
    case 1:
        this->ui->bottombar->setCurrentWidget(ui->page1);
        break;
    case 2:
        this->ui->bottombar->setCurrentWidget(ui->page2);
        break;
    case 3:
        this->ui->bottombar->setCurrentWidget(ui->page3);
        break;
    }
}

void CSystemMain::showEvent()
{
    this->show();
    global_list.append("正在加载数据...请稍候...");
    QStringListModel *model = new QStringListModel(global_list);
    ui->Global_Info->setModel(model);
    NodeInterface ni;
    // 拉取数据
    // 网络错误弹出提示
    CSystemMain::nodeInfoList = ni.getNodeInfo();
    CSystemMain::WINDOW_MAP_VIEW->init();
    CSystemMain::nodeDataList = ni.getNodeData();
    global_list.append("数据加载完成");
    model->setStringList(global_list);
}
