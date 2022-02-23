#include "security.h"

Security::Security(QObject *parent) : QObject(parent)
{
}

QString Security::ping()
{
    netWorkUtils nwu;
    // 绑定信号
    connect(&nwu, SIGNAL(netError(QString)), this, SLOT(panicError(QString)));
    QString url = "/ping";
    nwu.get(url);
    // 获取返回的byte数据转换为json
    QJsonParseError jsonError;
    QJsonDocument json = QJsonDocument::fromJson(nwu.exec(), &jsonError);
    // 断开信号
    disconnect(&nwu, SIGNAL(netError(QString)), this, SLOT(panicError(QString)));
    if (jsonError.error != QJsonParseError::NoError)
    {
        return jsonError.errorString();
    }
    // 获取json中的data
    QJsonObject jsonObj = json.object();
    // 获取RSA_SERVER_PUBLIC_KEY
    CONFIG_CORE::RSA_SERVER_PUBLIC_KEY = jsonObj.value("RSA_PUBLIC").toString();
    return "CX200";
}

QString Security::pingpost()
{
    netWorkUtils nwu;
    // 绑定信号
    connect(&nwu, SIGNAL(netError(QString)), this, SLOT(panicError(QString)));
    QString url = "/ping";
    // json生成
    QJsonObject jsonObj;
    // 生成随机字符串
    MAIN_RUN_CONFIG::AES_KEY = "";
    for (int i = 0; i < 15; ++i)
    {
        int idx = QRandomGenerator::global()->generate() % (200 - 1);
        QString ch = QString(CONFIG_CORE::RSA_SERVER_PUBLIC_KEY[idx + 20]);
        MAIN_RUN_CONFIG::AES_KEY.append(ch);
    }
    // 使用服务器RSA加密aes1和特征值
    rsa rsa;
    QString aes1 = rsa.rsaPubEncrypt(MAIN_RUN_CONFIG::AES_KEY, CONFIG_CORE::RSA_SERVER_PUBLIC_KEY);
    QString feature = rsa.rsaPubEncrypt(CONFIG_CORE::SYSTEM_FEATURE, CONFIG_CORE::RSA_SERVER_PUBLIC_KEY);
    jsonObj.insert("KEY", aes1);
    jsonObj.insert("FEATURE", feature);
    jsonObj.insert("RSA", CONFIG_CORE::RSA_PUBLIC_KEY);
    // 设置将此json发送到服务器
    nwu.sendJson(jsonObj);
    nwu.post(url);
    // 获取返回的byte数据转换为json
    QJsonParseError jsonError;
    QJsonDocument json = QJsonDocument::fromJson(nwu.exec(), &jsonError);
    // 断开信号
    disconnect(&nwu, SIGNAL(netError(QString)), this, SLOT(panicError(QString)));
    if (jsonError.error != QJsonParseError::NoError)
    {
        return jsonError.errorString();
    }
    jsonObj = json.object();
    // 获取aes密钥
    QString aese = jsonObj.value("KEY").toString();
    // 解密获取aes信息
    QString aes2 = rsa.rsaPriDecrypt(aese, CONFIG_CORE::RSA_PRIVATE_KEY);
    // 拼接aes信息
    MAIN_RUN_CONFIG::AES_KEY.append(aes2);
    // 计算aes
    MAIN_RUN_CONFIG::AES_KEY = QCryptographicHash::hash(MAIN_RUN_CONFIG::AES_KEY.toUtf8(), QCryptographicHash::Md5).toHex();
    return "CX200";
}

QString Security::getToken()
{
    netWorkUtils nwu;
    // 绑定信号
    connect(&nwu, SIGNAL(netError(QString)), this, SLOT(panicError(QString)));
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
    nwu.post("/auth/getauth");
    nwu.sendJson(jsonObj);
    // 获取返回的byte数据转换为json
    QJsonParseError jsonError;
    QJsonDocument json = QJsonDocument::fromJson(nwu.exec(), &jsonError);
    // 断开信号
    disconnect(&nwu, SIGNAL(netError(QString)), this, SLOT(panicError(QString)));
    if (jsonError.error != QJsonParseError::NoError)
    {
        return jsonError.errorString();
    }
    jsonObj = json.object();
    // 获取token
    MAIN_RUN_CONFIG::SYSTEM_TOKEN = jsonObj.value("token").toString();
    // base64解码
    QByteArray data = QByteArray::fromBase64(MAIN_RUN_CONFIG::SYSTEM_TOKEN.toUtf8());
    AES aes;
    // 使用aes密码解密token
    MAIN_RUN_CONFIG::SYSTEM_TOKEN = aes.decrypt(data);
    return jsonObj.value("code").toString();
}

void Security::onnetError(QString errStr)
{
    emit netError(errStr);
}

void Security::panicError(QString errStr)
{
    // 弹出错误提示，点击确定后退出程序
    QMessageBox::critical(nullptr, "错误", "网络连接失败，请检查网络连接！ <br> 错误描述：" + errStr, QMessageBox::Ok);
    QApplication::exit(0);
}
