#include "main.h"
#include "QMessageBox"
#include <QFile>

int MAIN_RUN_CONFIG::SYSTEM_STATUS = 0;
QString MAIN_RUN_CONFIG::SYSTEM_TOKEN = "";
QString MAIN_RUN_CONFIG::AES_KEY = "";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("stvsl&jl");
    QCoreApplication::setApplicationName("CSystem");
    QCoreApplication::setOrganizationDomain("stvsl.github.io");
    QCoreApplication::setApplicationVersion("v0.0.1");
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "CSystem_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }

    //启动等待页面
    QPixmap pixmap(":/loading/loading/pixmap.png");
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("系统启动中，请稍候", Qt::AlignBottom, Qt::black);

    QEventLoop eventloop;
    QTimer::singleShot(100, &eventloop, SLOT(quit()));
    eventloop.exec();
    //检查屏幕状态
    QScreen *mScreen = QGuiApplication::screens().at(0);

    //配置文件加载
    splash.showMessage("正在读取配置文件", Qt::AlignBottom, Qt::black);
    configManager config;
    config.makeRSA();

    //局部事件循环
    QTimer::singleShot(100, &eventloop, SLOT(quit()));
    eventloop.exec();

    //网络模块加载
    splash.showMessage("正在设置网络", Qt::AlignBottom, Qt::black);
    netWorkUtils nwu;
    nwu.setGlobalTimeout(5000);
    nwu.openHttpsGlobal();
    nwu.closeVerify();
    Security snet;
    QString err = snet.ping();

    if (err != "CX200")
    {
        // 弹窗提示，点击确定后关闭程序
        QMessageBox::critical(nullptr, "错误", "当前网络环境可能存在风险！系统已安全退出<br> 错误：" + err, QMessageBox::Ok);
        // 关闭splash
        splash.close();
        return 0;
    }

    // 加密协商
    splash.showMessage("正在协商安全加密", Qt::AlignBottom, Qt::black);
    err = snet.pingpost();
    if (err != "CX200")
    {
        // 弹窗提示，点击确定后关闭程序
        QMessageBox::critical(nullptr, "错误", "网络连接失败，请检查网络连接！<br>" + err, QMessageBox::Ok);
        // 关闭splash
        splash.close();
        return 0;
    }

    //数据库模块加载
    splash.showMessage("正在连接本地数据库", Qt::AlignBottom, Qt::black);
    // 初始化数据库
    DButils *db = new DButils();

    if (db->readUserInfo() == -1)
    {
        splash.showMessage("系统环境变化，数据库已锁定", Qt::AlignBottom, Qt::red);
        //局部事件循环
        QTimer::singleShot(200, &eventloop, SLOT(quit()));
        eventloop.exec();
    }

    splash.showMessage("正在拉起登录模块", Qt::AlignBottom, Qt::black);

    // 启动登录界面
    Login login;
    CSystemMain m;
    QObject::connect(&login, SIGNAL(launch()), &m, SLOT(show()));
    // 移动到屏幕中央
    QPoint center = mScreen->geometry().center();
    login.move(center.x() - login.width() / 2, center.y() - login.height() / 2);
    m.move(center.x() - m.width() / 2, center.y() - m.height() / 2);
    //主界面启动时关闭启动等待页面
    splash.close();
    // 淡入效果
    QPropertyAnimation *animation = new QPropertyAnimation(&login, "windowOpacity");
    animation->setDuration(280);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    login.show();
    return a.exec();
}