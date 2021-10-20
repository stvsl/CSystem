#include "netWorkUtils.h"
#include "configManager/configmanager.h"

netWorkUtils::netWorkUtils(QObject *parent) : QObject(parent)
{
    //绑定连接
    socket.connectToHost(net::netIP,net::netport);
    //表示接收消息的槽函数
    connect(&socket,SIGNAL(readyRead()),this,SLOT(newMsg()));
    //处理网络异常的槽函数
    connect(&socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onError()));
}

void netWorkUtils::onError(){

}

void netWorkUtils::newMsg(){

}
