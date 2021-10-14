#ifndef NETWORKCONFIG_H
#define NETWORKCONFIG_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QMessageBox>

class netWorkConfig : public QObject
{
    Q_OBJECT
public:
    explicit netWorkConfig(QObject *parent = nullptr);
    ~netWorkConfig();

signals:
    QString netError();

private:
    //网络模块启动
    void netServiceStart();
    //网络模块关闭
    void netServiceStop();
    //和服务器连接成功时执行的槽函数
    void onConnected();
    //和服务器断开连接时执行的槽函数
    void onDisconnected();
    //接受服务器转发的消息的槽函数
    void onReadyRead();
    //网络异常时执行的槽函数
    void onError();

private:
    //通信套接字
    QTcpSocket socket;
    //服务器IP地址
    QHostAddress serverIP;
    //服务器端口
    quint16 serverPort;
    //客户端名称
    QString clientname;
};

#endif // NETWORKCONFIG_H
