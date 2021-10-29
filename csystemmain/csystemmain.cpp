#include "csystemmain.h"
#include "ui_csystemmain.h"
#include "mapview.h"
#include <QDebug>

CSystemMain::CSystemMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSystemMain)
{
    ui->setupUi(this);
//    MapView *mv = new MapView(ui->widget);
//    mv->show();
}

CSystemMain::~CSystemMain()
{
    delete ui;
}




void CSystemMain::on_MenuList_itemSelectionChanged()
{
    QString str = ui->MenuList->selectedItems().takeFirst()->text();
        if(str == "全局信息概览"){
            ui->widget->close();
            ui->widget->show();
            MapView *mv = new MapView(ui->widget);
            mv->show();
        }else if(str == "节点信息详情"){
            ui->widget->close();
        }else if(str == "数据可视化分析"){
            ui->widget->close();
        }else if(str == "智能监控系统"){
            ui->widget->close();
        }else if(str == "数据管理系统"){
            ui->widget->close();
        }else if(str == "系统性能调试"){
            ui->widget->close();
        }
}

