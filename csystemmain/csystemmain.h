#ifndef CSYSTEMMAIN_H
#define CSYSTEMMAIN_H

#include <QMainWindow>
#include "configManager/configmanager.h"
#include "mapview.h"
#include "systemsetting.h"
#include "nodeinformation.h"
#include "dataview.h"
#include "mapsetting.h"
#include "nodeinstall.h"
#include "accountmanagement.h"
#include <QStandardItemModel>
#include <configManager/configmanager.h>

namespace Ui
{
    class CSystemMain;
    class MapView;
}

class CSystemMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit CSystemMain(QWidget *parent = nullptr);
    static QVector<NodeInfo> *nodeInfoList; // 节点数据缓存指针
    static QVector<NodeData> *nodeDataList; // 节点详细数据缓存指针

    ~CSystemMain();

private slots:
    void on_side_menu_clicked(const QModelIndex &index);

public slots:
    void bottombarchanged();
    void showEvent();

private:
    Ui::CSystemMain *ui;

    /***
     * 用户级别指针
     */
    ///
    /// \brief 默认用户
    ///
    QStandardItemModel *USER_DEFAULT;

    ///
    /// \brief 数据录入人员
    ///
    QStandardItemModel *USER_ENTRY;

    ///
    /// \brief 地方管理员
    ///
    QStandardItemModel *USER_ADMIN_DOMAN;

    ///
    /// \brief 最高管理员
    ///
    QStandardItemModel *USER_ADMIN_FULL;

    /***
     * 界面指针
     */

    ///
    /// \brief 全局信息界面指针
    ///
    MapView *WINDOW_MAP_VIEW;

    ///
    /// \brief 节点详细信息界面指针
    ///
    nodeinformation *WINDOW_NODE_INFORMATION;

    ///
    /// \brief 数据浏览界面指针
    ///
    DataView *WINDOW_DATA_VIEW;

    ///
    /// \brief 地图设置指针
    ///
    MapSetting *WINDOW_MAP_SETTING;

    ///
    /// \brief 系统设置界面指针
    ///
    SystemSetting *WINDOW_SYSTEM_SETTING;

    ///
    /// \brief 节点配置界面指针
    ///
    NodeInstall *WINDOW_NODE_INSTALL;

    ///
    /// \brief 账户管理界面指针
    ///
    AccountManagement *WINDOW_ACCOUNT_MANAGEMENT;

    /***
     * 内部函数及内部全局值
     */

    ///
    /// \brief 菜单初始化
    ///
    void initialization();

    ///
    /// \brief 界面呈现状态控制器
    ///
    int widgetstatus = 0;
};

#endif // CSYSTEMMAIN_H
