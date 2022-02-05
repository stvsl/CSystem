#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("stvsl&jl");
    QCoreApplication::setApplicationName("CSystem");
    QCoreApplication::setOrganizationDomain("stvsl.github.io");
    QCoreApplication::setApplicationVersion("v0.0.1");
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "CSystem_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    //启动等待页面
    QPixmap pixmap(":/loading/loading/pixmap.png");
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("系统启动中，请稍候", Qt::AlignBottom, Qt::white);

    //检查屏幕状态
    QScreen *mScreen = QGuiApplication::screens().at(0);

    //配置文件加载
    splash.showMessage("正在读取配置文件", Qt::AlignBottom, Qt::white);
    configManager config;

    //网络模块加载
    splash.showMessage("正在连接网络", Qt::AlignBottom, Qt::white);
    netWorkUtils nwu;

    //数据库模块加载
    splash.showMessage("正在连接本地数据库", Qt::AlignBottom, Qt::white);
    DButils DB;

    splash.showMessage("加载完成！欢迎！！！", Qt::AlignBottom, Qt::white);

    //局部事件循环
    QEventLoop eventloop;
    QTimer::singleShot(90, &eventloop, SLOT(quit()));
    eventloop.exec();

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
