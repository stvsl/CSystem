#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QUrl>
#include <QWebChannel>

namespace Ui {
class MapView;
}

class MapView : public QWidget
{
    Q_OBJECT

public:
    explicit MapView(QWidget *parent = nullptr);
    ~MapView();

signals:
    void setcenter();
    void setpoitext();
    void setpoiicon();
    void searchp(QString str);

private slots:
    void on_PositionReset_clicked();

    void on_mapSearcher_editingFinished();

private:
    QWebChannel *channel;
    Ui::MapView *ui;
};

#endif // MAPVIEW_H
