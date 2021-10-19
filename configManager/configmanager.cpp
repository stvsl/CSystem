#include "configmanager.h"

/*网络成员全局变量*/
//netIP：需要连接的服务器的ip地址，此变量将会暴露到netWorkUtils中，作为运行时所需要的IP地址使用
QHostAddress net::netIP;
//netport：需要连接的服务器的端口号，此变量将会暴露到netWorkUtils中，作为运行时所需要的端口信息使用
quint16 net::netport;
//hostname：当前设备的主机名，此变量将会暴露到全局，作为运行时必要数据
QString net::hostname;
//netname：当前连接后服务器反馈的网络使用名称，作为运行时必要数据
QString net::netname;

/*全局变量*/
//isFirst:表示整个程序是否是初次启动，若是则为true；此参数将会在程序启动时被读取，可用于系统重置，此参数将会暴露给main,用于判断是否启动初始设置引导界面
bool configManager::isFirst = false;

/*数据库变量*/


configManager::configManager(QObject *parent) : QObject(parent)
{
    QSettings settings(QCoreApplication::applicationDirPath() + inipath,QSettings::IniFormat);
    net::hostname = QString(QHostInfo::localHostName());
    //执行恢复函数，恢复函数将会先进行判定是否是初次运行随后完成初始化流程
    recover();
}

void configManager::recover()
{
    qDebug() << inipath;
    if (settings.value("Global/recover").toString() == "ture" ||settings.value("Global/recover").toString() == ""){
        qDebug() << "配置文件不存在或已被设置要求恢复初始状态，即将开始重置";
        isFirst = true;
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
    qDebug() << "判定为初次启动，正在重置";
    /*全局*/
    settings.setValue("Global/recover","false");
    /*网络*/
    settings.setValue("Net/IP","127.0.0.1");
    settings.setValue("Net/port","8080");
    /*数据库*/

    //调用reader函数进行基本配置的预读取
    reader();

}

//基础数据预读取函数,由于其特殊性，不暴露且禁止调用
void configManager::reader()
{
    /*网络成员*/
    net::netIP.setAddress(settings.value("Net/IP").toString());
    net::netport = settings.value("Net/port").toUInt();
    /*数据库成员*/
}

QString configManager::reader(QString group,QString key,QString value)
{
    return settings.value(group + "/" + key,value).toString();
}

void configManager::writer(QString group,QString key,QString value)
{
    settings.setValue(group + "/" + key,value);
}
