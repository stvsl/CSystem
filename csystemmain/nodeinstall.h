#ifndef NODEINSTALL_H
#define NODEINSTALL_H

#include <QWidget>

namespace Ui
{
    class NodeInstall;
}

class NodeInstall : public QWidget
{
    Q_OBJECT

public:
    explicit NodeInstall(QWidget *parent = nullptr);
    ~NodeInstall();

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

public slots:

    // 接收地址信息
    void receiveLocateInfo(QString str, float x, float y);

private slots:
    void on_NodeList_clicked(const QModelIndex &index);

    void on_node_Search_editingFinished();

    void on_addNode_clicked();

    void on_removeNode_clicked();

    void on_typr_normal_toggled(bool checked);

    void on_type_iron_toggled(bool checked);

    void on_type_pg_toggled(bool checked);

    void on_type_lm_toggled(bool checked);

    void on_type_js_toggled(bool checked);

    void on_enableSelfCheck_stateChanged(int arg1);

    void on_sendCheckRequest_stateChanged(int arg1);

    void on_selfCheckCycle_valueChanged(int arg1);

    void on_GasAuto_toggled(bool checked);

    void on_Gas_Do_toggled(bool checked);

    void on_Gas_All_toggled(bool checked);

    void on_Tem_Auto_toggled(bool checked);

    void on_Tem_Do_toggled(bool checked);

    void on_Tem_ALL_toggled(bool checked);

    void on_den_Auto_toggled(bool checked);

    void on_den_Do_toggled(bool checked);

    void on_den_All_toggled(bool checked);

    void on_ph_Auto_toggled(bool checked);

    void on_ph_Do_toggled(bool checked);

    void on_ph_All_toggled(bool checked);

    void on_con_Auto_toggled(bool checked);

    void on_con_Do_toggled(bool checked);

    void on_con_All_toggled(bool checked);

    void on_oxy_Auto_toggled(bool checked);

    void on_oxy_Do_toggled(bool checked);

    void on_oxy_All_toggled(bool checked);

    void on_met_Auto_toggled(bool checked);

    void on_met_Do_toggled(bool checked);

    void on_met_All_toggled(bool checked);

    void on_dso_Auto_toggled(bool checked);

    void on_dso_Do_toggled(bool checked);

    void on_dso_All_toggled(bool checked);

    void on_fso_Auto_toggled(bool checked);

    void on_fso_Do_toggled(bool checked);

    void on_fso_All_toggled(bool checked);

    void on_tn_Auto_toggled(bool checked);

    void on_tn_Do_toggled(bool checked);

    void on_tn_All_toggled(bool checked);

    void on_oc_Auto_toggled(bool checked);

    void on_oc_Do_toggled(bool checked);

    void on_oc_All_toggled(bool checked);

    void on_tnb_Auto_toggled(bool checked);

    void on_tnb_Do_toggled(bool checked);

    void on_tnb_All_toggled(bool checked);

    void on_ec_Auto_toggled(bool checked);

    void on_ec_Do_toggled(bool checked);

    void on_ec_All_toggled(bool checked);

    void on_OK_btn_clicked();

    void on_recover_btn_clicked();

    void on_tp_Auto_toggled(bool checked);

    void on_tp_Do_toggled(bool checked);

    void on_tp_All_toggled(bool checked);

    void on_bod_Auto_toggled(bool checked);

    void on_bod_Do_toggled(bool checked);

    void on_bod_All_toggled(bool checked);

    void on_cod_Auto_toggled(bool checked);

    void on_cod_Do_toggled(bool checked);

    void on_cod_All_toggled(bool checked);

    void on_locateChangeByMap_clicked();

    void on_locateChangeByHand_clicked();

private:
    Ui::NodeInstall *ui;
};

#endif // NODEINSTALL_H
