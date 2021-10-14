#include "configmanager.h"

configManager::configManager(QObject *parent) : QObject(parent)
{
    settings.setPath(QSettings::NativeFormat,QSettings::UserScope,inipath);
}

void configManager::reader()
{

}

void configManager::writer()
{
    settings.setValue("","");
}
