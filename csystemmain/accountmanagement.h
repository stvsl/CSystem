#ifndef ACCOUNTMANAGEMENT_H
#define ACCOUNTMANAGEMENT_H

#include <QWidget>

namespace Ui {
class AccountManagement;
}

class AccountManagement : public QWidget
{
    Q_OBJECT

public:
    explicit AccountManagement(QWidget *parent = nullptr);
    ~AccountManagement();

private:
    Ui::AccountManagement *ui;
};

#endif // ACCOUNTMANAGEMENT_H
