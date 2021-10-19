#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QSettings>
#include <QHostAddress>
#include <QFileInfo>
#include <QDebug>
#include <QCoreApplication>
#include <QHostInfo>

class configManager : public QObject
{
    Q_OBJECT
public:
    explicit configManager(QObject *parent = nullptr);

signals:

public:
    //初始第一次运行判定器
    static bool isFirst;
    //配置读取（指定加载）
    QString reader(QString group,QString key,QString value);
    //配置写入
    void writer(QString group,QString key,QString value);
    //初始化
    void recover();

private:
    //配置读取（预加载）
    void reader();
    //配置文件初始化函数
    void writer();

private:
    QString inipath = "/config/config.ini";
    QSettings settings;
};

/*网络配置数据全局存储*/
class net{
public:
    //IP连接地址
    static QHostAddress netIP;
    //IP端口号
    static quint16 netport;
    //设备名称
    static QString hostname;
    //网络中名称
    static QString netname;
};

#endif // CONFIGMANAGER_H
