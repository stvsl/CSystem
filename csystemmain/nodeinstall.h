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

private:
    Ui::NodeInstall *ui;
};

#endif // NODEINSTALL_H
