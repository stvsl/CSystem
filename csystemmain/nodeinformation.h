#ifndef NODEINFORMATION_H
#define NODEINFORMATION_H

#include <QWidget>

namespace Ui {
class nodeinformation;
}

class nodeinformation : public QWidget
{
    Q_OBJECT

public:
    explicit nodeinformation(QWidget *parent = nullptr);
    ~nodeinformation();

private:
    Ui::nodeinformation *ui;
};

#endif // NODEINFORMATION_H
