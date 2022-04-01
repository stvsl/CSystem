#ifndef MAPSETTING_H
#define MAPSETTING_H

#include <QWidget>

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

    void init();
};

#endif // MAPSETTING_H
