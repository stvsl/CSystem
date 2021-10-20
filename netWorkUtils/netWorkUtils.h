#ifndef NETWORKUTILS_H
#define NETWORKUTILS_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>

class netWorkUtils : public QObject
{
    Q_OBJECT
public:
    explicit netWorkUtils(QObject *parent = nullptr);

signals:
    void netError();

private slots:
    void newMsg();
    //网络组件异常
    void onError();

private:
    //网络模块启动
    void netServiceStart();
    //网络模块关闭
    void netServiceStop();
    //接受服务器转发的消息的槽函数
    //网络数据发送
    void send(QString str);

public:
    //通信套接字
    QTcpSocket socket;
    //客户端名称
    QString clientname;
};



#endif // NETWORKUTILS_H
