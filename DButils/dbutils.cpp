#include "dbutils.h"
/***
 * 数据库组件介绍:
 * 此数据库组件属于客户端的组件，数据库本身除备份外不存储与生产资料有关的任何东西，备份功能将会用来进行紧急数据库还原和运行验证，使用sqllite数据库
***/
/*数据库密码*/

DButils::DButils()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("SDB.db");
        db.setUserName("test");
        db.setPassword("2060");
    }
    db.open();
    db.close();
}
