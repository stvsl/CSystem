#include "nodeinterface.h"
#include "cacheManager/CacheManager.h"

NodeInterface::NodeInterface() : QObject()
{
}

QVector<NodeInfo> *NodeInterface::getNodeInfo()
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
    if (data == "")
    {
        emit netError("服务器返回为null");
        qDebug() << "服务器返回为null";
        return nullptr;
    }
    // base64解码
    QByteArray data64 = QByteArray::fromBase64(data.toUtf8());
    // AES解密
    AES aes;
    QString dedata = aes.decrypt(data64);
    // 转换为json
    jsondoc = QJsonDocument::fromJson(dedata.toUtf8());
    QVariantList list = jsondoc.toVariant().toList();
    // 最终数据储存
    QVector<NodeInfo> *nodeInfoList = new QVector<NodeInfo>();
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
        nodeInfoList->append(nodeInfo);
    }
    return nodeInfoList;
}

QVector<NodeData> *NodeInterface::getNodeData()
{
    netWorkUtils nwu;
    connect(&nwu, SIGNAL(netError(QString)), this, SLOT(onnetError(QString)));
    nwu.get("/node/professional");
    nwu.setToken();
    QJsonParseError jsonError;
    QJsonDocument jsondoc = QJsonDocument::fromJson(nwu.exec(), &jsonError);
    // 断开信号
    disconnect(&nwu, SIGNAL(netError(QString)), this, SLOT(onnetError(QString)));
    QJsonObject jsonObj = jsondoc.object();
    // 读取data
    QString data = jsonObj.value("data").toString();
    if (data == "")
    {
        emit netError("服务器返回为null");
        qDebug() << "服务器返回为null";
        return nullptr;
    }
    // base64解码
    QByteArray data64 = QByteArray::fromBase64(data.toUtf8());
    // AES解密
    AES aes;
    QString dedata = aes.decrypt(data64);
    // 转换为json
    jsondoc = QJsonDocument::fromJson(dedata.toUtf8());
    // 解析json列表
    QVariantList list = jsondoc.toVariant().toList();
    // 最终数据存储
    QVector<NodeData> *nodeDataList = new QVector<NodeData>();

    // 最终数据存储
    for (int i = 0; i < list.size(); i++)
    {
        QVariantMap map = list.at(i).toMap();
        NodeData nodeData;
        nodeData.id = map.value("id").toString();
        nodeData.Community = map.value("community").toString();
        nodeData.ComId = map.value("comId").toString();
        nodeData.Time = map.value("time").toString();
        nodeData.Status = map.value("status").toInt();
        nodeData.PhDirectHigh = map.value("phdirecthigh").toFloat();
        nodeData.PhDirectLow = map.value("phdirectlow").toFloat();
        nodeData.PhIndirectHigh = map.value("phindirecthigh").toFloat();
        nodeData.PhIndirectLow = map.value("phindirectlow").toFloat();
        nodeData.CODDirect = map.value("coddirect").toFloat();
        nodeData.CODIndirect = map.value("codindirect").toFloat();
        nodeData.TPDirect = map.value("tpdirect").toFloat();
        nodeData.TPIndirect = map.value("tpindirect").toFloat();
        nodeData.TNDirect = map.value("tndirect").toFloat();
        nodeData.IPIndirect = map.value("ipindirect").toFloat();
        nodeData.ANDirect = map.value("andirect").toFloat();
        nodeData.ANINDirect = map.value("anindirect").toFloat();
        nodeData.OCCDirect = map.value("occdirect").toFloat();
        nodeData.OCCIndirect = map.value("occindirect").toFloat();
        nodeData.FSCDirectT = map.value("fscdirectt").toFloat();
        nodeData.FSCIndirectT = map.value("fscindirectt").toFloat();
        nodeData.FSCDirectO = map.value("fscdirecto").toFloat();
        nodeData.FSCIndirectO = map.value("fscindirecto").toFloat();
        nodeData.SADirect = map.value("sadirect").toFloat();
        nodeData.SAIndirect = map.value("saindirect").toFloat();
        nodeData.FDirect = map.value("fdirect").toFloat();
        nodeData.FIndirect = map.value("findirect").toFloat();
        nodeData.Cu = map.value("cu").toFloat();
        nodeData.Zn = map.value("zn").toFloat();
        nodeData.Sn = map.value("sn").toFloat();
        nodeData.Sb = map.value("sb").toFloat();
        nodeData.Hg = map.value("hg").toFloat();
        nodeData.Cd = map.value("cd").toFloat();
        nodeData.Pb = map.value("pb").toFloat();
        nodeData.As = map.value("as").toFloat();
        nodeData.Cr6 = map.value("cr6").toFloat();
        nodeData.Gc = map.value("gc").toFloat();
        nodeData.Density = map.value("density").toFloat();
        nodeData.COLORIndirect = map.value("colorindirect").toFloat();
        nodeData.AFDirect = map.value("afdirect").toFloat();
        nodeData.AFINDirect = map.value("afindirect").toFloat();
        nodeData.CLDirect = map.value("cldirect").toFloat();
        nodeData.CLIndirect = map.value("clindirect").toFloat();
        nodeData.PINDirect = map.value("pindirect").toFloat();
        nodeData.Cr = map.value("cr").toFloat();
        nodeData.Conductivity = map.value("conductivity").toFloat();
        nodeData.Mc = map.value("mc").toFloat();
        nodeData.Sc = map.value("sc").toFloat();
        nodeData.Toc = map.value("toc").toFloat();
        nodeData.BOD5Direct = map.value("bod5direct").toFloat();
        nodeData.BOD5Indirect = map.value("bod5indirect").toFloat();
        nodeData.BOD = map.value("bod").toFloat();
        nodeData.PDirect = map.value("pdirect").toFloat();
        nodeData.BC = map.value("bc").toFloat();
        nodeData.SLC = map.value("slc").toFloat();
        nodeData.COLORDirect = map.value("colordirect").toFloat();
        nodeData.Ton = map.value("ton").toFloat();
        nodeDataList->append(nodeData);
    }
    return nodeDataList;
}

QVector<InfluxData> *NodeInterface::getNodeInfluxData(QString startTime, QString endTime)
{
    netWorkUtils nwu;
    connect(&nwu, SIGNAL(netError(QString)), this, SLOT(onnetError(QString)));
    nwu.get("/node/alldatainfo");
    nwu.setToken();
    nwu.addQuery("StartTime", startTime);
    nwu.addQuery("EndTime", endTime);
    // 获取返回的byte数据转换为json
    QJsonParseError jsonError;
    QJsonDocument jsondoc = QJsonDocument::fromJson(nwu.exec(), &jsonError);
    // 断开信号
    disconnect(&nwu, SIGNAL(netError(QString)), this, SLOT(onnetError(QString)));
    QJsonObject jsonObj = jsondoc.object();
    // 读取data
    QString data = jsonObj.value("data").toString();
    if (data == "")
    {
        emit netError("服务器返回为null");
        qDebug() << "服务器返回为null";
        return nullptr;
    }
    // base64解码
    QByteArray data64 = QByteArray::fromBase64(data.toUtf8());
    // AES解密
    AES aes;
    QString dedata = aes.decrypt(data64);
    // 转换为json
    jsondoc = QJsonDocument::fromJson(dedata.toUtf8());
    QVariantList list = jsondoc.toVariant().toList();
    // 最终数据储存
    QVector<InfluxData> *influxList = new QVector<InfluxData>();
    for (int i = 0; i < list.size(); i++)
    {
        QVariantMap map = list.at(i).toMap();
        InfluxData nodeInfo;
        nodeInfo.id = map.value("id").toString();
        nodeInfo.time = map.value("Time").toString();
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
        influxList->append(nodeInfo);
    }
    // 快速排序
    qSort(influxList->begin(), influxList->end(), [](const InfluxData &a, const InfluxData &b)
          { return a.time < b.time; });
    // 逆置
    std::reverse(influxList->begin(), influxList->end());
    return influxList;
}

QVector<ProData> *NodeInterface::getNodeProData(QString startTime, QString endTime)
{
    netWorkUtils nwu;
    connect(&nwu, SIGNAL(netError(QString)), this, SLOT(onnetError(QString)));
    nwu.get("/node/allpsubinfo");
    nwu.setToken();
    nwu.addQuery("StartTime", startTime);
    nwu.addQuery("EndTime", endTime);
    // 获取返回的byte数据转换为json
    QJsonParseError jsonError;
    QJsonDocument jsondoc = QJsonDocument::fromJson(nwu.exec(), &jsonError);
    // 断开信号
    disconnect(&nwu, SIGNAL(netError(QString)), this, SLOT(onnetError(QString)));
    QJsonObject jsonObj = jsondoc.object();
    // 读取data
    QString data = jsonObj.value("data").toString();
    if (data == "")
    {
        emit netError("服务器返回为null");
        qDebug() << "服务器返回为null";
        return nullptr;
    }
    // base64解码
    QByteArray data64 = QByteArray::fromBase64(data.toUtf8());
    // AES解密
    AES aes;
    QString dedata = aes.decrypt(data64);
    // 转换为json
    jsondoc = QJsonDocument::fromJson(dedata.toUtf8());
    QVariantList list = jsondoc.toVariant().toList();
    // 最终数据储存
    QVector<ProData> *proList = new QVector<ProData>();
    for (int i = 0; i < list.size(); i++)
    {
        QVariantMap map = list.at(i).toMap();
        ProData proInfo;
        proInfo.id = map.value("id").toString();
        proInfo.Time = map.value("time").toString();
        proInfo.Status = map.value("status").toInt();
        proInfo.PhDirectHigh = map.value("phdirecthigh").toFloat();
        proInfo.PhDirectLow = map.value("phdirectlow").toFloat();
        proInfo.PhIndirectHigh = map.value("phindirecthigh").toFloat();
        proInfo.PhIndirectLow = map.value("phindorectlow").toFloat();
        proInfo.CODDirect = map.value("coddirect").toFloat();
        proInfo.CODIndirect = map.value("codindirect").toFloat();
        proInfo.TPDirect = map.value("tpdirect").toFloat();
        proInfo.TPIndirect = map.value("tpindirect").toFloat();
        proInfo.TNDirect = map.value("tndirect").toFloat();
        proInfo.IPIndirect = map.value("ipindirect").toFloat();
        proInfo.ANDirect = map.value("andirect").toFloat();
        proInfo.ANINDirect = map.value("anindirect").toFloat();
        proInfo.OCCDirect = map.value("occdirect").toFloat();
        proInfo.OCCIndirect = map.value("occindirect").toFloat();
        proInfo.FSCDirectT = map.value("fscdirectt").toFloat();
        proInfo.FSCIndirectT = map.value("fscindirectt").toFloat();
        proInfo.FSCDirectO = map.value("fscdirecto").toFloat();
        proInfo.FSCIndirectO = map.value("fscindirecto").toFloat();
        proInfo.SADirect = map.value("sadirect").toFloat();
        proInfo.SAIndirect = map.value("saindirect").toFloat();
        proInfo.FDirect = map.value("fdirect").toFloat();
        proInfo.FIndirect = map.value("findirect").toFloat();
        proInfo.Cu = map.value("cu").toFloat();
        proInfo.Zn = map.value("zn").toFloat();
        proInfo.Sn = map.value("sn").toFloat();
        proInfo.Sb = map.value("sb").toFloat();
        proInfo.Hg = map.value("hg").toFloat();
        proInfo.Cd = map.value("cd").toFloat();
        proInfo.Pb = map.value("pb").toFloat();
        proInfo.As = map.value("as").toFloat();
        proInfo.Cr6 = map.value("cr6").toFloat();
        proInfo.Gc = map.value("gs").toFloat();
        proInfo.Density = map.value("density").toFloat();
        proInfo.Conductivity = map.value("conductivity").toFloat();
        proInfo.Mc = map.value("mc").toFloat();
        proInfo.Sc = map.value("sc").toFloat();
        proInfo.Toc = map.value("toc").toFloat();
        proInfo.BOD5Direct = map.value("bod5direct").toFloat();
        proInfo.BOD5Indirect = map.value("bod5indirect").toFloat();
        proInfo.BOD = map.value("bod").toFloat();
        proInfo.PDirect = map.value("pdirect").toFloat();
        proInfo.BC = map.value("bc").toFloat();
        proInfo.SLC = map.value("slc").toFloat();
        proInfo.COLORDirect = map.value("colordirect").toFloat();
        proInfo.COLORIndirect = map.value("colorindirect").toFloat();
        proInfo.AFDirect = map.value("afdirect").toFloat();
        proInfo.AFINDirect = map.value("afindirect").toFloat();
        proInfo.CLDirect = map.value("cldirect").toFloat();
        proInfo.CLIndirect = map.value("clindirect").toFloat();
        proInfo.PINDirect = map.value("pindirect").toFloat();
        proInfo.Cr = map.value("cr").toFloat();
        proList->append(proInfo);
    }
    // 逆置
    std::reverse(proList->begin(), proList->end());
    return proList;
}

Standard *NodeInterface::getStandard(QString standard)
{
    // 获取标准
    netWorkUtils nwu;
    nwu.get("/standard");
    nwu.addQuery("id", standard);
    // 连接信号
    connect(&nwu, SIGNAL(netError(QString)), this, SLOT(onnetError(QString)));
    // 获取返回的byte数据转换为json
    QJsonParseError jsonError;
    QJsonDocument jsondoc = QJsonDocument::fromJson(nwu.exec(), &jsonError);
    // 断开信号
    disconnect(&nwu, SIGNAL(netError(QString)), this, SLOT(onnetError(QString)));
    QJsonObject jsonObjo = jsondoc.object();
    // 读取data
    QString data = jsonObjo.value("data").toString();
    if (data == "")
    {
        emit netError("服务器返回为null");
        qDebug() << "服务器返回为null";
        return nullptr;
    }
    // 转换为json
    jsondoc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jsonObj = jsondoc.object();
    qDebug() << jsonObj;
    // // 最终数据储存
    Standard *fstandard = new Standard();
    fstandard->ID = jsonObj.value("id").toString();
    fstandard->Description = jsonObj.value("description").toString();
    fstandard->Name = jsonObj.value("name").toString();
    fstandard->PhDirectHigh = jsonObj.value("phdirecthigh").toDouble();
    fstandard->PhDirectLow = jsonObj.value("phdirectlow").toDouble();
    fstandard->PhIndirectHigh = jsonObj.value("phindirecthigh").toDouble();
    fstandard->PhIndirectLow = jsonObj.value("phindirectlow").toDouble();
    fstandard->CODDirect = jsonObj.value("coddirect").toDouble();
    fstandard->CODIndirect = jsonObj.value("codindirect").toDouble();
    fstandard->TPDirect = jsonObj.value("tpdirect").toDouble();
    fstandard->TPIndirect = jsonObj.value("tpindirect").toDouble();
    fstandard->TNDirect = jsonObj.value("tndirect").toDouble();
    fstandard->IPIndirect = jsonObj.value("ipindirect").toDouble();
    fstandard->ANDirect = jsonObj.value("andirect").toDouble();
    fstandard->ANINDirect = jsonObj.value("anindirect").toDouble();
    fstandard->OCCDirect = jsonObj.value("occdirect").toDouble();
    fstandard->OCCIndirect = jsonObj.value("occindirect").toDouble();
    fstandard->FSCDirectT = jsonObj.value("fscdirectt").toDouble();
    fstandard->FSCIndirectT = jsonObj.value("fscindirectt").toDouble();
    fstandard->FSCDirectO = jsonObj.value("fscdirecto").toDouble();
    fstandard->FSCIndirectO = jsonObj.value("fscindirecto").toDouble();
    fstandard->SADirect = jsonObj.value("sadirect").toDouble();
    fstandard->SAIndirect = jsonObj.value("saindirect").toDouble();
    fstandard->FDirect = jsonObj.value("fdirect").toDouble();
    fstandard->FIndirect = jsonObj.value("findirect").toDouble();
    fstandard->Cu = jsonObj.value("cu").toDouble();
    fstandard->Zn = jsonObj.value("zn").toDouble();
    fstandard->Sn = jsonObj.value("sn").toDouble();
    fstandard->Sb = jsonObj.value("sb").toDouble();
    fstandard->Hg = jsonObj.value("hg").toDouble();
    fstandard->Cd = jsonObj.value("cd").toDouble();
    fstandard->Pb = jsonObj.value("pb").toDouble();
    fstandard->As = jsonObj.value("as").toDouble();
    fstandard->Cr6 = jsonObj.value("cr6").toDouble();
    fstandard->Ton = jsonObj.value("ton").toDouble();
    fstandard->Gc = jsonObj.value("gc").toDouble();
    fstandard->Density = jsonObj.value("density").toDouble();
    fstandard->Conductivity = jsonObj.value("conductivity").toDouble();
    fstandard->Mc = jsonObj.value("mc").toDouble();
    fstandard->Sc = jsonObj.value("sc").toDouble();
    fstandard->Toc = jsonObj.value("toc").toDouble();
    fstandard->BOD5Direct = jsonObj.value("bod5direct").toDouble();
    fstandard->BOD5Indirect = jsonObj.value("bod5indirect").toDouble();
    fstandard->BOD = jsonObj.value("bod").toDouble();
    fstandard->PDirect = jsonObj.value("pdirect").toDouble();
    fstandard->Bc = jsonObj.value("bc").toDouble();
    fstandard->Slc = jsonObj.value("slc").toDouble();
    fstandard->COLORDirect = jsonObj.value("colordirect").toDouble();
    fstandard->COLORIndirect = jsonObj.value("colorindirect").toDouble();
    fstandard->AFDirect = jsonObj.value("afdirect").toDouble();
    fstandard->AFINDirect = jsonObj.value("afindirect").toDouble();
    fstandard->CLDirect = jsonObj.value("cldirect").toDouble();
    fstandard->CLIndirect = jsonObj.value("clindirect").toDouble();
    fstandard->PINDirect = jsonObj.value("pindirect").toDouble();
    fstandard->Cr = jsonObj.value("cr").toDouble();
    return fstandard;
}

void NodeInterface::onnetError(QString err)
{
    emit netError(err);
}