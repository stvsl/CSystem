#ifndef NODEINSTALL_H
#define NODEINSTALL_H

#include <QWidget>

namespace Ui {
class NodeInstall;
}

class NodeInstall : public QWidget
{
    Q_OBJECT

public:
    explicit NodeInstall(QWidget *parent = nullptr);
    ~NodeInstall();

private:
    Ui::NodeInstall *ui;
};

#endif // NODEINSTALL_H
