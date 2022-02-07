#include "dbutils.h"

DButils::DButils()
{
    QSqlDatabase::addDatabase("QSQLITE", "default");
    // 检查数据库文件是否存在
    QFileInfo check_file("./SDB.db");
    if (!check_file.exists() || !check_file.isFile())
    {
        qDebug() << "数据库文件不存在，创建数据库文件";
        initDB();
    }
}
DButils::~DButils()
{
    QSqlDatabase::removeDatabase("default");
}

void DButils::readUserInfo()
{
    // 连接到数据库
    QSqlDatabase db = QSqlDatabase::database("default");
    db.setPassword(CONFIG_CORE::DB_PASSWD);
    if (!db.open())
    {
        qDebug() << "数据库连接失败";
        return;
    }

    // 查询ID,密码,自动登陆和记住密码状态
    QSqlQuery query(db);
    query.exec("SELECT ID,PASSWD,AUTO_LOGIN,SAVE_PASSWD FROM CONFIG");
    while (query.next())
    {
        LOGIN_CONFIG::ID = query.value(0).toString();
        LOGIN_CONFIG::PASSWD = query.value(1).toString();
        LOGIN_CONFIG::AUTO_LOGIN = query.value(2).toBool();
        LOGIN_CONFIG::SAVE_PASSWD = query.value(3).toBool();
    }
}

bool DButils::initDB()
{
    // 建立default数据库连接
    QSqlDatabase dbconn = QSqlDatabase::contains("default") ? QSqlDatabase::database("default") : QSqlDatabase::addDatabase("default");
    dbconn.setDatabaseName("SDB.db");
    dbconn.setPassword(CONFIG_CORE::DB_PASSWD);
    if (!dbconn.open())
    {
        qDebug() << "Failed to connect to database." << dbconn.lastError();
        return false;
    }
    // 创建CONFIG表
    QSqlQuery query(dbconn);
    query.exec("CREATE TABLE CONFIG (ID TEXT,PASSWD TEXT,AUTO_LOGIN BLOB,SAVE_PASSWD BLOB, RSA_PRIVATE TEXT, RSA_PUBLIC TEXT, \"TYPE\" INTEGER, USER_NAME TEXT, USER_ID TEXT,USER_PHONE TEXT, USER_LOCATE TEXT, ORGANIZATION TEXT);");
    query.clear();
    // 创建ProfessionalData表
    query.exec("CREATE TABLE ProfessionalData (ID TEXT,COMMUNITY TEXT,COMID TEXT,TIME TEXT,STATUS INTEGER,DESCRIPTION TEXT,PH_INDIRECT_HIGH REAL,PH_INDORECT_LOW REAL,PH_DIRECT_HIGH REAL,PH_DIRECT_LOW REAL,COD_DIRECT REAL,COD_INDIRECT REAL,TP_DIRECT REAL,TP_INDIRECT REAL,TN_DIRECT REAL,IP_INDIRECT REAL,AN_DIRECT REAL,AN_INDIRECT REAL,OCC_DIRECT REAL,OCC_INDIRECT REAL,FSC_DIRECT_T REAL,FSC_INDIRECT_T REAL,FSC_DIRECT_O REAL,FSC_INDIRECT_O REAL,SA_DIRECT REAL,SA_INDIRECT REAL,F_DIRECT REAL,F_INDIRECT REAL,CU REAL,ZN REAL,SN REAL,SB REAL,HG REAL,CD REAL,PB REAL,ASD REAL,CR6 REAL,GC REAL,DENSITY REAL,CONDUCTIVITY REAL,MC REAL,SC REAL,TOC REAL,BOD5_DIRECT REAL,BOD5_INDIRECT REAL,BOD REAL,P_DIRECT REAL,BC REAL,SLC REAL,COLOR_DIRECT REAL,COLOR_INDIRECT REAL,AF_DIRECT REAL,AF_INDIRECT REAL,CL_DIRECT REAL,CL_INDIRECT REAL,P_INDIRECT REAL,CR REAL,TON REAL);");
    query.clear();
    // 创建索引
    query.exec("CREATE INDEX ProfessionalData_ID_IDX ON ProfessionalData (ID,COMMUNITY,COMID,TIME,STATUS);");
    query.clear();
    // 创建TSDB记录存储表
    query.exec("CREATE TABLE TSDB(NODEID TEXT,TIME INT,STATUS INTEGER,GASCONCENTRATION REAL,TEMPERATURE REAL,PH REAL,DENSITY REAL,CONDUCTIVITY REAL,OXYGENCONCENTRATION REAL,METALCONCENTRATION REAL,SOLIDSCONCENTRATION REAL,FLOATINGSOLIDSCONCENTRATION REAL,TOTALNITROGEN REAL,TOTALPHOSPHORUS REAL,TOTALORGANICCARBON REAL,BIOLOGICALOXYGENDEMAND REAL,CHEMICALOXYGENDEMAND REAL,BACTERIACOUNT INT,STAPHYLOCOCCUSCOUNT INT);");
    query.clear();
    // 创建索引
    query.exec("CREATE INDEX TSDB_NODEID_IDX ON TSDB (NODEID,TIME,STATUS);");
    query.clear();
    dbconn.close();
    qDebug() << "数据库初始化完成";
    initData();
    return true;
}

bool DButils::initData(){
    // 建立default数据库连接
    qDebug() << "正在写入默认数据";
    QSqlDatabase dbconn = QSqlDatabase::contains("default") ? QSqlDatabase::database("default") : QSqlDatabase::addDatabase("default");
    dbconn.setDatabaseName("SDB.db");
    dbconn.setPassword(CONFIG_CORE::DB_PASSWD);
    if (!dbconn.open())
    {
        qDebug() << "Failed to connect to database." << dbconn.lastError();
        return false;
    }
    // 清空CONFIG表并写入默认数据
    QSqlQuery query(dbconn);
    query.exec("DELETE FROM CONFIG");
    query.clear();
    query.prepare("INSERT INTO CONFIG (ID,PASSWD,AUTO_LOGIN,SAVE_PASSWD,RSA_PRIVATE,RSA_PUBLIC,\"TYPE\",USER_NAME,USER_ID,USER_PHONE,USER_LOCATE,ORGANIZATION) VALUES (:ID,:PASSWD,:AUTO_LOGIN,:SAVE_PASSWD,:RSA_PRIVATE,:RSA_PUBLIC,:TYPE,:USER_NAME,:USER_ID,:USER_PHONE,:USER_LOCATE,:ORGANIZATION)");
    // 重置参数值
    LOGIN_CONFIG::ID = "";
    LOGIN_CONFIG::PASSWD = "";
    LOGIN_CONFIG::AUTO_LOGIN = false;
    LOGIN_CONFIG::SAVE_PASSWD = false;
    LOGIN_CONFIG::RSA_PRIVATE_KEY = "";
    LOGIN_CONFIG::RSA_PUBLIC_KEY = "";
    CONFIG_CORE::USER_TYPE = 0;
    USER_CONFIG::USER_NAME = "";
    USER_CONFIG::USER_ID = "";
    USER_CONFIG::USER_PHONE = "";
    USER_CONFIG::USER_LOCATE = "";
    USER_CONFIG::ORGANIZATION = "";

    query.bindValue(":ID", LOGIN_CONFIG::ID);
    query.bindValue(":PASSWD", LOGIN_CONFIG::PASSWD);
    query.bindValue(":AUTO_LOGIN", LOGIN_CONFIG::AUTO_LOGIN);
    query.bindValue(":SAVE_PASSWD", LOGIN_CONFIG::SAVE_PASSWD);
    query.bindValue(":RSA_PRIVATE", LOGIN_CONFIG::RSA_PRIVATE_KEY);
    query.bindValue(":RSA_PUBLIC", LOGIN_CONFIG::RSA_PUBLIC_KEY);
    query.bindValue(":TYPE", CONFIG_CORE::USER_TYPE);
    query.bindValue(":USER_NAME", USER_CONFIG::USER_NAME);
    query.bindValue(":USER_ID", USER_CONFIG::USER_ID);
    query.bindValue(":USER_PHONE", USER_CONFIG::USER_PHONE);
    query.bindValue(":USER_LOCATE", USER_CONFIG::USER_LOCATE);
    query.bindValue(":ORGANIZATION", USER_CONFIG::ORGANIZATION);
    query.exec();
    query.clear();
    // 关闭数据库连接
    dbconn.close();
    return true;
}

void DButils::resetPasswd(QString newpass)
{
    // 连接到SQLITECIPHER数据库
    QSqlDatabase dbconn = QSqlDatabase::database("default");
    dbconn.setDatabaseName("SDB.db");
    dbconn.setPassword(CONFIG_CORE::DB_PASSWD);
    dbconn.setConnectOptions("QSQLITE_UPDATE_KEY=" + newpass);
    // 关闭数据库
    dbconn.close();
}
