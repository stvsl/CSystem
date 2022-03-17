#include "csystemmain.h"
#include "ui_csystemmain.h"
#include <QDebug>

//菜单项指针
QStandardItem *MAP_VIEW = new QStandardItem("全局信息");           // status 1
QStandardItem *Node_Information = new QStandardItem("节点详情");   // status 2
QStandardItem *DATA_VIEW = new QStandardItem("数据浏览");          // status 3
QStandardItem *MAP_SETTING = new QStandardItem("地图设置");        // status 4
QStandardItem *SYSTEM_SETTING = new QStandardItem("系统设置");     // status 5
QStandardItem *NODE_INSTALL = new QStandardItem("节点配置");       // status 6
QStandardItem *ACCOUNT_MANAGEMENT = new QStandardItem("账户管理"); // status 7

CSystemMain::CSystemMain(QWidget *parent) : QMainWindow(parent),
                                            ui(new Ui::CSystemMain)
{
    ui->setupUi(this);
    // 渐入动画
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setEasingCurve(QEasingCurve::InQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    this->initialization();
    ui->side_menu->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

CSystemMain::~CSystemMain()
{
    delete ui;
}

void CSystemMain::initialization()
{
    //判断用户类型
    if (CONFIG_CORE::USER_TYPE == 0)
    {
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
        break;
    case 7:
        CSystemMain::WINDOW_ACCOUNT_MANAGEMENT->close();
        break;
    }

    //打开新的界面并显示，同时设置局部状态为对应状态
    if (index.data().toString() == "全局信息")
    {
        CSystemMain::WINDOW_MAP_VIEW = new MapView(ui->widget);
        CSystemMain::WINDOW_MAP_VIEW->show();
        CSystemMain::widgetstatus = 1;
        this->ui->bottombar->setCurrentWidget(ui->page1);
    }
    else if (index.data().toString() == "节点详情")
    {
        CSystemMain::WINDOW_NODE_INFORMATION = new nodeinformation(ui->widget);
        CSystemMain::WINDOW_NODE_INFORMATION->show();
        CSystemMain::widgetstatus = 2;
        this->ui->bottombar->setCurrentWidget(ui->page1);
    }
    else if (index.data().toString() == "数据浏览")
    {
        CSystemMain::WINDOW_DATA_VIEW = new DataView(ui->widget);
        CSystemMain::WINDOW_DATA_VIEW->show();
        CSystemMain::widgetstatus = 3;
        this->ui->bottombar->setCurrentWidget(ui->page1);
    }
    else if (index.data().toString() == "地图设置")
    {
        CSystemMain::WINDOW_MAP_SETTING = new MapSetting(ui->widget);
        CSystemMain::WINDOW_MAP_SETTING->show();
        CSystemMain::widgetstatus = 4;
        this->ui->bottombar->setCurrentWidget(ui->page1);
    }
    else if (index.data().toString() == "系统设置")
    {
        CSystemMain::WINDOW_SYSTEM_SETTING = new SystemSetting(ui->widget);
        CSystemMain::WINDOW_SYSTEM_SETTING->show();
        CSystemMain::widgetstatus = 5;
        this->ui->bottombar->setCurrentWidget(ui->page1);
    }
    else if (index.data().toString() == "节点配置")
    {
        CSystemMain::WINDOW_NODE_INSTALL = new NodeInstall(ui->widget);
        CSystemMain::WINDOW_NODE_INSTALL->show();
        CSystemMain::widgetstatus = 6;
        this->ui->bottombar->setCurrentWidget(ui->page2);
    }
    else if (index.data().toString() == "账户管理")
    {
        CSystemMain::WINDOW_ACCOUNT_MANAGEMENT = new AccountManagement(ui->widget);
        CSystemMain::WINDOW_ACCOUNT_MANAGEMENT->show();
        CSystemMain::widgetstatus = 7;
        this->ui->bottombar->setCurrentWidget(ui->page3);
    }
}
