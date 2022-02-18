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
    timer.setInterval(3000);
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
    MAIN_RUN_CONFIG::AES_KEY = "";
    qsrand(QDateTime::currentMSecsSinceEpoch());
    int idx = 0;
    for (int i = 0; i < 15; ++i)
    {
        idx = qrand() % (200 - 1);
        QString ch = QString(CONFIG_CORE::RSA_SERVER_PUBLIC_KEY[idx+20]);
        MAIN_RUN_CONFIG::AES_KEY.append(ch);
    }
    // 使用服务器RSA加密aes1和特征值
    rsa rsa;
    QString aes1 = rsa.rsaPubEncrypt(MAIN_RUN_CONFIG::AES_KEY, CONFIG_CORE::RSA_SERVER_PUBLIC_KEY);
    QString feature = rsa.rsaPubEncrypt(CONFIG_CORE::SYSTEM_FEATURE, CONFIG_CORE::RSA_SERVER_PUBLIC_KEY);
    // json生成
    QJsonObject jsonObj;
    jsonObj.insert("KEY", aes1);
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
            // 获取aes密钥
            QString aese = jsonObj.value("KEY").toString();
            // 解密获取aes信息
            QString aes2 = rsa.rsaPriDecrypt(aese, CONFIG_CORE::RSA_PRIVATE_KEY);
            // 拼接aes信息
            MAIN_RUN_CONFIG::AES_KEY.append(aes2);
            // 计算aes
            MAIN_RUN_CONFIG::AES_KEY = QCryptographicHash::hash(MAIN_RUN_CONFIG::AES_KEY.toUtf8(), QCryptographicHash::Md5).toHex();
        }
    }
    // 释放资源
    reply->deleteLater();
    manager->deleteLater();
    return code;
}

QString netWorkUtils::getToken()
{
   // 发送https的post请求
    QNetworkRequest request;
    request.setUrl(QUrl("https://" + CONFIG_CORE::SERVICE_DOMAIN + "/auth/getauth"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QSslConfiguration conf;
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(conf);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 计算密码特征
    QString passwdsha256 = QCryptographicHash::hash(LOGIN_CONFIG::PASSWD.toUtf8(), QCryptographicHash::Sha256).toHex();
    // 加密
    rsa rsa;
    QString feature = rsa.rsaPubEncrypt(CONFIG_CORE::SYSTEM_FEATURE, CONFIG_CORE::RSA_SERVER_PUBLIC_KEY);
    QString id = rsa.rsaPubEncrypt(LOGIN_CONFIG::ID, CONFIG_CORE::RSA_SERVER_PUBLIC_KEY);
    QString passwd = rsa.rsaPubEncrypt(passwdsha256, CONFIG_CORE::RSA_SERVER_PUBLIC_KEY);
    // json生成
    QJsonObject jsonObj;
    jsonObj.insert("feature", feature);
    jsonObj.insert("id", id);
    jsonObj.insert("passwd", passwd);
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
            // 获取token
            MAIN_RUN_CONFIG::SYSTEM_TOKEN = jsonObj.value("token").toString();
            // base64解码
            QByteArray data = QByteArray::fromBase64(MAIN_RUN_CONFIG::SYSTEM_TOKEN.toUtf8());
            AES aes;
            // 使用aes密码解密token
            MAIN_RUN_CONFIG::SYSTEM_TOKEN =  aes.decrypt(data);
        }
    }
    // 释放资源
    reply->deleteLater();
    manager->deleteLater();
    return code;
}

QString netWorkUtils::updatePasswdPart()
{
   
}
