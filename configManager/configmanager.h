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

public slots:
    ///
    /// \brief 系统配置文件被修改时执行的槽函数
    ///
    void config_Changed();

private:
    QString inipath = "./config/config.ini";

};

/***
 *  系统核心配置
 */
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
    /// \brief 本地数据库用户名片段
    ///
    static QString DB_USERNAME_PART;

    ///
    /// \brief 本地数据库密码残片
    ///
    static QString DB_PASSWD_PART;
};



#endif // CONFIGMANAGER_H
