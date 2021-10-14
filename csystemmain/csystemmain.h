#ifndef CSYSTEMMAIN_H
#define CSYSTEMMAIN_H

#include <QMainWindow>

namespace Ui {
class CSystemMain;
}

class CSystemMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit CSystemMain(QWidget *parent = nullptr);
    ~CSystemMain();

private:
    Ui::CSystemMain *ui;
};

#endif // CSYSTEMMAIN_H
