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
    void netError(QString errorStr);

private slots:
    void newMsg();
    //网络组件异常
    void onError();

private:
    //网络模块启动
    void Start();
    //网络模块关闭
    void Stop();

public:
    //网络数据发送
    void send(QString str);
    //网络重连函数
    void reConnect();

private:
    //通信套接字
    QTcpSocket socket;
    //客户端名称
    QString clientname;
};



#endif // NETWORKUTILS_H
