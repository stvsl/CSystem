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

    
private:
    QTimer timer;
};

#endif // USERINTERFACE_H
