#include "csystemmain.h"
#include "ui_csystemmain.h"
#include <QDebug>

CSystemMain::CSystemMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSystemMain)
{
    ui->setupUi(this);
    CSystemMain::mV = new MapView(ui->widget);
    CSystemMain::mV->show();
    CSystemMain::widgetstatus = 1;
}

CSystemMain::~CSystemMain()
{
    delete ui;
}

void CSystemMain::on_MenuList_itemSelectionChanged()
{

    if(CSystemMain::widgetstatus == 1){
        delete CSystemMain::mV;
    }
    //页面重加载
    QString str = ui->MenuList->selectedItems().takeFirst()->text();

    if(str == "全局信息概览"){
        CSystemMain::mV = new MapView(ui->widget);
        CSystemMain::mV ->show();
        CSystemMain::widgetstatus = 1;
    }else if(str == "节点信息详情"){
        CSystemMain::mV = new MapView(ui->widget);
        CSystemMain::mV ->show();
        CSystemMain::widgetstatus = 1;
    }else if(str == "数据可视化分析"){
        CSystemMain::mV = new MapView(ui->widget);
        CSystemMain::mV ->show();
        CSystemMain::widgetstatus = 1;
    }else if(str == "智能监控系统"){
        CSystemMain::mV = new MapView(ui->widget);
        CSystemMain::mV ->show();
        CSystemMain::widgetstatus = 1;
    }else if(str == "数据管理系统"){
        CSystemMain::mV = new MapView(ui->widget);
        CSystemMain::mV ->show();
        CSystemMain::widgetstatus = 1;
    }else if(str == "系统性能调试"){
        CSystemMain::mV = new MapView(ui->widget);
        CSystemMain::mV ->show();
        CSystemMain::widgetstatus = 1;
    }else if(str == "地图显示调整"){
        CSystemMain::mV = new MapView(ui->widget);
        CSystemMain::mV ->show();
        CSystemMain::widgetstatus = 1;
    }
}

