#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QSettings>
#include <QHostAddress>
#include <QDebug>
#include <QCoreApplication>
#include <QHostInfo>

class configManager : public QObject
{
    Q_OBJECT
public:
    explicit configManager(QObject *parent = nullptr);

private:
    ///
    /// \brief 配置文件读取
    ///
    void reader();
    ///
    /// \brief 配置文件写入
    ///
    void writer();

private:
    QString inipath = "./config/config.ini";

};

/*网络配置数据全局存储*/
class CONFIG_CORE{
public:

    ///
    /// \brief 系统运行状态
    ///
    static bool RUN_FIRST;

    ///
    /// \brief 服务器IP
    ///
    static QHostAddress SERVICE_IP;

    ///
    /// \brief 服务器端口号
    ///
    static quint16 SERVICE_PORT;

    ///
    /// \brief 本地数据库用户名
    ///
    static QString DB_USERNAME;

    ///
    /// \brief 本地数据库密码残片
    ///
    static QString DB_PASSWD_PART;

};

#endif // CONFIGMANAGER_H
