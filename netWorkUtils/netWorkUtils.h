#ifndef NETWORKUTILS_H
#define NETWORKUTILS_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "main.h"
#include <QSslConfiguration>

class netWorkUtils : public QObject
{
    Q_OBJECT
public:
    explicit netWorkUtils(QObject *parent = nullptr);

signals:
   void netError(QString errorStr);

public:
    //网络重连函数
    void reConnect();

private:
    QTimer timer;

public:
    QString ping();

    //获取token
    void getToken();

    // 更新服务器密码残片
    void updatePasswdPart();
};

#endif // NETWORKUTILS_H
