#include "netWorkUtils.h"
#include "configManager/configmanager.h"

int netWorkUtils::CONNECTMODE = 1;
int netWorkUtils::TIMEOUT = 5000;
bool netWorkUtils::HTTPS = false;
bool netWorkUtils::SSLVERIFY = true;

netWorkUtils::netWorkUtils(QObject *parent) : QObject(parent)
{
    // 判断是否开启HTTPS
    if (netWorkUtils::HTTPS)
    {
        // 初始化SSL
        QSslConfiguration sslConfiguration;
        if (!netWorkUtils::SSLVERIFY)
        {
            sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
        }
        sslConfiguration.setProtocol(QSsl::TlsV1SslV3);
        QSslConfiguration::setDefaultConfiguration(sslConfiguration);
    }
    // 初始化计时器
    timer->setInterval(netWorkUtils::TIMEOUT);
    timer->setSingleShot(true);
}

QString netWorkUtils::CONNECT_MODE()
{
    if (netWorkUtils::CONNECTMODE == 0)
    {
        netWorkUtils::CONNECTMODE = 1;
        return "域名模式";
    }
    else
    {
        return "IP模式";
    }
}

QString netWorkUtils::get(QString url)
{
    // 发送get请求
    // 判断模式
    QString aim;
    if (netWorkUtils::CONNECTMODE == 0)
    {
        qDebug() << "状态异常，当前模式不支持get请求,请检查";
        return "状态异常，当前模式不支持get请求,请检查";
    }
    else
    {
        aim = CONFIG_CORE::SERVICE_DOMAIN + url;
    }
    // 判断是否开启HTTPS
    if (netWorkUtils::HTTPS)
    {
        request = new QNetworkRequest(QUrl("https://" + aim));
    }
    else
    {
        request = new QNetworkRequest(QUrl("http://" + aim));
    }
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    requestType = 0;
    return "OK";
}

QString netWorkUtils::post(QString url)
{
    // 发送post请求
    // 判断模式
    QString aim;
    if (netWorkUtils::CONNECTMODE == 0)
    {
        qDebug() << "状态异常，当前模式不支持get请求,请检查";
        return "状态异常，当前模式不支持get请求,请检查";
    }
    else
    {
        aim = CONFIG_CORE::SERVICE_DOMAIN + url;
    }
    // 判断是否开启HTTPS
    if (netWorkUtils::HTTPS)
    {
        request = new QNetworkRequest(QUrl("https://" + aim));
    }
    else
    {
        request = new QNetworkRequest(QUrl("http://" + aim));
    }
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    requestType = 1;
    return "OK";
}

void netWorkUtils::setToken()
{
    // 设置token
    QString token = MAIN_RUN_CONFIG::SYSTEM_TOKEN;
    if (token != "")
    {
        request->setRawHeader("Authorization", ("sintok " + token).toUtf8());
    }
}

void netWorkUtils::setHeader(QString header, QString key)
{
    // 设置header
    request->setRawHeader(header.toUtf8(), key.toUtf8());
}

void netWorkUtils::setTimeout(int timeout)
{
    timer->setInterval(timeout);
}

void netWorkUtils::setGlobalTimeout(int timeout)
{
    netWorkUtils::TIMEOUT = timeout;
    timer->setInterval(timeout);
}

void netWorkUtils::closeVerify()
{
    // 关闭SSL验证
    QSslConfiguration sslConfiguration;
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfiguration.setProtocol(QSsl::TlsV1SslV3);
    QSslConfiguration::setDefaultConfiguration(sslConfiguration);
    SSLVERIFY = false;
}

void netWorkUtils::openHttpsGlobal()
{
    // 开启HTTPS
    netWorkUtils::HTTPS = true;
}

QByteArray netWorkUtils::exec()
{
    // 执行请求
    if (requestType == 0)
    {
        reply = manager->get(*request);
    }
    else
    {
        reply = manager->post(*request, QJsonDocument(jsonObj).toJson());
    }
    // 事件循环
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    connect(timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer->start();
    loop.exec();
    // 如果超时
    if (timer->isActive())
    {
        emit netError(QString("网络超时"));
        timer->stop();
        reply->abort();
        reply->deleteLater();
        return "超时";
    }
    // 如果请求失败
    if (reply->error() != QNetworkReply::NoError)
    {
        emit netError(reply->errorString());
        reply->deleteLater();
        return "请求失败";
    }
    // 解析json
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError)
    {
        reply->deleteLater();
        emit netError(jsonError.errorString());
        return "解析失败";
    }
    reply->deleteLater();
    QJsonObject jsonObj = jsonDoc.object();
    QString code = jsonObj.value("code").toString();
    // 如果code不为CX200
    if (code != "CX200")
    {
        emit netError(code);
        return "请求失败";
    }
    // 返回json
    return jsonDoc.toJson();
}

void netWorkUtils::deleteLater()
{
    reply->deleteLater();
    timer->deleteLater();
    manager->deleteLater();
    delete request;
    QObject::deleteLater();
}