#include "csystemmain/csystemmain.h"

#include <QApplication>
#include <QScreen>
#include <QGuiApplication>
#include <QSplashScreen>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
    QPixmap pixmap("imagine/pixmap.png");
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("系统启动中，请稍候", Qt::AlignBottom, Qt::red);

    //检查屏幕状态
    QScreen *mScreen = QGuiApplication::screens().at(0);

    splash.showMessage("正在读取配置文件", Qt::AlignBottom, Qt::red);
    //TODO

    splash.showMessage("正在连接网络", Qt::AlignBottom, Qt::red);
    //TODO

    splash.showMessage("正在连接数据库", Qt::AlignBottom, Qt::red);
    //TODO

    //启动主界面
    CSystemMainWindow w;
    w.show();
    w.move((mScreen->geometry().width()-w.width()),(mScreen->geometry().height()-w.height())/3);
    //主界面启动时关闭启动等待页面
    splash.finish(&w);
    return a.exec();
}
