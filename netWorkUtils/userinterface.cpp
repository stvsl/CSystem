#include "userinterface.h"

UserInterface::UserInterface()
{
}

QString UserInterface::getUserInformation()
{
    // 发送Https形式的的GET请求
    netWorkUtils nwu;
    connect(&nwu, SIGNAL(netError(QString)), this, SLOT(onnetError(QString)));
    nwu.get("/my/account");
    nwu.setToken();
    // 获取返回的byte数据转换为json
    QJsonParseError jsonError;
    QJsonDocument json = QJsonDocument::fromJson(nwu.exec(), &jsonError);
    // 断开信号
    disconnect(&nwu, SIGNAL(netError(QString)), this, SLOT(onnetError(QString)));
    QJsonObject jsonObj = json.object();
    // 读取data
    QString data = jsonObj.value("data").toString();
    // base64解码
    QByteArray data64 = QByteArray::fromBase64(data.toUtf8());
    // AES解密
    AES aes;
    QString dedata = aes.decrypt(data64);
    // 转换为json
    QJsonDocument json = QJsonDocument::fromJson(dedata);
    jsonObj = json.object();
    LOGIN_CONFIG::ID = jsonObj.value("id").toString();
    ID_CARD::TYPE = jsonObj.value("type").toInt();
    ID_CARD::USERID = jsonObj.value("userid").toString();
    ID_CARD::USERLOCATE = jsonObj.value("userlocate").toString();
    ID_CARD::USERNAME = jsonObj.value("username").toString();
    ID_CARD::TEL = jsonObj.value("tel").toString();
    ID_CARD::ORGANIZATION = jsonObj.value("organization").toString();
    // 返回解密后的数据
    return dedata;
}

void UserInterface::onnetError(QString error)
{
    emit netError(error);
}
