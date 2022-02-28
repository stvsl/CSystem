#ifndef NODEINFOS_H
#define NODEINFOS_H

#include <QObject>

/***
 * 结点信息类
 */
class NodeInfos : public QObject
{
    Q_OBJECT
public:
    explicit NodeInfos(QObject *parent = nullptr);
    // 数据成员
    // 结点ID
    QString Id;
    // IP地址
    QString IP;
    // 节点地理位置
    QString Locate;
    // 节点类型
    int Type;
    // 所属信息
    QString Belong;
    // 负责人信息
    QString Principal;
    // 安装人信息
    QString Installer;
    // 维护人信息
    QString Maintainer;
    // 数据来源配置
    QString DataConfig;
    // 自检信息
    QString SelfInfo;
    // 上次更新日期
    QString LastUpload;
    // 上次自检日期
    QString SelfDate;
    // 备注信息
    QString Remark;
    // 安装日期
    QString InstallDate;
    // 经度
    float Lo;
    // 纬度
    float Li;
    // 气体浓度
    float GasConcentration;
    // 温度
    float Temperature;
    // PH
    float PH;
    // 浊度
    float Density;
    // 电导率
    float Conductivity;
    // 含氧量
    float OxygenConcentration;
    // 重金属
    float MetalConcentration;
    // 溶解性固体
    float SolidsConcentration;
    // 悬浮性固体
    float FloatingSolidsConcentration;
    // 总氮
    float TotalPhosphorus;
    // 总磷
    float TotalNitrogen;
    // 总有机碳
    float TotalOrganicCarbon;
    // 生物需氧量
    float BiologicalOxygenDemand;
    // 化学需氧量
    float ChemicalOxygenDemand;
    // 细菌总数
    int BacteriaCount;
    // 大肠杆菌数
    int StaphylococcusCount;
    // 数据成员

    // 超级多参初始化
    bool init(QString Id, QString IP, QString Locate, int Type, QString Belong, QString Principal, QString Installer, QString Maintainer, QString DataConfig, QString SelfInfo, QString LastUpload, QString SelfDate, QString Remark, QString InstallDate, float Lo, float Li, float GasConcentration, float Temperature, float PH, float Density, float Conductivity, float OxygenConcentration, float MetalConcentration, float SolidsConcentration, float FloatingSolidsConcentration, float TotalPhosphorus, float TotalNitrogen, float TotalOrganicCarbon, float BiologicalOxygenDemand, float ChemicalOxygenDemand, int BacteriaCount, int StaphylococcusCount);
};

#endif // NODEINFOS_H
