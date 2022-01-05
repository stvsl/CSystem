#include "netWorkUtils.h"
#include "configManager/configmanager.h"

netWorkUtils::netWorkUtils(QObject *parent) : QObject(parent)
{
    //绑定连接
    socket.connectToHost(CONFIG_CORE::SERVICE_IP,CONFIG_CORE::SERVICE_PORT);
    //表示接收消息的槽函数
    connect(&socket,SIGNAL(readyRead()),this,SLOT(newMsg()));
    //处理网络异常的槽函数
    connect(&socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onError()));
    Start();
}

void netWorkUtils::onError(){
    QString errorstr = socket.errorString();
    qDebug() << errorstr;
    //发送信号
    emit netError(errorstr);
}

void netWorkUtils::newMsg(){
    qDebug() << socket.readAll();

}

//重连槽函数
void netWorkUtils::reConnect(){
    socket.connectToHost(CONFIG_CORE::SERVICE_IP,CONFIG_CORE::SERVICE_PORT);
}

void netWorkUtils::Start(){

}

void netWorkUtils::Stop(){

}
