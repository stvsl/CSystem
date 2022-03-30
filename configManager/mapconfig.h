#ifndef MAPCONFIG_H
#define MAPCONFIG_H

#include <QObject>
///
/// \brief 地图个性化信息配置管理器
///
class MAP_CONFIG : public QObject
{
    Q_OBJECT

public:
    ///
    /// \brief 中央位置坐标X
    ///
    static float X;

    ///
    /// \brief 中央位置坐标Y
    ///
    static float Y;

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
    static QString MAP_DEFAULT_LOCATE;

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

    ///
    /// \brief 键盘控制
    ///
    static bool MAP_KEYBOARD_CONTROL;

    ///
    /// \brief 鼠标滚轮缩放
    ///
    static bool MAP_MOUSE_SCROLL_ZOOM;

    ///
    /// \brief 移除地图动画
    ///
    static bool MAP_REMOVE_ANIMATION;

    ///
    /// \brief 使用内部HTML文件
    ///
    static bool MAP_USE_INTERNAL_HTML;

    ///
    /// \brief 自动清除缓存
    ///
    static bool MAP_AUTO_CLEAR_CACHE;

    ///
    /// \brief 拖拽控制
    ///
    static bool MAP_DRAG_CONTROL;

    ///
    /// \brief 惯性拖拽
    ///
    static bool MAP_INERTIAL_DRAG;
};
#endif // MAPCONFIG_H
