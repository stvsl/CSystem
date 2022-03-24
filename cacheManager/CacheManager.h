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

class NodeData
{
public:
    QString id;           // 节点ID信息    json："id"
    QString Community;    // 检测机构名称    json："community"
    QString ComId;        // 检测机构的账户ID    json："comId"
    QString Time;         // 记录时间        json："time"
    int Status;           // 检测结果状态    json："status"
    float PhDirectHigh;   // PH直接排放上限  json:"phdirecthigh"
    float PhDirectLow;    // PH直接排放下限  json:"phdirectlow"
    float PhIndirectHigh; // PH间接排放上限  json:"phindirecthigh"
    float PhIndirectLow;  // PH间接排放下限  json:"phindirectlow"
    float CODDirect;      // 化学需氧量直接  json:"coddirect"
    float CODIndirect;    // 化学需氧量间接  json:"codindirect"
    float TPDirect;       // 总磷直接  json:"tpdirect"
    float TPIndirect;     // 总磷间接  json:"tpindirect"
    float TNDirect;       // 总氮直接  json:"tndirect"
    float IPIndirect;     // 总氮间接  json:"ipindirect"
    float ANDirect;       // 氨氮直接  json:"andirect"
    float ANINDirect;     // 氨氮间接  json:"anindirect"
    float OCCDirect;      // 石油类直接  json:"occdirect"
    float OCCIndirect;    // 石油类间接  json:"occindirect"
    float FSCDirectT;     // 悬浮物直接T  json:"fscdirectt"
    float FSCIndirectT;   // 悬浮物间接T  json:"fscindirectt"
    float FSCDirectO;     // 悬浮物直接O  json:"fscdirecto"
    float FSCIndirectO;   // 悬浮物间接O  json:"fscindirecto"
    float SADirect;       // 硫化物直接  json:"sadirect"
    float SAIndirect;     // 硫化物间接  json:"saindirect"
    float FDirect;        // 氟化物直接  json:"fdirect"
    float FIndirect;      // 氟化物间接  json:"findirect"
    float Cu;             // 总铜   json:"cu"
    float Zn;             // 总锌   json:"zn"
    float Sn;             // 总锡   json:"sn"
    float Sb;             // 总锑   json:"sb"
    float Hg;             // 总汞   json:"hg"
    float Cd;             // 总镉   json:"cd"
    float Pb;             // 总铅   json:"pb"
    float As;             // 总砷   json:"as"
    float Cr6;            // 六价铬 json:"cr6"
    float Gc;             // 气体浓度   json:"gc"
    float Density;        // 浊度   json:"density"
    float Conductivity;   // 电导率    json:"conductivity"
    float Mc;             // 重金属  json:"mc"
    float Sc;             // 溶解性固体 json:"sc"
    float Toc;            // 总有机碳   json:"toc"
    float BOD5Direct;     // 五日生化需氧量直接  json:"bod5direct"
    float BOD5Indirect;   // 五日生化需氧量间接    json:"bod5indirect"
    float BOD;            // 生物需氧量  json:"bod"
    float PDirect;        // 总磷直接   json:"pdirect"
    float BC;             // 细菌总数   json:"bc"
    float SLC;            // 大肠杆菌数   json:"slc"
    float COLORDirect;    // 色度直接   json:"colordirect"
    float COLORIndirect;  // 色度间接   json:"colorindirect"
    float AFDirect;       // 动植物油直接   json:"afdirect"
    float AFINDirect;     // 动植物油间接   json:"afindirect"
    float CLDirect;       // 氯离子直接   json:"cldirect"
    float CLIndirect;     // 氯离子间接   json:"clindirect"
    float PINDirect;      // 总磷间接   json:"pindirect"
    float Cr;             // 总铬   json:"cr"
    float Ton;            // 单位   json:"ton"
};

class Standard
{
};

#endif // CACHEMANAGER_H