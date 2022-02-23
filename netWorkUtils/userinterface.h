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

signals:
    void netError(QString err);

public:
    UserInterface();

    // 获取用户信息
    QString getUserInformation();

    // 写用户信息
    QString postUserInformation(QString userInformation);

private slots:
    void onnetError(QString err);
};

#endif // USERINTERFACE_H
