#include "main.h"
#include "QMessageBox"

int MAIN_RUN_CONFIG::SYSTEM_STATUS = 0;
QString MAIN_RUN_CONFIG::SYSTEM_TOKEN = "";

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
    QTimer::singleShot(200, &eventloop, SLOT(quit()));
    eventloop.exec();
    //检查屏幕状态
    QScreen *mScreen = QGuiApplication::screens().at(0);

    //配置文件加载
    splash.showMessage("正在读取配置文件", Qt::AlignBottom, Qt::black);
    configManager config;
    config.makeRSA();
    qDebug() << CONFIG_CORE::RSA_PRIVATE_KEY;

    //局部事件循环
    QTimer::singleShot(200, &eventloop, SLOT(quit()));
    eventloop.exec();

    //网络模块加载
    splash.showMessage("正在检查网络", Qt::AlignBottom, Qt::black);
    netWorkUtils nwu;
    QString err = nwu.ping();
    qDebug() << err;
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
    db->readUserInfo();

    splash.showMessage("正在拉起登录模块", Qt::AlignBottom, Qt::black);

    // 启动登录界面
    Login login;
    // 移动到屏幕中央
    QPoint center = mScreen->geometry().center();
    login.move(center.x() - login.width() / 2, center.y() - login.height() / 2);
    //主界面启动时关闭启动等待页面
    splash.finish(&login);
    login.show();
    return a.exec();
}
