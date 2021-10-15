#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QSettings>
#include <QHostAddress>

class configManager : public QObject
{
    Q_OBJECT
public:
    explicit configManager(QObject *parent = nullptr);

signals:

public:
    //配置读取
    void reader();
    //
    QString reader(QString group,QString key,QString value);
    //配置写入
    void writer(QString group,QString key,QString value);

private:
    QString inipath = "./config/config.data";
    QSettings settings;
};

/*网络配置数据全局存储*/
class net{
public:
    //IP连接地址
    static QHostAddress netIP;
    //IP端口号
    static quint16 netport;
};

#endif // CONFIGMANAGER_H
