#ifndef NETWORKUTILS_H
#define NETWORKUTILS_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "main.h"
#include <QSslConfiguration>
#include "RSA/rsa.h"
#include "AES/aes.h"

class netWorkUtils : public QObject
{
    Q_OBJECT
public:
    explicit netWorkUtils(QObject *parent = nullptr);

signals:
    void netError(QString errorStr);

private:
    // 连接模式
    // 0: IP模式
    // 1: 域名模式
    static int CONNECTMODE;

    // 超时时间设置
    static int TIMEOUT;

    // HTTPS模式
    static bool HTTPS;

    // 是否携带token
    static bool takeToken;

    // 是否需要认证
    static bool SSLVERIFY;

    // 要发送的json数据
    QByteArray jsondata;

    // 请求类型
    // 0: GET
    // 1: POST
    int requestType;

    // 保存请求头
    QMap<QString, QString> headers;

    // 访问目标
    QString target;

public:
    // 切换全局连接模式
    QString CONNECT_MODE();

    // 发送get请求
    void get(QString url);

    // 发送post请求
    void post(QString url);

    // 是否携带token(默认不携带)
    void setToken();

    // 设置请求头
    void setHeader(QString header, QString key);

    // 设置全局超时
    void setGlobalTimeout(int timeout);

    // 关闭全局验证
    void closeVerify();

    // 全局开启HTTPS
    static void openHttpsGlobal();

    // 发送json
    QString sendJson(QJsonObject jsonObj);

    // 执行访问
    QByteArray exec();

    // 网络重连函数
    void reConnect();

private:
    QTimer timer;

    QByteArray getRequest();

    QByteArray postRequest();
};

#endif // NETWORKUTILS_H
