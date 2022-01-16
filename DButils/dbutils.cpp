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
//    QSqlQuery query;
//    QString str = QString("CREATE TABLE STUDENT ("
//                          "id INT PRIMARY KEY NOT NULL,"
//                          "name TEXT NOT NULL,"
//                          "grade REAL NOT NULL,"
//                          "class TEXT NOT NULL)");
//    if(query.exec(str)){
//        qDebug() << "未发现数据库表,新的数据库表已创建";
//    }else{
//        qDebug() << "数据库已存在" << str;
//    }

    db.close();
}
