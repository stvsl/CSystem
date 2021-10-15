#include "configmanager.h"

/*网络成员全局变量*/
QHostAddress net::netIP;
quint16 net::netport;

configManager::configManager(QObject *parent) : QObject(parent)
{
    settings.setPath(QSettings::NativeFormat,QSettings::UserScope,inipath);
}

//基础数据预读取函数
void configManager::reader()
{
    net::netIP.setAddress(settings.value("Net/IP").toString());
    net::netport = settings.value("Net/port").toUInt();
}

QString configManager::reader(QString group,QString key,QString value)
{
    return settings.value(group + "/" + key,value).toString();
}

void configManager::writer(QString group,QString key,QString value)
{
    settings.setValue(group + "/" + key,value);
}
