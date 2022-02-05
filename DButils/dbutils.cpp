#include "dbutils.h"


DButils::DButils()
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("SQLITECIPHER");
        db.setDatabaseName("SDB.db");
        db.setPassword("2060");
        db.setConnectOptions("QSQLITE_CREATE_KEY");
        db.setConnectOptions("QSQLITE_USE_CIPHER=aes256cbc");
    }
    if (!db.open()) {
        qDebug() << "Can not open connection: " << db.lastError().driverText();
    }else{
        qDebug() << "DB open successful!!!";
    }
    db.close();
}
