#include "netWorkUtils.h"
#include "configManager/configmanager.h"

int netWorkUtils::CONNECTMODE = 1;
int netWorkUtils::TIMEOUT = 5000;
bool netWorkUtils::HTTPS = false;
bool netWorkUtils::SSLVERIFY = true;
bool netWorkUtils::takeToken = false;

netWorkUtils::netWorkUtils(QObject *parent) : QObject(parent)
{
    // 设置超时时间
    timer.setInterval(TIMEOUT);
    // 设置只执行一次
    timer.setSingleShot(true);
    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    // 导入证书
    QList<QSslCertificate> certList = QSslCertificate::fromPath("./cert/server.crt");
    // 设置
    sslConfig.setCaCertificates(certList);
    // 判断是否认证
    if (SSLVERIFY)
    {
        sslConfig.setPeerVerifyMode(QSslSocket::VerifyPeer);
    }
    else
    {
        sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    }
    sslConfig.setProtocol(QSsl::TlsV1SslV3);
    // 保存到默认
    QSslConfiguration::setDefaultConfiguration(sslConfig);
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

void netWorkUtils::get(QString url)
{
    // 设置请求类型
    requestType = 0;
    target = url;
}

void netWorkUtils::post(QString url)
{
    // 设置请求类型
    requestType = 1;
    target = url;
}

void netWorkUtils::setToken()
{
    takeToken = true;
}

void netWorkUtils::setHeader(QString header, QString key)
{
    // 向headers内添加
    headers.insert(header, key);
}

void netWorkUtils::setGlobalTimeout(int timeout)
{
    netWorkUtils::TIMEOUT = timeout;
    timer.setInterval(timeout);
}

void netWorkUtils::closeVerify()
{
    // 关闭SSL验证
    SSLVERIFY = false;
}

void netWorkUtils::openHttpsGlobal()
{
    // 开启HTTPS
    netWorkUtils::HTTPS = true;
}

QByteArray netWorkUtils::exec()
{
    QByteArray tmp;
    // 判断连接模式
    if (netWorkUtils::CONNECTMODE == 0)
    {
        return "模式错误，当前状态不支持";
    }
    else
    {
        // 拼接目标
        if (!netWorkUtils::HTTPS)
        {
            target = "http://" + CONFIG_CORE::SERVICE_DOMAIN + target;
        }
        else
        {
            target = "https://" + CONFIG_CORE::SERVICE_DOMAIN + target;
        }
        // 判断请求类型
        if (requestType == 0)
        {
            // 发送get请求
            tmp = getRequest();
        }
        else if (requestType == 1)
        {
            // 发送post请求
            tmp = postRequest();
        }
    }
    return tmp;
}

QByteArray netWorkUtils::getRequest()
{
    // 发送GET请求
    QNetworkRequest request;
    request.setUrl(QUrl(target));
    // 判断是否开启HTTPS
    if (netWorkUtils::HTTPS)
    {
        // 开启HTTPS
        // 创建配置
        QSslConfiguration config = QSslConfiguration::defaultConfiguration();
        // 开启SSL验证
        if (SSLVERIFY)
        {
            config.setPeerVerifyMode(QSslSocket::VerifyPeer);
        }
        else
        {
            config.setPeerVerifyMode(QSslSocket::VerifyNone);
        }
        // 设置配置
        request.setSslConfiguration(config);
    }
    // 设置默认请求头
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // 判断是否需要token
    if (takeToken)
    {
        // 添加token
        request.setRawHeader("Authorization", QString("sintok " + MAIN_RUN_CONFIG::SYSTEM_TOKEN).toUtf8());
    }
    // 判断是否有自定义请求头
    if (headers.size() > 0)
    {
        // 遍历headers
        for (auto it = headers.begin(); it != headers.end(); it++)
        {
            // 添加请求头
            request.setRawHeader(it.key().toUtf8(), it.value().toUtf8());
        }
    }
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QEventLoop loop;
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();
    // 如果超时
    if (!timer.isActive())
    {
        emit netError(QString("网络超时"));
        timer.stop();
        reply->deleteLater();
        manager->deleteLater();
        return "超时";
    }
    // 如果请求失败
    if (reply->error() != QNetworkReply::NoError)
    {
        emit netError(reply->errorString());
        reply->deleteLater();
        manager->deleteLater();
        return ("请求失败" + reply->errorString().toUtf8());
    }
    // 解析json
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll(), &jsonError);
    reply->deleteLater();
    manager->deleteLater();
    if (jsonError.error != QJsonParseError::NoError)
    {
        emit netError(jsonError.errorString());
        return "解析失败";
    }
    QJsonObject jsonObj = jsonDoc.object();
    QString code = jsonObj.value("code").toString();
    // 如果code不为CX200
    if (code != "CX200")
    {
        emit netError(code);
        return "请求内容错误";
    }
    // 返回json
    return jsonDoc.toJson();
}

QByteArray netWorkUtils::postRequest()
{
    // 发送post请求
    QNetworkRequest request;
    // 判断是否开启HTTPS
    if (netWorkUtils::HTTPS)
    {
        // 开启HTTPS
        // 创建配置
        QSslConfiguration config = QSslConfiguration::defaultConfiguration();
        // 开启SSL验证
        if (SSLVERIFY)
        {
            config.setPeerVerifyMode(QSslSocket::VerifyPeer);
        }
        else
        {
            config.setPeerVerifyMode(QSslSocket::VerifyNone);
        }
        // 设置配置
        request.setSslConfiguration(config);
    }
    // 设置默认请求头
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // 判断是否需要token
    if (takeToken)
    {
        // 添加token
        request.setRawHeader("Authorization", QString("sintok " + MAIN_RUN_CONFIG::SYSTEM_TOKEN).toUtf8());
    }
    // 判断是否有自定义请求头
    if (headers.size() > 0)
    {
        // 遍历headers
        for (auto it = headers.begin(); it != headers.end(); it++)
        {
            // 添加请求头
            request.setRawHeader(it.key().toUtf8(), it.value().toUtf8());
        }
    }
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QEventLoop loop;
    QNetworkReply *reply = manager->post(request, QJsonDocument(jsonObj).toJson());
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();
    // 如果超时
    if (!timer.isActive())
    {
        emit netError(QString("网络超时"));
        timer.stop();
        reply->abort();
        reply->deleteLater();
        return "超时";
    }
    // 如果请求失败
    if (reply->error() != QNetworkReply::NoError)
    {
        emit netError(reply->errorString());
        reply->deleteLater();
        return ("请求失败" + reply->errorString().toUtf8());
    }
    // 解析json
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll(), &jsonError);
    reply->deleteLater();
    if (jsonError.error != QJsonParseError::NoError)
    {
        emit netError(jsonError.errorString());
        return "解析失败";
    }
    QJsonObject jsonObj = jsonDoc.object();
    QString code = jsonObj.value("code").toString();
    // 如果code不为CX200
    if (code != "CX200")
    {
        emit netError(code);
        return "请求内容错误";
    }
    // 返回json
    return jsonDoc.toJson();
}
