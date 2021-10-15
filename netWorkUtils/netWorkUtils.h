#ifndef NETWORKUTILS_H
#define NETWORKUTILS_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QMessageBox>

class netWorkUtils : public QObject
{
    Q_OBJECT
public:
    explicit netWorkUtils(QObject *parent = nullptr);
    ~netWorkUtils();

signals:
    QString netError();
    //网络异常时执行的槽函数
    void onError();

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
    //网络数据发送
    void send(QString str);

public:
    //通信套接字
    QTcpSocket socket;
    //客户端名称
    QString clientname;
};

#endif // NETWORKUTILS_H
