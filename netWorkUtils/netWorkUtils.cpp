#include "netWorkUtils.h"
#include "configManager/configmanager.h"
#include <QMessageBox>

netWorkUtils::netWorkUtils(QObject *parent) : QObject(parent)
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
    socket.write("OK!");
}

netWorkUtils::~netWorkUtils()
{
    netServiceStop();
}

void netWorkUtils::netServiceStart()
{
   socket.connectToHost(net::netIP,net::netport);
}

void netWorkUtils::netServiceStop()
{
    socket.disconnectFromHost();
}

void netWorkUtils::send(QString str)
{
    socket.write(str.toUtf8());
}
