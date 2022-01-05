#include "mapconfig.h"

//默认初始值

bool mapConfig::MAP_AUTO_POSITIONING = false;
bool mapConfig::MAP_CONTROL_3D = true;
bool mapConfig::MAP_CONTROL_SCALE = true;
QString mapConfig::MAP_DEFAULT_LOCATE = nullptr;
bool mapConfig::MAP_EARTHMODEL = false;
bool mapConfig::MAP_POIICON_ON = true;
bool mapConfig::MAP_POITEXT_ON = true;

mapConfig::mapConfig(QObject *parent)
    : QObject{parent}
{
    reader();
    writer();
}

void mapConfig::reader(){

}


void mapConfig::writer(){

}
