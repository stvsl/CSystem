#ifndef MAPSETTING_H
#define MAPSETTING_H

#include <QWidget>

namespace Ui {
class MapSetting;
}

class MapSetting : public QWidget
{
    Q_OBJECT

public:
    explicit MapSetting(QWidget *parent = nullptr);
    ~MapSetting();

private:
    Ui::MapSetting *ui;
};

#endif // MAPSETTING_H
