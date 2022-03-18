#include "nodeinterface.h"
#include "cacheManager/CacheManager.h"

NodeInterface::NodeInterface(QVector<NodeInfo> *list) : QObject()
{
    this->nodeInfoList = list;
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
    QJsonDocument jsondoc = QJsonDocument::fromJson(nwu.exec(), &jsonError);
    // 断开信号
    disconnect(&nwu, SIGNAL(netError(QString)), this, SLOT(onnetError(QString)));
    QJsonObject jsonObj = jsondoc.object();
    // 读取data
    QString data = jsonObj.value("data").toString();
    // base64解码
    QByteArray data64 = QByteArray::fromBase64(data.toUtf8());
    // AES解密
    AES aes;
    QString dedata = aes.decrypt(data64);
    // 转换为json
    jsondoc = QJsonDocument::fromJson(dedata.toUtf8());
    QVariantList list = jsondoc.toVariant().toList();
    for (int i = 0; i < list.size(); i++)
    {
        QVariantMap map = list.at(i).toMap();
        NodeInfo nodeInfo;
        nodeInfo.ip = map.value("ip").toString();
        nodeInfo.id = map.value("id").toString();
        nodeInfo.locate = map.value("locate").toString();
        nodeInfo.type = map.value("type").toInt();
        nodeInfo.belong = map.value("belong").toString();
        nodeInfo.principal = map.value("principal").toString();
        nodeInfo.installer = map.value("installer").toString();
        nodeInfo.maintainer = map.value("maintainer").toString();
        nodeInfo.dataConfig = map.value("dataconfig").toString();
        nodeInfo.aesKey = map.value("aeskeyfeature").toString();
        nodeInfo.selfInfo = map.value("selfinfo").toString();
        nodeInfo.lastUpload = map.value("lastupload").toDateTime();
        nodeInfo.selfDate = map.value("selfdate").toDateTime();
        nodeInfo.remark = map.value("remark").toString();
        nodeInfo.installDate = map.value("installdate").toDateTime();
        nodeInfo.lo = map.value("lo").toFloat();
        nodeInfo.li = map.value("li").toFloat();
        nodeInfo.gasConcentration = map.value("GasConcentration").toFloat();
        nodeInfo.temperature = map.value("Temperature").toFloat();
        nodeInfo.pH = map.value("PH").toFloat();
        nodeInfo.density = map.value("Density").toFloat();
        nodeInfo.conductivity = map.value("Conductivity").toFloat();
        nodeInfo.oxygenConcentration = map.value("OxygenConcentration").toFloat();
        nodeInfo.metalConcentration = map.value("MetalConcentration").toFloat();
        nodeInfo.SC = map.value("SC").toFloat();
        nodeInfo.FSC = map.value("FSC").toFloat();
        nodeInfo.TN = map.value("TN").toFloat();
        nodeInfo.TP = map.value("TP").toFloat();
        nodeInfo.TOC = map.value("TOC").toFloat();
        nodeInfo.BOD = map.value("BOD").toFloat();
        nodeInfo.COD = map.value("COD").toFloat();
        nodeInfo.BC = map.value("BC").toInt();
        nodeInfo.SLC = map.value("SLC").toInt();
        nodeInfo.COMID = map.value("comid").toString();
        nodeInfo.COMNAME = map.value("comname").toString();
        nodeInfo.REMARK = map.value("comremark").toString();
        nodeInfo.REGISTTIME = map.value("register").toString();
        nodeInfo.COMTYPE = map.value("comtype").toString();
        nodeInfo.STANDARD = map.value("standard").toString();
        nodeInfo.status = 0;
        this->nodeInfoList->append(nodeInfo);
    }
}
