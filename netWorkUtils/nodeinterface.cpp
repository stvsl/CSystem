#include "nodeinterface.h"

NodeInterface::NodeInterface() : QObject()
{
}

void NodeInterface::getNodeInfo()
{
    netWorkUtils nwu;
    connect(&nwu, SIGNAL(netError(QString)), this, SLOT(onnetError(QString)));
    nwu.get("/node/info");
    nwu.setToken();
    nwu.addQuery("StartTime", "-72h");
    nwu.addQuery("EndTime", "-0h");
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
    json = QJsonDocument::fromJson(dedata.toUtf8());
    jsonObj = json.object();
}