#include "mapsetting.h"
#include "ui_mapsetting.h"
#include <QGraphicsDropShadowEffect>
#include <configManager/configmanager.h>
#include <configManager/mapconfig.h>

QGraphicsDropShadowEffect *effect1;

MapSetting::MapSetting(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::MapSetting)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    // 阴影效果
    effect1 = new QGraphicsDropShadowEffect(ui->label);
    effect1->setOffset(0, 0);
    effect1->setColor(QColor(125, 164, 255, 80));
    effect1->setBlurRadius(10);
    ui->label->setGraphicsEffect(effect1);
    init();
    ui->webView->setUrl(QUrl("http://127.0.0.1:10241/pages/default/map"));
}

MapSetting::~MapSetting()
{
    delete effect1;
    delete ui;
}

void MapSetting::init()
{
    if (MAP_CONFIG::MAP_CONTROL_3D)
    {
        ui->support_3D->setChecked(true);
    }
    if (MAP_CONFIG::MAP_CONTROL_SCALE)
    {
        ui->support_ruler->setChecked(true);
    }
    if (MAP_CONFIG::MAP_POIICON_ON)
    {
        ui->show_Poi_Text->setChecked(true);
    }
    if (MAP_CONFIG::MAP_POITEXT_ON)
    {
        ui->show_Poi_Icon->setChecked(true);
    }
    if (MAP_CONFIG::MAP_KEYBOARD_CONTROL)
    {
        ui->control_KeyBoard->setChecked(true);
    }
    if (MAP_CONFIG::MAP_MOUSE_SCROLL_ZOOM)
    {
        ui->control_Rolling->setChecked(true);
    }
    if (MAP_CONFIG::MAP_DRAG_CONTROL)
    {
        ui->control_Drag->setChecked(true);
    }
    if (MAP_CONFIG::MAP_INERTIAL_DRAG)
    {
        ui->control_Drag_Flux->setChecked(true);
    }
    if (MAP_CONFIG::MAP_REMOVE_ANIMATION)
    {
        ui->remove_Anmine->setChecked(true);
    }
    if (MAP_CONFIG::MAP_USE_INTERNAL_HTML)
    {
        ui->use_Insid_Controller->setChecked(true);
    }
    if (MAP_CONFIG::MAP_AUTO_CLEAR_CACHE)
    {
        ui->noCache->setChecked(true);
    }
    if (MAP_CONFIG::MAP_EARTHMODEL)
    {
        ui->model_Earth->setChecked(true);
    }
    if (MAP_CONFIG::MAP_AUTO_POSITIONING)
    {
        ui->aoto_POS->setChecked(true);
    }
}

void MapSetting::on_support_3D_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        MAP_CONFIG::MAP_CONTROL_3D = true;
    }
    else
    {
        MAP_CONFIG::MAP_CONTROL_3D = false;
    }
}

void MapSetting::on_support_ruler_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        MAP_CONFIG::MAP_CONTROL_SCALE = true;
    }
    else
    {
        MAP_CONFIG::MAP_CONTROL_SCALE = false;
    }
}

void MapSetting::on_show_Poi_Icon_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        MAP_CONFIG::MAP_POIICON_ON = true;
    }
    else
    {
        MAP_CONFIG::MAP_POIICON_ON = false;
    }
}

void MapSetting::on_show_Poi_Text_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        MAP_CONFIG::MAP_POITEXT_ON = true;
    }
    else
    {
        MAP_CONFIG::MAP_POITEXT_ON = false;
    }
}

void MapSetting::on_control_KeyBoard_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        MAP_CONFIG::MAP_KEYBOARD_CONTROL = true;
    }
    else
    {
        MAP_CONFIG::MAP_KEYBOARD_CONTROL = false;
    }
}

void MapSetting::on_control_Rolling_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        MAP_CONFIG::MAP_MOUSE_SCROLL_ZOOM = true;
    }
    else
    {
        MAP_CONFIG::MAP_MOUSE_SCROLL_ZOOM = false;
    }
}

void MapSetting::on_control_Drag_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        MAP_CONFIG::MAP_DRAG_CONTROL = true;
    }
    else
    {
        MAP_CONFIG::MAP_DRAG_CONTROL = false;
    }
}

void MapSetting::on_control_Drag_Flux_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        MAP_CONFIG::MAP_INERTIAL_DRAG = true;
    }
    else
    {
        MAP_CONFIG::MAP_INERTIAL_DRAG = false;
    }
}

void MapSetting::on_remove_Anmine_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        MAP_CONFIG::MAP_REMOVE_ANIMATION = true;
    }
    else
    {
        MAP_CONFIG::MAP_REMOVE_ANIMATION = false;
    }
}

void MapSetting::on_use_Insid_Controller_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        MAP_CONFIG::MAP_USE_INTERNAL_HTML = true;
    }
    else
    {
        MAP_CONFIG::MAP_USE_INTERNAL_HTML = false;
    }
}

void MapSetting::on_noCache_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        MAP_CONFIG::MAP_AUTO_CLEAR_CACHE = true;
    }
    else
    {
        MAP_CONFIG::MAP_AUTO_CLEAR_CACHE = false;
    }
}

void MapSetting::on_model_Earth_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        MAP_CONFIG::MAP_EARTHMODEL = true;
    }
    else
    {
        MAP_CONFIG::MAP_EARTHMODEL = false;
    }
}

void MapSetting::on_aoto_POS_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        MAP_CONFIG::MAP_AUTO_POSITIONING = true;
    }
    else
    {
        MAP_CONFIG::MAP_AUTO_POSITIONING = false;
    }
}

void MapSetting::on_saveanduse_btn_clicked()
{
    // 打印系统信息
    qDebug() << "System Information:";
    qDebug() << MAP_CONFIG::X;
    qDebug() << MAP_CONFIG::Y;
    qDebug() << MAP_CONFIG::MAP_AUTO_POSITIONING;
    qDebug() << MAP_CONFIG::MAP_POIICON_ON;
    qDebug() << MAP_CONFIG::MAP_POITEXT_ON;
    qDebug() << MAP_CONFIG::MAP_EARTHMODEL;
    qDebug() << MAP_CONFIG::MAP_DEFAULT_LOCATE;
    qDebug() << MAP_CONFIG::MAP_CONTROL_3D;
    qDebug() << MAP_CONFIG::MAP_CONTROL_SCALE;
    configManager config;
    config.config_Changed();
}

void MapSetting::on_cancle_btn_clicked()
{
    configManager config;
    config.config_Recovery();
    init();
}

void MapSetting::on_reset_btn_clicked()
{
    MAP_CONFIG::MAP_AUTO_POSITIONING = false;
    MAP_CONFIG::MAP_POIICON_ON = true;
    MAP_CONFIG::MAP_POITEXT_ON = true;
    MAP_CONFIG::MAP_EARTHMODEL = false;
    MAP_CONFIG::MAP_CONTROL_3D = true;
    MAP_CONFIG::MAP_CONTROL_SCALE = true;
    MAP_CONFIG::MAP_KEYBOARD_CONTROL = true;
    MAP_CONFIG::MAP_MOUSE_SCROLL_ZOOM = true;
    MAP_CONFIG::MAP_REMOVE_ANIMATION = true;
    MAP_CONFIG::MAP_USE_INTERNAL_HTML = true;
    MAP_CONFIG::MAP_AUTO_CLEAR_CACHE = false;
    MAP_CONFIG::MAP_DRAG_CONTROL = true;
    MAP_CONFIG::MAP_INERTIAL_DRAG = true;
    on_saveanduse_btn_clicked();
    init();
}
