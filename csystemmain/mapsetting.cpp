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
    ui->webView->setUrl(QUrl("http://127.0.0.1:10241/pages/default/map"));
    channelsetting = new QWebChannel(this);             //通讯对象
    channelsetting->registerObject("trans", this);      //通信介质注册
    ui->webView->page()->setWebChannel(channelsetting); //通讯附加
    // 阴影效果
    effect1 = new QGraphicsDropShadowEffect(ui->label);
    effect1->setOffset(0, 0);
    effect1->setColor(QColor(125, 164, 255, 80));
    effect1->setBlurRadius(10);
    ui->label->setGraphicsEffect(effect1);
    configManager config;
    config.config_Recovery();
    init();
}

MapSetting::~MapSetting()
{
    delete effect1;
    delete channelsetting;
    delete ui;
}

void MapSetting::init()
{
    if (MAP_CONFIG::MAP_CONTROL_3D)
    {
        ui->support_3D->setChecked(true);
    }
    else
    {
        ui->support_3D->setChecked(false);
    }
    if (MAP_CONFIG::MAP_CONTROL_SCALE)
    {
        ui->support_ruler->setChecked(true);
    }
    else
    {
        ui->support_ruler->setChecked(false);
    }
    if (MAP_CONFIG::MAP_POIICON_ON)
    {
        ui->show_Poi_Text->setChecked(true);
    }
    else
    {
        ui->show_Poi_Text->setChecked(false);
    }
    if (MAP_CONFIG::MAP_POITEXT_ON)
    {
        ui->show_Poi_Icon->setChecked(true);
    }
    else
    {
        ui->show_Poi_Icon->setChecked(false);
    }
    if (MAP_CONFIG::MAP_KEYBOARD_CONTROL)
    {
        ui->control_KeyBoard->setChecked(true);
    }
    else
    {
        ui->control_KeyBoard->setChecked(false);
    }
    if (MAP_CONFIG::MAP_MOUSE_SCROLL_ZOOM)
    {
        ui->control_Rolling->setChecked(true);
    }
    else
    {
        ui->control_Rolling->setChecked(false);
    }
    if (MAP_CONFIG::MAP_DRAG_CONTROL)
    {
        ui->control_Drag->setChecked(true);
    }
    else
    {
        ui->control_Drag->setChecked(false);
    }
    if (MAP_CONFIG::MAP_INERTIAL_DRAG)
    {
        ui->control_Drag_Flux->setChecked(true);
    }
    else
    {
        ui->control_Drag_Flux->setChecked(false);
    }
    if (MAP_CONFIG::MAP_REMOVE_ANIMATION)
    {
        ui->remove_Anmine->setChecked(true);
    }
    else
    {
        ui->remove_Anmine->setChecked(false);
    }
    if (MAP_CONFIG::MAP_USE_INTERNAL_HTML)
    {
        ui->use_Insid_Controller->setChecked(true);
    }
    else
    {
        ui->use_Insid_Controller->setChecked(false);
    }
    if (MAP_CONFIG::MAP_AUTO_CLEAR_CACHE)
    {
        ui->noCache->setChecked(true);
    }
    else
    {
        ui->noCache->setChecked(false);
    }
    if (MAP_CONFIG::MAP_EARTHMODEL)
    {
        ui->model_Earth->setChecked(true);
    }
    else
    {
        ui->model_Earth->setChecked(false);
    }
    if (MAP_CONFIG::MAP_AUTO_POSITIONING)
    {
        ui->aoto_POS->setChecked(true);
    }
    else
    {
        ui->aoto_POS->setChecked(false);
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
        ui->webView->page()->runJavaScript("setPoiIcon(1)");
    }
    else
    {
        MAP_CONFIG::MAP_POIICON_ON = false;
        ui->webView->page()->runJavaScript("setPoiIcon(0)");
    }
}

void MapSetting::on_show_Poi_Text_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        MAP_CONFIG::MAP_POITEXT_ON = true;
        ui->webView->page()->runJavaScript("setPoiText(1)");
    }
    else
    {
        MAP_CONFIG::MAP_POITEXT_ON = false;
        ui->webView->page()->runJavaScript("setPoiText(0)");
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
        // js函数
        QString js = "setMapType(1);";
        ui->webView->page()->runJavaScript(js);
    }
    else
    {
        MAP_CONFIG::MAP_EARTHMODEL = false;
        // js函数
        QString js = "setMapType(0);";
        ui->webView->page()->runJavaScript(js);
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
    configManager config;
    config.config_Changed();
    init();
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
    MAP_CONFIG::MAP_REMOVE_ANIMATION = false;
    MAP_CONFIG::MAP_USE_INTERNAL_HTML = false;
    MAP_CONFIG::MAP_AUTO_CLEAR_CACHE = false;
    MAP_CONFIG::MAP_DRAG_CONTROL = true;
    MAP_CONFIG::MAP_INERTIAL_DRAG = true;
    on_saveanduse_btn_clicked();
    init();
}
