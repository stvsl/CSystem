#include "csystemmain.h"
#include "ui_csystemmain.h"
#include <QDebug>

//菜单项指针
QStandardItem *MAP_VIEW = new QStandardItem("全局信息");            //status 1
QStandardItem *Node_Information = new QStandardItem("节点详情");    //status 2
QStandardItem *DATA_VIEW = new QStandardItem("数据浏览");           //status 3
QStandardItem *MAP_SETTING = new QStandardItem("地图设置");         //status 4

CSystemMain::CSystemMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSystemMain)
{
    ui->setupUi(this);

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
    if(CONFIG_CORE::USER_TYPE == 0){
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
        ui->side_menu->setModel(CSystemMain::USER_DEFAULT);
    }

}

void CSystemMain::on_side_menu_clicked(const QModelIndex &index)
{
    //关闭之前显示的界面
    switch(CSystemMain::widgetstatus){
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
    }

    //打开新的界面并显示，同时设置局部状态为对应状态
    if(index.data().toString() == "全局信息"){
        CSystemMain::WINDOW_MAP_VIEW = new MapView(ui->widget);
        CSystemMain::WINDOW_MAP_VIEW->show();
        CSystemMain::widgetstatus = 1;
    }else if(index.data().toString() == "节点详情"){
        CSystemMain::WINDOW_NODE_INFORMATION = new nodeinformation(ui->widget);
        CSystemMain::WINDOW_NODE_INFORMATION->show();
        CSystemMain::widgetstatus = 2;
    }else if(index.data().toString() == "数据浏览"){
        CSystemMain::WINDOW_DATA_VIEW = new DataView(ui->widget);
        CSystemMain::WINDOW_DATA_VIEW->show();
        CSystemMain::widgetstatus = 3;
    }else if(index.data().toString() == "地图设置"){
        CSystemMain::WINDOW_MAP_SETTING = new MapSetting(ui->widget);
        CSystemMain::WINDOW_MAP_SETTING->show();
        CSystemMain::widgetstatus = 4;
    }
}
