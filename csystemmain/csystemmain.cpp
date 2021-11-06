#include "csystemmain.h"
#include "ui_csystemmain.h"
#include <QDebug>

CSystemMain::CSystemMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSystemMain)
{
    ui->setupUi(this);
    MapView *mv = new MapView(ui->widget);
    mv->show();
}

CSystemMain::~CSystemMain()
{
    delete ui;
}

void CSystemMain::on_MenuList_itemSelectionChanged()
{
    //原有的内存释放
    for (int i = 0; i < ui->widget->children().length(); i++) {
        delete  ui->widget->children().at(i);
    }
    //页面重加载
    QString str = ui->MenuList->selectedItems().takeFirst()->text();
        if(str == "全局信息概览"){
            MapView *mv = new MapView(ui->widget);
            mv->show();
        }else if(str == "节点信息详情"){
            MapView *mv = new MapView(ui->widget);
            mv->show();
        }else if(str == "数据可视化分析"){
            MapView *mv = new MapView(ui->widget);
            mv->show();
        }else if(str == "智能监控系统"){
            MapView *mv = new MapView(ui->widget);
            mv->show();
        }else if(str == "数据管理系统"){
            MapView *mv = new MapView(ui->widget);
            mv->show();
        }else if(str == "系统性能调试"){
            MapView *mv = new MapView(ui->widget);
            mv->show();
        }else if(str == "地图显示调整"){
            MapView *mv = new MapView(ui->widget);
            mv->show();
        }
}

