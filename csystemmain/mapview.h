#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QUrl>
#include <QDir>
#include <QWebChannel>
#include <QWebFrame>

namespace Ui {
class MapView;
}

class MapView : public QWidget
{
    Q_OBJECT

public:
    explicit MapView(QWidget *parent = nullptr);
    ~MapView();

public:


public slots:


private slots:
    void on_PositionReset_clicked();

private:
    Ui::MapView *ui;
};

#endif // MAPVIEW_H
