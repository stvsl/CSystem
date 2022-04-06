#ifndef NODEINFORMATION_H
#define NODEINFORMATION_H

#include <QWidget>
#include <QtCharts/QChart>
#include <QChartView>
#include <QWebChannel>

namespace Ui
{
    class nodeinformation;
    QT_CHARTS_USE_NAMESPACE
}
QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

class nodeinformation : public QWidget
{
    Q_OBJECT

public:
    explicit nodeinformation(QWidget *parent = nullptr);
    ~nodeinformation();

signals:

    void setCenter(float x, float y);

    void setPoiText(bool);

    void setPoiIcon(bool);

    void searchP(QString str);

    void setMapType();

    void addPoint(QString info, float x, float y);

    void requestPointLocate(QString str);

private slots:
    void on_NodeList_clicked(const QModelIndex &index);

    void on_modSwitch_btn_clicked();

private:
    Ui::nodeinformation *ui;
    QWebChannel *channel_ni;
};

#endif // NODEINFORMATION_H
