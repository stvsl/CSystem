#include "networkconfig.h"

netWorkConfig::netWorkConfig(QObject *parent) : QObject(parent)
{
    //建立连接槽函数
    connect(&socket,SIGNAL(connected()),this,SLOT(onConnected()));
    //断开连接槽函数
    connect(&socket,SIGNAL(disconnected()),this,SLOT(onDisconnected()));
    //表示接收消息的槽函数
    connect(&socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    //处理网络异常的槽函数
    connect(&socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onError()));

    /*启动网络组件*/
    netServiceStart();
}

netWorkConfig::~netWorkConfig()
{
    netServiceStop();
}

void netWorkConfig::netServiceStart()
{

}

void netWorkConfig::netServiceStop()
{

}
