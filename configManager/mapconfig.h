#ifndef MAPCONFIG_H
#define MAPCONFIG_H

#include <QObject>
///
/// \brief 地图个性化信息配置管理器
///
class mapConfig : public QObject
{
    Q_OBJECT
public:
    explicit mapConfig(QObject *parent = nullptr);


public:

    ///
    /// \brief 显示地标(poi)文字
    ///
    static bool MAP_POITEXT_ON;

    ///
    /// \brief 显示地标(poi)图标
    ///
    static bool MAP_POIICON_ON;

    ///
    /// \brief 默认地址
    ///
    static QString  MAP_DEFAULT_LOCATE;

    ///
    /// \brief 地图卫星地球模式
    ///
    static bool MAP_EARTHMODEL;

    ///
    /// \brief 3D控件支持
    ///
    static bool MAP_CONTROL_3D;

    ///
    /// \brief 比例尺控件支持
    ///
    static bool MAP_CONTROL_SCALE;

    ///
    /// \brief 自动定位
    ///
    static bool MAP_AUTO_POSITIONING;

private:

    ///
    /// \brief 地图配置文件读取器
    ///
    void reader();

    ///
    /// \brief 地图配置文件写入器
    ///
    void writer();

};

#endif // MAPCONFIG_H
