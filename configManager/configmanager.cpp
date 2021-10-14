#include "configmanager.h"

configManager::configManager(QObject *parent) : QObject(parent)
{
    settings.setPath(QSettings::NativeFormat,QSettings::UserScope,inipath);
}

void configManager::reader()
{

}

QString configManager::reader(QString group,QString key,QString value)
{
    return settings.value(group + "/" + key,value).toString();
}

void configManager::writer(QString group,QString key,QString value)
{
    settings.setValue(group + "/" + key,value);
}
