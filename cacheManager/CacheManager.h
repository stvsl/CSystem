#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <QObject>
#include <QDateTime>

/*----------------------------------------------------------------
 *                  数据缓存管理器
 *  存储运行时的数据，系统关闭后数据将会销毁
 *  类本身不具备实体，其相关功能实现由其它各个类自行完成，其实体交由configManager进行管理
 *  操作由相关需求类进行实现
 *                                              @anchor stvsl
 *                                              @date   2022-3.18
 *----------------------------------------------------------------*/

class NodeInfo
{
public:
    // 数据成员
    QString ip;            // IP地址        json："ip"
    QString id;            // 节点ID信息    json："id"
    QString locate;        // 节点地理位置  json："locate"
    int type;              // 节点类型      json："type"
    QString belong;        // 所属信息      json："belong"
    QString principal;     // 负责人信息    json："principal"
    QString installer;     // 安装人信息    json："installer"
    QString maintainer;    // 维护人信息    json："maintainer"
    QString dataConfig;    // 数据来源配置  json："dataconfig"
    QString aesKey;        // AES密钥指纹    json："aeskeyfeature"
    QString selfInfo;      // 自检信息      json："selfinfo"
    QDateTime lastUpload;  // 上次更新日期  json："lastupload"
    QDateTime selfDate;    // 上次自检日期  json："selfdate"
    QString remark;        // 备注信息      json："remark"
    QDateTime installDate; // 安装日期      json："installdate"
    float lo;              // 经度          json："lo"
    float li;              // 纬度          json："li"
    // 时序数据
    float gasConcentration;    // 气体浓度    json："GasConcentration"
    float temperature;         // 温度         json："Temperature"
    float pH;                  // PH           json："PH"
    float density;             // 浊度         json："Density"
    float conductivity;        // 电导率       json："Conductivity"
    float oxygenConcentration; // 含氧量       json："OxygenConcentration"
    float metalConcentration;  // 重金属       json："MetalConcentration"
    float SC;                  // 溶解性固体  json："SC"
    float FSC;                 // 悬浮性固体  json："FSC"
    float TN;                  // 总氮         json："TN"
    float TP;                  // 总磷         json："TP"
    float TOC;                 // 总有机碳     json："TOC"
    float BOD;                 // 生物需氧量   json："BOD"
    float COD;                 // 化学需氧量   json："COD"
    int64_t BC;                // 细菌总数     json："BC"
    int64_t SLC;               // 大肠杆菌数   json："SLC"
    // 企业/机构信息
    QString COMID;      // 企业ID      json："comid"
    QString COMNAME;    // 企业名称    json："comname"
    QString REMARK;     // 企业备注    json："comremark"
    QString REGISTTIME; // 注册时间    json："register"
    QString COMTYPE;    // 企业类型    json："comtype"
    QString STANDARD;   // 服从标准    json："standard"

    // 状态
    int status;
};

#endif // CACHEMANAGER_H
