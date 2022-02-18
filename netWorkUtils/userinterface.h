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

    QString getUserInformation();
private:
    QTimer timer;
};

#endif // USERINTERFACE_H
