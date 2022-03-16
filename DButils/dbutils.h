#ifndef DBUTILS_H
#define DBUTILS_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "configManager/configmanager.h"
#include "DButils/nodeinfos.h"
#include "QFileInfo"

class DButils
{

public:
    DButils();
    ~DButils();
    // 重置密码
    void resetPasswd(QString newpass);

    // 数据库初始化
    bool initDB();
    bool initData();

    // 读取用户名和密码等等的其他信息到系统数据库
    int readUserInfo();

    // 写入用户名和密码等等的其他信息到系统数据库
    void writeUserInfo();

    // 存储结点信息的容器
    static QVector<NodeInfos> nodeList;
};

#endif // DBUTILS_H
