#ifndef CSYSTEMMAIN_H
#define CSYSTEMMAIN_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class CSystemMain;
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
};

#endif // CSYSTEMMAIN_H
