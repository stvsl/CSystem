#include "userinterface.h"

UserInterface::UserInterface()
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

QString UserInterface::getUserInformation()
{
    // 发送Https形式的的GET请求
    QNetworkRequest request;
    request.setUrl(QUrl("https://" + CONFIG_CORE::SERVICE_DOMAIN + "/my/account"));
    // 添加header
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // 在请求头添加token信息
    request.setRawHeader("Authorization", QString("sintok " + MAIN_RUN_CONFIG::SYSTEM_TOKEN).toUtf8());
    QSslConfiguration conf;
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(conf);
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
        manager->deleteLater();
        reply->deleteLater();
        return "网络连接超时";
    }
    else
    {
        // 读取json
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
            qDebug() << "getUserInformation：code: " << code << "message" << jsonObj.value("message").toString();
            // 释放资源
            reply->deleteLater();
            manager->deleteLater();
            return jsonObj.value("message").toString();
        }
        else
        {
            // 读取data
            QString data = jsonObj.value("data").toString();
            // base64解码
            QByteArray data64 = QByteArray::fromBase64(data.toUtf8());
            // AES解密
            AES aes;
            QString dedata = aes.decrypt(data64);
            // 释放资源
            reply->deleteLater();
            manager->deleteLater();
            // 返回解密后的数据
            return dedata;
        }
    }
}