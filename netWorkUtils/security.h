#ifndef SECURITY_H
#define SECURITY_H

#include <QObject>
#include <QSslConfiguration>
#include <QTimer>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include "configManager/configmanager.h"
#include "main.h"
#include <QThread>
#include <netWorkUtils/netWorkUtils.h>

class Security : public QObject
{
    Q_OBJECT

signals:
    void netError(QString errorStr);

public:
    explicit Security(QObject *parent = nullptr);

    // pingGET请求
    QString ping();

    // pingPOST请求
    QString pingpost();

    //获取token
    QString getToken();

    // 更新服务器密码残片
    QString updatePasswdPart();

private slots:
    void onnetError(QString errStr);
};

#endif // SECURITY_H
