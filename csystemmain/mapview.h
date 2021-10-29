#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QUrl>

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


private:
    Ui::MapView *ui;
};

#endif // MAPVIEW_H
