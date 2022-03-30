#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QSettings>
#include <QHostAddress>
#include <QDebug>
#include <QCoreApplication>
#include <QHostInfo>
#include "main.h"

class configManager : public QObject
{
    Q_OBJECT
public:
    explicit configManager(QObject *parent = nullptr);
    void getPasswd();

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

    void config_Recovery();

public:
    void makeRSA();
};

///
/// \brief 系统核心配置
/// \author stvsl
/// \date 2022.1.6
///
class CONFIG_CORE
{
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
    /// \brief 服务器域名
    ///
    static QString SERVICE_DOMAIN;

    ///
    /// \brief 本地数据库密码残片
    ///
    static QString DB_PASSWD_PART;

    ///
    /// \brief 完整的数据库密码
    ///
    static QString DB_PASSWD;

    ///
    /// \brief 用户类型
    ///  0：一般用户
    ///  1：数据录入人员
    ///  2：地方管理员
    ///  3：最高权限管理员
    ///  4: 安装维护人员
    ///
    static int USER_TYPE;

    ///
    /// \brief 本地RSA_PRIVATE_KEY
    ///
    static QString RSA_PRIVATE_KEY;

    ///
    /// \brief 本地RSA_PUBLIC_KEY
    ///
    static QString RSA_PUBLIC_KEY;

    ///
    /// \brief 服务器RSA_PUBLIC_KEY
    ///
    static QString RSA_SERVER_PUBLIC_KEY;

    ///
    /// \brief 本次系统特征值
    ///
    static QString SYSTEM_FEATURE;
};

///
/// \brief 登陆配置
/// \author stvsl
/// \date 2022.2.6
class LOGIN_CONFIG
{
public:
    ///
    /// \brief 自动登陆状态
    ///
    static bool AUTO_LOGIN;

    ///
    /// \brief 保存密码状态
    ///
    static bool SAVE_PASSWD;

    ///
    /// \brief 账户ID
    ///
    static QString ID;

    ///
    /// \brief 账户密码
    ///
    static QString PASSWD;
};

class ID_CARD
{

public:
    // 账户类型
    static int TYPE;

    // 用户姓名
    static QString USERNAME;

    // 身份证号
    static QString USERID;

    // 电话号码
    static QString TEL;

    // 家庭住址
    static QString USERLOCATE;

    // 所属机构代码
    static QString ORGANIZATION;
};

#endif // CONFIGMANAGER_H
