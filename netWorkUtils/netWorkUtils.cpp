#include "netWorkUtils.h"
#include "configManager/configmanager.h"

netWorkUtils::netWorkUtils(QObject *parent) : QObject(parent)
{
}

QString netWorkUtils::ping()
{
    //发送GET请求
    QNetworkRequest request;
    request.setUrl(QUrl("http://stvsljl.com/ping"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // manager
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(request);
    // 等待响应
    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();
    // 获取响应内容
    QByteArray response = reply->readAll();
    // 获取响应状态码
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    reply->close();
    // 判断响应状态码
    // 完成后释放内存
    reply->deleteLater();
    manager->deleteLater();
    if (statusCode == 200)
    {
        // 解析响应内容
        QJsonParseError jsonError;
        QJsonDocument json = QJsonDocument::fromJson(response, &jsonError);
        // 获取code字段
        QJsonObject jsonObject = json.object();
        QString code = jsonObject.value("code").toString();
        // 返回code
        return code;
    }
    else
    {
        // 返回错误信息
        return QString("Error: %1").arg(statusCode);
    }
}

void netWorkUtils::getToken(QString id, QString passwd)
{
    // json对象
    QJsonObject json;
    json.insert("id", id);
    json.insert("fragment", passwd);
    QJsonDocument document;
    document.setObject(json);
    // 获取json字符串
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString jsonStr(byteArray);
    //发送请求
    QNetworkRequest request;
    request.setUrl(QUrl("http://stvsljl.com/auth/getauth"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
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
        reply->close();
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
