#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QObject>
#include <QSslConfiguration>
#include <QTimer>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include "configManager/configmanager.h"
#include "main.h"

class UserInterface : public QObject
{
    Q_OBJECT
public:
    UserInterface();

    // 获取用户信息
    QString getUserInformation();

    // 写用户信息
    QString postUserInformation(QString userInformation);

    
    // pingGET请求
    QString ping();

    // pingPOST请求
    QString pingpost();

    //获取token
    QString getToken();

    // 更新服务器密码残片
    QString updatePasswdPart();
private:
    QTimer timer;
};

#endif // USERINTERFACE_H
