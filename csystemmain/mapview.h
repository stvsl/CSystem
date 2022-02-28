#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QUrl>
#include <QWebChannel>
#include "DButils/nodeinfos.h"

namespace Ui
{
    class MapView;
}

class MapView : public QWidget
{
    Q_OBJECT

public:
    explicit MapView(QWidget *parent = nullptr);
    ~MapView();

public:
    void addAllPoint(QVector<NodeInfos> &nodelist);

    /***
     * 与js文件通讯的信号函数
     */
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
    void addPoint(QString name, float x, float y);

    /***
     * 界面按键相关的槽函数
     */
private slots:

    ///
    /// \brief 位置重置按钮点击事件
    ///
    void on_PositionReset_clicked();

    ///
    /// \brief 地图位置搜索功能输入触发事件
    ///
    void on_mapSearcher_editingFinished();

    ///
    /// \brief 结点搜索功能触发事件
    ///
    void on_node_Searcher_editingFinished();

private:
    QWebChannel *channel;
    Ui::MapView *ui;
};

#endif // MAPVIEW_H
