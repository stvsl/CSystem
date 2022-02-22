#include "encryptionconfig.h"

QString EncryptionConfig::databasePasswd_Old = "";
QString EncryptionConfig::key = "";

EncryptionConfig::EncryptionConfig(QObject *parent) : QObject{parent}
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

    // 检查二进制文件是否存在
    QFile file(QCoreApplication::applicationDirPath() + "/config/config.cfg");
    if(!file.exists()){
        // 如果不存在，则创建文件
        // 创建文件
        file.open(QIODevice::WriteOnly);
        file.close();
    }
    generatePassword();
}

QString EncryptionConfig::generatePassword()
{
    // 生成随机字符串
    // 随机种子
    QString seed = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    // 生成密码
    QString password = "";
    for(int i = 0; i < 16; i++){
        password += seed.at(qrand() % seed.length());
    }
    // 计算MD5
    QByteArray byteArray = QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Md5);
    // 转换为16进制
    QString md5 = byteArray.toHex();
    return md5;
}

// 向服务器发起顶求获取解锁密码
QString EncryptionConfig::getUnlockPassword()
{
    // 发送Https形式的GET请求
    QNetworkRequest request;
    request.setUrl(QUrl("https://" + CONFIG_CORE::SERVICE_DOMAIN + "/passwd/getpass"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // 携带token
    request.setRawHeader("Authorization", QString("sintok " + MAIN_RUN_CONFIG::SYSTEM_TOKEN).toUtf8());
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
        // 资源释放
        reply->deleteLater();
        manager->deleteLater();
        return "网络连接超时";
    }
    // 如果没有超时
    else
    {
        timer.stop();
        // 获取返回码
        code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
        // 如果返回码不是200
        if(code != "200"){
            // 资源释放
            reply->deleteLater();
            manager->deleteLater();
            return "服务器错误";
        }
        // 获取返回数据
        QByteArray data = reply->readAll();
        // 转换为json
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        // 获取json对象
        QJsonObject jsonObj = jsonDoc.object();
        // 获取密码
        QString passwd = jsonObj.value("feature").toString();
        // base64解密
        QByteArray byteArray = QByteArray::fromBase64(passwd.toUtf8());
        // AES解密
        AES aes;
        key = aes.decrypt(byteArray);
        // 资源释放
        reply->deleteLater();
        manager->deleteLater();
        return passwd;
    }
}

QString EncryptionConfig::uploadPasswordFragment(){
    // 发送POST请求
    QNetworkRequest request;
    request.setUrl(QUrl("https://" + CONFIG_CORE::SERVICE_DOMAIN + "/passwd/getpass"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // 携带token
    request.setRawHeader("Authorization", QString("sintok " + MAIN_RUN_CONFIG::SYSTEM_TOKEN).toUtf8());
    QSslConfiguration conf;
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(conf);
    // manager
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QEventLoop loop;
    QNetworkReply *reply = manager->post(request, QString("{\"feature\":\"" + key + "\"}").toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();
    QString code;
    // 如果超时
    if (!timer.isActive())
    {
        timer.stop();
        // 资源释放
        reply->deleteLater();
        manager->deleteLater();
        return "网络连接超时";
    }
    // 如果没有超时
    else
    {
        timer.stop();
        // 获取返回码
        code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
        // 如果返回码不是200
        if(code != "200"){
            // 资源释放
            reply->deleteLater();
            manager->deleteLater();
            return "服务器错误";
        }
        // 获取返回数据
        QByteArray data = reply->readAll();
        // 转换为json
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        // 获取json对象
        QJsonObject jsonObj = jsonDoc.object();
        // 获取code
        QString code = jsonObj.value("code").toString();
        // 判断是否是CX200
        if(code == "CX200"){
            // 资源释放
            reply->deleteLater();
            manager->deleteLater();
            return "CX200";
        }else{
            // 资源释放
            reply->deleteLater();
            manager->deleteLater();
            return "服务器错误";
        }
    }
}

void EncryptionConfig::read()
{
    // 读取配置文件
    QFile file(QCoreApplication::applicationDirPath() + "/config/config.cfg");
    // 打开文件
    file.open(QIODevice::ReadOnly);
    // 读取二进制数据
    QByteArray byteArray = file.readAll();
    // 关闭文件
    file.close();
    // AES解密
    AES aes;
    QByteArray byteArrayDecrypted = aes.decrypt(byteArray, key);
    // 解析成json
    QJsonDocument jsonDocument = QJsonDocument::fromJson(byteArrayDecrypted);
    // 获取json对象
    QJsonObject jsonObject = jsonDocument.object();
    // 获取数据
    databasePasswd_Old = jsonObject.value("databasePasswd").toString();
}

void EncryptionConfig::write()
{
    // 打开文件
    QFile file(QCoreApplication::applicationDirPath() + "/config/config.cfg");
    // 生成json对象
    QJsonObject jsonObject;
    jsonObject.insert("databasePasswd", databasePasswd_Old);
    // 生成json文档
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    // 转换为二进制数据
    QByteArray byteArray = jsonDocument.toJson();
    // AES加密
    AES aes;
    QByteArray byteArrayEncrypted = aes.encrypt(byteArray, key);
    // 清空数据并写入
    if(file.open(QIODevice::WriteOnly| QIODevice::Text | QFile::Truncate)){
        file.write(byteArrayEncrypted);
        file.close();
    }
}