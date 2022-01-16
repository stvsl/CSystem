#ifndef SERVICECONTROL_H
#define SERVICECONTROL_H

#include <QWidget>

namespace Ui {
class ServiceControl;
}

class ServiceControl : public QWidget
{
    Q_OBJECT

public:
    explicit ServiceControl(QWidget *parent = nullptr);
    ~ServiceControl();

private:
    Ui::ServiceControl *ui;
};

#endif // SERVICECONTROL_H
