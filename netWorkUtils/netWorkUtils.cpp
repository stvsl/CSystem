#include "netWorkUtils.h"
#include "configManager/configmanager.h"

netWorkUtils::netWorkUtils(QObject *parent) : QObject(parent)
{
    // 初始化SSL配置
    QSslConfiguration sslConf = QSslConfiguration::defaultConfiguration();
    sslConf.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConf.setProtocol(QSsl::TlsV1SslV3);
    QSslConfiguration::setDefaultConfiguration(sslConf);
    // 初始化计时器
    // 设置超时时间3秒
    timer.setInterval(5000);
    timer.setSingleShot(true);
}

QString netWorkUtils::ping()
{
    //发送Https形式的的GET请求
    QNetworkRequest request;
    request.setUrl(QUrl("https://" + CONFIG_CORE::SERVICE_DOMAIN + "/ping"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QSslConfiguration conf;
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(conf);
    // manager
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QEventLoop loop;
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();
    QString code;
    // 如果超时
    if (!timer.isActive())
    {
        timer.stop();
        return "网络连接超时";
    }
    // 如果没有超时
    else
    {
        // 解析json
        QJsonParseError jsonError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll(), &jsonError);
        if (jsonError.error != QJsonParseError::NoError)
        {
            return "数据通信异常";
        }
        QJsonObject jsonObj = jsonDoc.object();
        code = jsonObj.value("code").toString();
        // 如果code不为CX200
        if (code != "CX200")
        {
            qDebug() << "ping：code: " << code << "message" << jsonObj.value("message").toString();
        }
        else
        {
            // 获取服务器RSA
            CONFIG_CORE::RSA_SERVER_PUBLIC_KEY = jsonObj.value("RSA_PUBLIC").toString();
        }
    }
    // 释放资源
    reply->deleteLater();
    manager->deleteLater();
    return code;
}

QString netWorkUtils::pingpost()
{
    // 发送Https形式的的POST请求
    QNetworkRequest request;
    request.setUrl(QUrl("https://" + CONFIG_CORE::SERVICE_DOMAIN + "/ping"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QSslConfiguration conf;
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(conf);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 使用服务器RSA公钥作为数据种子生成随机字符串
    MAIN_RUN_CONFIG::MD5_KEY = "";
    qsrand(QDateTime::currentMSecsSinceEpoch());
    int idx = 0;
    for (int i = 0; i < 15; ++i)
    {
        idx = qrand() % (256 - 1);
        QString ch = QString(CONFIG_CORE::RSA_SERVER_PUBLIC_KEY[idx]);
        MAIN_RUN_CONFIG::MD5_KEY.append(ch);
    }
    // 使用服务器RSA加密MD51和特征值
    rsa rsa;
    QString md51 = rsa.rsaPubEncrypt(MAIN_RUN_CONFIG::MD5_KEY, CONFIG_CORE::RSA_SERVER_PUBLIC_KEY);
    QString feature = rsa.rsaPubEncrypt(CONFIG_CORE::SYSTEM_FEATURE, CONFIG_CORE::RSA_SERVER_PUBLIC_KEY);
    // json生成
    QJsonObject jsonObj;
    jsonObj.insert("KEY", md51);
    jsonObj.insert("FEATURE", feature);
    jsonObj.insert("RSA", CONFIG_CORE::RSA_PUBLIC_KEY);
    QJsonDocument jsonDoc(jsonObj);
    QEventLoop loop;
    QNetworkReply *reply = manager->post(request, QJsonDocument(jsonObj).toJson());
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();
    QString code;
    // 如果超时
    if (!timer.isActive())
    {
        timer.stop();
        return "网络连接超时";
    }
    // 如果没有超时
    else
    {
        // 解析json
        QJsonParseError jsonError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll(), &jsonError);
        if (jsonError.error != QJsonParseError::NoError)
        {
            // 释放资源
            reply->deleteLater();
            manager->deleteLater();
            return "数据通信异常";
        }
        QJsonObject jsonObj = jsonDoc.object();
        code = jsonObj.value("code").toString();
        // 如果code不为CX200
        if (code != "CX200")
        {
            qDebug() << "ping：code: " << code << "message" << jsonObj.value("message").toString();
        }
        else
        {
            // 获取MD5密钥
            QString md5e = jsonObj.value("KEY").toString();
            // 解密获取md5信息
            QString md52 = rsa.rsaPriDecrypt(md5e, CONFIG_CORE::RSA_PRIVATE_KEY);
            // 拼接MD5信息
            MAIN_RUN_CONFIG::MD5_KEY.append(md52);
            // 计算MD5
            MAIN_RUN_CONFIG::MD5_KEY = QCryptographicHash::hash(MAIN_RUN_CONFIG::MD5_KEY.toUtf8(), QCryptographicHash::Md5).toHex();
        }
    }
             qDebug() << MAIN_RUN_CONFIG::MD5_KEY;
   
    // 释放资源
    reply->deleteLater();
    manager->deleteLater();
    return code;
}

void netWorkUtils::getToken()
{
    // json对象
    QJsonObject json;
    json.insert("id", LOGIN_CONFIG::ID);
    json.insert("fragment", LOGIN_CONFIG::PASSWD);
    QJsonDocument document;
    document.setObject(json);
    // 获取json字符串
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString jsonStr(byteArray);
    //发送请求
    QNetworkRequest request;
    request.setUrl(QUrl("https://stvsljl.com/auth/getauth"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // https支持
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(conf);
    // manager
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->post(request, jsonStr.toUtf8());
    // 发送请求
    connect(reply, &QNetworkReply::finished, this, [=]()
            {
        // 获取返回的数据
        QByteArray data = reply->readAll();
        // 解析json的数据
        QJsonParseError jsonError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data,&jsonError);
        // 查看code信息
        QJsonObject jsonObject = jsonDocument.object();
        QString code = jsonObject.value("code").toString();
        if (code != "CX200"){
            emit netError(jsonObject.value("message").toString());
            return;
        }
        // 获取token
        QString token = jsonObject.value("token").toString();
        // 存储token
        MAIN_RUN_CONFIG::SYSTEM_TOKEN = token; });
    reply->deleteLater();
    manager->deleteLater();
}

void netWorkUtils::updatePasswdPart()
{
    // 向服务器发送服务器密码json数据
    QJsonObject json;
    json.insert("fragment", CONFIG_CORE::DB_PASSWD_PART);
    // 发送
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();
    QString str = QString(data);
    // 以POST请求发送到stvsljl.com//passwd/getpass
    QNetworkRequest request;
    request.setUrl(QUrl("http://stvsljl.com/passwd/getpass"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // 在头部添加token
    QString token = "sintok " + MAIN_RUN_CONFIG::SYSTEM_TOKEN;
    request.setRawHeader("Authorization", token.toUtf8());
    // manager
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 发送
    QNetworkReply *reply = manager->post(request, data);
    // 接收
    connect(reply, &QNetworkReply::finished, [=]()
            {
        // 获取服务器返回的数据
        QByteArray data = reply->readAll();
        // 转换为json
        QJsonDocument doc = QJsonDocument::fromJson(data);
        // 获取json对象
        QJsonObject json = doc.object();
        //查看code信息
        QString code = json.value("code").toString();
        if (code != "CX200"){
            emit netError(json.value("message").toString());
        } });
    // 关闭连接
    reply->close();
    // 回收内存
    delete manager;
    delete reply;
}
