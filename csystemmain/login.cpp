#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) : QMainWindow(parent),
                                ui(new Ui::Login)
{
    // 关闭标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    // 启动
    ui->setupUi(this);
    // 设置记住密码按钮状态
    if (LOGIN_CONFIG::SAVE_PASSWD)
    {
        ui->passwd_save->setChecked(true);
        ui->inPut_ID->setText(LOGIN_CONFIG::ID);
        ui->inPut_Passwd->setText(LOGIN_CONFIG::PASSWD);
        // 设置自动登录按钮状态
        if (LOGIN_CONFIG::AUTO_LOGIN)
        {
            ui->auto_login->setChecked(true);
        }
    }
    else
    {
        ui->passwd_save->setChecked(false);
        // 禁用自动登录按钮
        ui->auto_login->setEnabled(false);
    }
    // 判断是否自动登录
    if (LOGIN_CONFIG::AUTO_LOGIN)
    {
        // 点击登录按钮
        QTimer::singleShot(1000, this, SLOT(on_login_btn_clicked()));
    }
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
    animation->setEndValue(QRect(0, 0, ui->groupBox_2->width(), ui->groupBox_2->height()));
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
    animation->setEndValue(QRect(0, 0, ui->groupBox->width(), ui->groupBox->height()));
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void Login::on_passwd_save_stateChanged(int arg1)
{
    // 自动登录按钮enable状态改变
    ui->auto_login->setEnabled(arg1);
    // 如果disable则记住密码设置为false
    if (!arg1)
    {
        ui->auto_login->setChecked(false);
    }
    // 修改配置文件
    LOGIN_CONFIG::SAVE_PASSWD = arg1;
    // 写入数据库
    DButils db;
    db.writeUserInfo();
}

void Login::on_auto_login_stateChanged(int arg1)
{
    // 修改配置文件
    LOGIN_CONFIG::AUTO_LOGIN = arg1;
    // 程序等待1000后继续执行
    QTimer::singleShot(1000, [=]()
                       {
        // 写入数据库
        DButils db;
        db.writeUserInfo(); });
}

void Login::on_login_btn_clicked()
{
    ui->login_btn->setText("登录中...");
    // 判断账号是否为空和密码小于8位
    if (ui->inPut_ID->text().isEmpty() || ui->inPut_Passwd->text().length() < 8)
    {
        QMessageBox::warning(this, "警告", "ID或密码不能为空！");
        ui->login_btn->setText("登录");
        return;
    }
    LOGIN_CONFIG::ID = ui->inPut_ID->text();
    LOGIN_CONFIG::PASSWD = ui->inPut_Passwd->text();
    // 获取token
    Security secu;
    if (secu.getToken() != "CX200")
    {
        // 弹出错误提示
        QMessageBox::warning(this, "登录失败", "账号或密码错误！", QMessageBox::Ok);
        ui->login_btn->setText("登录");
        ui->inPut_ID->clear();
        ui->inPut_Passwd->clear();
        return;
    }
    ui->login_btn->setText("正在拉取用户信息");
    UserInterface uif;
    QString userinfo = uif.getUserInformation();
    // 解析为json
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(userinfo.toUtf8(), &json_error);
    // 判断是否解析成功
    if (json_error.error != QJsonParseError::NoError)
    {
        QMessageBox::warning(this, "登录失败", "账号或密码错误！", QMessageBox::Ok);
        ui->login_btn->setText("登录");
        ui->inPut_ID->clear();
        ui->inPut_Passwd->clear();
        return;
    }
    // 判断是否保存ID和密码
    if (ui->passwd_save->isChecked())
    {
        // 保存ID和密码
        LOGIN_CONFIG::SAVE_PASSWD = true;
        LOGIN_CONFIG::ID = ui->inPut_ID->text();
        LOGIN_CONFIG::PASSWD = ui->inPut_Passwd->text();
    }
    else
    {
        // 不保存ID和密码
        LOGIN_CONFIG::SAVE_PASSWD = false;
        LOGIN_CONFIG::ID = "";
        LOGIN_CONFIG::PASSWD = "";
    }

    // 写入数据库
    DButils db;
    db.writeUserInfo();

    // EncryptionConfig ec;
    // if (MAIN_RUN_CONFIG::SYSTEM_STATUS == 3)
    // {
    //     ui->login_btn->setText("正在请求解锁数据库");
    //     // 获取解锁数据库的密码
    //     ec.getUnlockPassword();
    //     // 重新设置数据库密码
    //     CONFIG_CORE::DB_PASSWD = ec.databasePasswd_Old;
    //     ui->login_btn->setText("数据库已解锁");
    //     MAIN_RUN_CONFIG::SYSTEM_STATUS = 1;
    // }
    // // 上传密码残片
    // ec.uploadPasswordFragment();
    // 逐渐消失
    ui->login_btn->setText("正在加载数据");
    emit launch();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(230);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->setEasingCurve(QEasingCurve::InQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    QFile file(":/style/Style/defaultStyle.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        file.close();
    }
    QTimer::singleShot(1000, [=]()
                       { this->hide();
                         this->close(); });
}
