#include "dbutils.h"

DButils::DButils()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(".db");
        db.setUserName("XingYeZhiXia");
        db.setPassword("123456");
    }
}
