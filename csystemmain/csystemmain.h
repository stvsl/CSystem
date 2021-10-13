#ifndef CSYSTEMMAIN_H
#define CSYSTEMMAIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CSystemMainWindow; }
QT_END_NAMESPACE

class CSystemMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CSystemMainWindow(QWidget *parent = nullptr);
    ~CSystemMainWindow();

private:
    Ui::CSystemMainWindow *ui;
};
#endif // CSYSTEMMAIN_H
