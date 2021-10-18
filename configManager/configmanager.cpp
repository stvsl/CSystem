#include "configmanager.h"

/*网络成员全局变量*/
//netIP：此变量将会暴露到netWorkUtils中，作为运行时所需要的IP地址使用
QHostAddress net::netIP;
//netport：此变量将会暴露到netWorkUtils中，作为运行时所需要的端口信息使用
quint16 net::netport;

/*全局变量*/
//isFirst:表示整个程序是否是初次启动，若是则为true；此参数将会在程序启动时被读取，可用于系统重置，此参数将会暴露给main,用于判断是否启动初始设置引导界面
bool configManager::isFirst = false;

/*数据库变量*/


configManager::configManager(QObject *parent) : QObject(parent)
{
    settings.setPath(QSettings::IniFormat,QSettings::UserScope,inipath);
    //执行恢复函数，恢复函数将会先进行判定是否是初次运行随后完成初始化流程
    recover();
}

void configManager::recover()
{
    qDebug() << inipath;
    //判断配置文件是否存在，如果不存在，则可确定程序是第一次运行或被误删除，配置文件数据视为不会被人为修改，但保守起见，在配置文件中添加初次判定，便于后期维护
    QFileInfo exist(inipath);
    if(exist.isFile() == false){
        if(settings.value("Global/isfirststart").toString() == "true"){
            isFirst = true;
        }
    }
    if(isFirst == true){
        writer();
    }else{
        reader();
    }
}

//初始化设置函数
void configManager::writer()
{
    qDebug() << "判定为初次启动，正在初始化";
    /*全局*/
    settings.setValue("Global/isfirststart","false");
    /*网络*/
    settings.setValue("Net/IP","127.0.0.1");
    settings.setValue("Net/port","8080");
    /*数据库*/

    //调用reader函数进行基本配置的预读取

}

//基础数据预读取函数,由于其特殊性，不暴露且禁止调用
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
