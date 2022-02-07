#include "login.h"
#include "ui_login.h"
#include "QPixmap"
#include "QPalette"
#include "QPropertyAnimation"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    // 关闭标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    // 绑定按钮状态
    // ui->auto_login->setChecked(LOGIN_CONFIG::AUTO_LOGIN);
    // ui->passwd_save->setChecked(LOGIN_CONFIG::SAVE_PASSWD);
    // 启动
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

// 关闭程序
void Login::on_exit_btn_clicked()
{
    this->close();
}

// 更多按钮点击事件
void Login::on_more_btn_clicked()
{
    ui->mode_changer->setCurrentIndex(1);
    // 动画效果
    QPropertyAnimation *animation = new QPropertyAnimation(ui->groupBox_2, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(0, 0, 0, 0));
    animation->setEndValue(QRect(0, 0, ui->groupBox_2->width(),ui->groupBox_2->height()));
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

// 返回按钮点击事件
void Login::on_back_btn_clicked()
{
    ui->mode_changer->setCurrentIndex(0);
    // 动画效果
    QPropertyAnimation *animation = new QPropertyAnimation(ui->groupBox, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(0, 0, 0, 0));
    animation->setEndValue(QRect(0, 0, ui->groupBox->width(),ui->groupBox->height()));
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

