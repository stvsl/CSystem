#include "main.h"

int MAIN_RUN_CONFIG::SYSTEM_STATUS = -1;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("stvsl&jc");
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
    splash.showMessage("系统启动中，请稍候", Qt::AlignBottom, Qt::red);

    //检查屏幕状态
    QScreen *mScreen = QGuiApplication::screens().at(0);

    //配置文件加载
    splash.showMessage("正在读取配置文件", Qt::AlignBottom, Qt::red);
    configManager config;
    //首次运行状态数据同步到全局
    MAIN_RUN_CONFIG::SYSTEM_STATUS = CONFIG_CORE::RUN_FIRST;

    //网络模块加载
    splash.showMessage("正在连接网络", Qt::AlignBottom, Qt::red);
    netWorkUtils nwu;

    //数据库模块加载
    splash.showMessage("正在连接本地数据库", Qt::AlignBottom, Qt::red);
    DButils DB;

    splash.showMessage("加载完成！欢迎！！！", Qt::AlignBottom, Qt::red);

    //局部事件循环
    QEventLoop eventloop;
    QTimer::singleShot(200, &eventloop, SLOT(quit()));
    eventloop.exec();
    //启动主界面
    CSystemMain w;
    w.show();
    w.move(((mScreen->geometry().width()-w.width())/2),((mScreen->geometry().height()-w.height())/2));
    //主界面启动时关闭启动等待页面
    splash.finish(&w);
    return a.exec();
}
