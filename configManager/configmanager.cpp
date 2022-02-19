#include "configmanager.h"
#include "mapconfig.h"
#include <QHostInfo>
#include "QNetworkInterface"
#include "QCryptographicHash"
#include <QDateTime>

//初始默认值

//系统核心配置文件默认值

bool CONFIG_CORE::RUN_FIRST = true;
QHostAddress CONFIG_CORE::SERVICE_IP = QHostAddress("127.0.0.1");
quint16 CONFIG_CORE::SERVICE_PORT = 10214;
// QString CONFIG_CORE::SERVICE_DOMAIN = "stvsljl.com";
QString CONFIG_CORE::SERVICE_DOMAIN = "127.0.0.1:10214";
QString CONFIG_CORE::DB_PASSWD_PART = "";
QString CONFIG_CORE::DB_PASSWD = "DO1900281VE";
int CONFIG_CORE::USER_TYPE = 0;
QString CONFIG_CORE::RSA_PRIVATE_KEY = "";
QString CONFIG_CORE::RSA_PUBLIC_KEY = "";
QString CONFIG_CORE::RSA_SERVER_PUBLIC_KEY = "";
QString CONFIG_CORE::SYSTEM_FEATURE = "";

// 登录配置默认值
bool LOGIN_CONFIG::AUTO_LOGIN = false;
bool LOGIN_CONFIG::SAVE_PASSWD = false;
QString LOGIN_CONFIG::ID = "";
QString LOGIN_CONFIG::PASSWD = "";

// 用户配置默认值
QString USER_CONFIG::USER_NAME = "";
QString USER_CONFIG::USER_ID = "";
QString USER_CONFIG::USER_LOCATE = "";
QString USER_CONFIG::USER_PHONE = "";
QString USER_CONFIG::ORGANIZATION = "";


//地图自定义配置文件默认值

bool MAP_CONFIG::MAP_AUTO_POSITIONING = false;
bool MAP_CONFIG::MAP_POIICON_ON = true;
bool MAP_CONFIG::MAP_POITEXT_ON = true;
bool MAP_CONFIG::MAP_EARTHMODEL = false;
QString MAP_CONFIG::MAP_DEFAULT_LOCATE = nullptr;
bool MAP_CONFIG::MAP_CONTROL_3D = true;
bool MAP_CONFIG::MAP_CONTROL_SCALE = true;


configManager::configManager(QObject *parent) : QObject(parent)
{
    QSettings settings(QCoreApplication::organizationName() ,QCoreApplication::applicationName());
    settings.setPath(QSettings::IniFormat,QSettings::UserScope,"./config");
    qDebug() << settings.fileName();
    CONFIG_CORE::RUN_FIRST = settings.value("CORE/RUNFIRST").Bool;
    if(CONFIG_CORE::RUN_FIRST){
        writer();
    }else{
        reader();
    }
    getPasswd();
}

void configManager::writer()
{
    QSettings settings(QCoreApplication::organizationName() ,QCoreApplication::applicationName());
    settings.setPath(QSettings::IniFormat,QSettings::UserScope,"./config/config.rc");
    settings.beginGroup("CORE");
    settings.setValue("RUN_FIRST",CONFIG_CORE::RUN_FIRST);
    settings.setValue("SERVICE_IP",CONFIG_CORE::SERVICE_IP.toString());
    settings.setValue("SERVICE_PORT",CONFIG_CORE::SERVICE_PORT);
    settings.setValue("PAR",CONFIG_CORE::DB_PASSWD_PART);
    settings.endGroup();

    settings.beginGroup("MAP");
    settings.setValue("MAP_AUTO_POSITIONING",MAP_CONFIG::MAP_DEFAULT_LOCATE);
    settings.setValue("MAP_AUTO_POSITIONING",MAP_CONFIG::MAP_AUTO_POSITIONING);
    settings.setValue("MAP_CONTROL_3D",MAP_CONFIG::MAP_CONTROL_3D);
    settings.setValue("MAP_CONTROL_SCALE",MAP_CONFIG::MAP_CONTROL_SCALE);
    settings.setValue("MAP_EARTHMODEL",MAP_CONFIG::MAP_EARTHMODEL);
    settings.setValue("MAP_POIICON_ON",MAP_CONFIG::MAP_POIICON_ON);
    settings.setValue("MAP_POITEXT_ON",MAP_CONFIG::MAP_POITEXT_ON);
    settings.endGroup();
}


void configManager::reader()
{
    QSettings settings(QCoreApplication::organizationName() ,QCoreApplication::applicationName());
    settings.setPath(QSettings::IniFormat,QSettings::UserScope,"./config/config.rc");
    settings.beginGroup("CORE");
    CONFIG_CORE::SERVICE_IP = QHostAddress(settings.value("SERVICE_IP").toString());
    CONFIG_CORE::SERVICE_PORT = settings.value("SERVICE_PORT").toInt();
    CONFIG_CORE::DB_PASSWD_PART = settings.value("PAR").toString();
    settings.endGroup();
    
    settings.beginGroup("MAP");
    MAP_CONFIG::MAP_AUTO_POSITIONING = settings.value("MAP_AUTO_POSITIONING").Bool;
    MAP_CONFIG::MAP_CONTROL_3D = settings.value("MAP_CONTROL_3D").Bool;
    MAP_CONFIG::MAP_CONTROL_SCALE = settings.value("MAP_CONTROL_SCALE").Bool;
    MAP_CONFIG::MAP_DEFAULT_LOCATE = settings.value("MAP_DEFAULT_LOCATE").toString();
    MAP_CONFIG::MAP_EARTHMODEL = settings.value("MAP_EARTHMODEL").Bool;
    MAP_CONFIG::MAP_POIICON_ON = settings.value("MAP_POIICON_ON").Bool;
    MAP_CONFIG::MAP_POITEXT_ON = settings.value("MAP_POITEXT_ON").Bool;
    settings.endGroup();
}

void configManager::config_Changed(){
    writer();
}

void configManager::getPasswd(){
    // 获取主机名
    QString hostName = QHostInfo::localHostName();
    // 获取设备类型
    QString deviceType = QSysInfo::productType();
    // 获取设备名称
    QString deviceName = QSysInfo::machineHostName();
    // 获取设备IP地址
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address())
        {
            strIpAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // 如果没有找到，则以本地IP地址为IP
    if (strIpAddress.isEmpty())
    {
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }
    // 获取设备MAC地址
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces(); // 获取所有网络接口列表
    int nCnt = nets.count();
    QString strMacAddr = "";
    for (int i = 0; i < nCnt; i++)
    {
        // 如果此网络接口被激活并且正在运行并且不是回环地址，则就是要找的Mac地址
        if (nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning) && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            strMacAddr = nets[i].hardwareAddress();
            break;
        }
    }
    // 计算CONFIG_CORE::DB_PASSWD_PART的SHA256加密值
    QString dbpart256 = QString(QCryptographicHash::hash(CONFIG_CORE::DB_PASSWD_PART.toUtf8(), QCryptographicHash::Sha256).toHex());
    // 将设备信息整合成字符串
    QString sysstr = hostName + deviceType + deviceName + strIpAddress + strMacAddr + "CSystem" + QCoreApplication::applicationVersion() + dbpart256;
    // 计算syssstr的md5值
    QByteArray aes = QCryptographicHash::hash(sysstr.toUtf8(), QCryptographicHash::Md5);
    // 将md5值转换为16进制字符串
    QString dbpasswd = aes.toHex();
    // 保存数据库密码
    CONFIG_CORE::DB_PASSWD = dbpasswd;
    // 计算一个系统特征值
    // 获取当前时间
    QDateTime current_date_time = QDateTime::currentDateTime();
    // 随机生成一个20位数的随机数
    QString random_str = QString::number(qrand() % 100000000000);
    // 计算特征值
    CONFIG_CORE::SYSTEM_FEATURE = QCryptographicHash::hash((CONFIG_CORE::DB_PASSWD + current_date_time.toString("yyyyMMddhhmmss") + random_str).toUtf8(), QCryptographicHash::Md5).toHex();
}

void configManager::makeRSA(){
    rsa rsa;
    rsa.RSAmake();
}