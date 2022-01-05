#ifndef CSYSTEMMAIN_H
#define CSYSTEMMAIN_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "mapview.h"

namespace Ui {
class CSystemMain;
class MapView;
}

class CSystemMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit CSystemMain(QWidget *parent = nullptr);
    ~CSystemMain();


private slots:
    void on_MenuList_itemSelectionChanged();

private:
    Ui::CSystemMain *ui;
    MapView *mV;
    ///
    /// \brief 界面呈现状态控制器
    ///
    int widgetstatus = 0;
};

#endif // CSYSTEMMAIN_H
