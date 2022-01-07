#include "configmanager.h"
#include "mapconfig.h"

//初始默认值
//系统核心配置文件默认值
bool CONFIG_CORE::RUN_FIRST = true;
QHostAddress CONFIG_CORE::SERVICE_IP = QHostAddress("127.0.0.1");
quint16 CONFIG_CORE::SERVICE_PORT = 8000;
QString CONFIG_CORE::DB_USERNAME_PART = "STVSL_JL";
QString CONFIG_CORE::DB_PASSWD_PART = "DO1900281VE";
int CONFIG_CORE::USER_TYPE = 0;

//地图自定义配置文件默认值
bool MAP_CONFIG::MAP_AUTO_POSITIONING = false;
bool MAP_CONFIG::MAP_POIICON_ON = true;
bool MAP_CONFIG::MAP_POITEXT_ON = true;
bool MAP_CONFIG::MAP_EARTHMODEL = false;
QString MAP_CONFIG::MAP_DEFAULT_LOCATE = nullptr;
bool MAP_CONFIG::MAP_CONTROL_3D = true;
bool MAP_CONFIG::MAP_CONTROL_SCALE = true;


configManager::configManager(QObject *parent) : QObject(parent)
{
    QSettings settings(QCoreApplication::organizationName() ,QCoreApplication::applicationName());
    settings.setPath(QSettings::IniFormat,QSettings::UserScope,"./config");
    qDebug() << settings.fileName();
    CONFIG_CORE::RUN_FIRST = settings.value("CORE/RUNFIRST").Bool;
    if(CONFIG_CORE::RUN_FIRST){
        writer();
    }else{
        reader();
    }
}

void configManager::writer()
{
    QSettings settings(QCoreApplication::organizationName() ,QCoreApplication::applicationName());
    settings.setPath(QSettings::IniFormat,QSettings::UserScope,"./config/config.rc");
    settings.beginGroup("CORE");
    settings.setValue("RUN_FIRST",CONFIG_CORE::RUN_FIRST);
    settings.setValue("SERVICE_IP",CONFIG_CORE::SERVICE_IP.toString());
    settings.setValue("SERVICE_PORT",CONFIG_CORE::SERVICE_PORT);
    settings.setValue("PART1",CONFIG_CORE::DB_USERNAME_PART);
    settings.setValue("PART2",CONFIG_CORE::DB_PASSWD_PART);
    settings.endGroup();
    settings.beginGroup("MAP");
    settings.setValue("MAP_AUTO_POSITIONING",MAP_CONFIG::MAP_DEFAULT_LOCATE);
    settings.setValue("MAP_AUTO_POSITIONING",MAP_CONFIG::MAP_AUTO_POSITIONING);
    settings.setValue("MAP_CONTROL_3D",MAP_CONFIG::MAP_CONTROL_3D);
    settings.setValue("MAP_CONTROL_SCALE",MAP_CONFIG::MAP_CONTROL_SCALE);
    settings.setValue("MAP_EARTHMODEL",MAP_CONFIG::MAP_EARTHMODEL);
    settings.setValue("MAP_POIICON_ON",MAP_CONFIG::MAP_POIICON_ON);
    settings.setValue("MAP_POITEXT_ON",MAP_CONFIG::MAP_POITEXT_ON);
    settings.endGroup();
}


void configManager::reader()
{
    QSettings settings(QCoreApplication::organizationName() ,QCoreApplication::applicationName());
    settings.setPath(QSettings::IniFormat,QSettings::UserScope,"./config/config.rc");
    settings.beginGroup("CORE");
    CONFIG_CORE::SERVICE_IP = QHostAddress(settings.value("SERVICE_IP").toString());
    CONFIG_CORE::SERVICE_PORT = settings.value("SERVICE_PORT").toInt();
    CONFIG_CORE::DB_USERNAME_PART = settings.value("PART1").toString();
    CONFIG_CORE::DB_PASSWD_PART = settings.value("PART2").toString();
    settings.endGroup();
    settings.beginGroup("MAP");
    MAP_CONFIG::MAP_AUTO_POSITIONING = settings.value("MAP_AUTO_POSITIONING").Bool;
    MAP_CONFIG::MAP_CONTROL_3D = settings.value("MAP_CONTROL_3D").Bool;
    MAP_CONFIG::MAP_CONTROL_SCALE = settings.value("MAP_CONTROL_SCALE").Bool;
    MAP_CONFIG::MAP_DEFAULT_LOCATE = settings.value("MAP_DEFAULT_LOCATE").toString();
    MAP_CONFIG::MAP_EARTHMODEL = settings.value("MAP_EARTHMODEL").Bool;
    MAP_CONFIG::MAP_POIICON_ON = settings.value("MAP_POIICON_ON").Bool;
    MAP_CONFIG::MAP_POITEXT_ON = settings.value("MAP_POITEXT_ON").Bool;
    settings.endGroup();
}

void configManager::config_Changed(){
    writer();
}
