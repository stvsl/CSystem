#include "netWorkUtils.h"
#include "configManager/configmanager.h"
#include <QMessageBox>

netWorkUtils::netWorkUtils(QObject *parent) : QObject(parent)
{
    //绑定连接
    socket.connectToHost(net::netIP,net::netport);
    socket.write(net::hostname.toUtf8() + "OK");
}



