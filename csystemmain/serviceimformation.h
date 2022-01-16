#ifndef SERVICEIMFORMATION_H
#define SERVICEIMFORMATION_H

#include <QWidget>

namespace Ui {
class ServiceImformation;
}

class ServiceImformation : public QWidget
{
    Q_OBJECT

public:
    explicit ServiceImformation(QWidget *parent = nullptr);
    ~ServiceImformation();

private:
    Ui::ServiceImformation *ui;
};

#endif // SERVICEIMFORMATION_H
