#ifndef MAPSETTING_H
#define MAPSETTING_H

#include <QWidget>
#include <QWebChannel>

namespace Ui
{
    class MapSetting;
}

class MapSetting : public QWidget
{
    Q_OBJECT

public:
    explicit MapSetting(QWidget *parent = nullptr);
    ~MapSetting();

signals:
signals:

    ///
    /// \brief 设置中心位置
    ///
    void setCenter(float x, float y);

    ///
    /// \brief 设置地标文字
    ///
    void setPoiText(bool);

    ///
    /// \brief 设置地标图标
    ///
    void setPoiIcon(bool);

    ///
    /// \brief 搜索地址
    /// \param str
    ///
    void searchP(QString str);

    ///
    /// \brief 地图卫星地球模式
    ///
    void setMapType();

    ///
    /// \brief 添加结点
    ///
    void addPoint(QString info, float x, float y, QString data);

    ///
    /// \brief 请求获取地址信息
    ///
    void requestPointLocate(QString str);

    ///
    /// \brief 卫星地图模式
    ///
    void setMapType(int status);

private slots:
    void on_support_3D_stateChanged(int arg1);

    void on_support_ruler_stateChanged(int arg1);

    void on_show_Poi_Icon_stateChanged(int arg1);

    void on_show_Poi_Text_stateChanged(int arg1);

    void on_control_KeyBoard_stateChanged(int arg1);

    void on_control_Rolling_stateChanged(int arg1);

    void on_control_Drag_stateChanged(int arg1);

    void on_control_Drag_Flux_stateChanged(int arg1);

    void on_remove_Anmine_stateChanged(int arg1);

    void on_use_Insid_Controller_stateChanged(int arg1);

    void on_noCache_stateChanged(int arg1);

    void on_model_Earth_stateChanged(int arg1);

    void on_aoto_POS_stateChanged(int arg1);

    void on_saveanduse_btn_clicked();

    void on_cancle_btn_clicked();

    void on_reset_btn_clicked();

private:
    Ui::MapSetting *ui;
    QWebChannel *channelsetting;
    void init();
};

#endif // MAPSETTING_H
