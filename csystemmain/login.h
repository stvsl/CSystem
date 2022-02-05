#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:

private slots:
    void on_exit_btn_clicked();

    void on_more_btn_clicked();

    void on_back_btn_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
