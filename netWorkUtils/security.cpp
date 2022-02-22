#include "security.h"

Security::Security(QObject *parent) : QObject(parent)
{
}

QString Security::ping()
{
    netWorkUtils nwu;
    // 绑定信号
    connect(&nwu, SIGNAL(netError(QString)), this, SLOT(onnetError(QString)));
    QString url = "/ping";
    nwu.get(url);
    QString result = nwu.exec();
    qDebug() << "ping result:" << result;
    nwu.deleteLater();
    return result;
}

void Security::onnetError(QString errStr)
{
    emit netError(errStr);
}
