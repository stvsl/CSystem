#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "configManager/configmanager.h"
#include "DButils/dbutils.h"
#include "QPixmap"
#include "QPalette"
#include "QPropertyAnimation"
#include "QTimer"
#include "QDebug"
#include "netWorkUtils/security.h"
#include "netWorkUtils/userinterface.h"
#include "netWorkUtils/nodeinterface.h"
#include "configManager/encryptionconfig.h"
#include <QMessageBox>
#include <QPropertyAnimation>

namespace Ui
{
    class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void launch();
private slots:
    void on_exit_btn_clicked();

    void on_more_btn_clicked();

    void on_back_btn_clicked();

    void on_passwd_save_stateChanged(int arg1);

    void on_auto_login_stateChanged(int arg1);

    void on_login_btn_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
