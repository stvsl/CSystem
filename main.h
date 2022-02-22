#ifndef MAIN_H
#define MAIN_H

#include <QApplication>
#include <QScreen>
#include <QSplashScreen>
#include <QTranslator>
#include <QObject>
#include "csystemmain/csystemmain.h"
#include "netWorkUtils/netWorkUtils.h"
#include "netWorkUtils/security.h"
#include "configManager/configmanager.h"
#include "DButils/dbutils.h"
#include "csystemmain/login.h"

class MAIN_RUN_CONFIG : public QObject
{
    Q_OBJECT

    /***
     *  系统运行相关
     */
public:
    /***
     * status:系统运行指示锁
     * 状态：
     *   0 ～ 首次运行
     *   1 ～ 系统正常
     *   2 ～ 网络异常
     *   3 ～ 本地数据库异常
     *   4 ～ 休眠
     *   5 ～ 停止运行
     *   6 ～ 委托重启
     ***/
    static int SYSTEM_STATUS;

    // 系统token信息
    static QString SYSTEM_TOKEN;

    // aes加密密钥信息
    static QString AES_KEY;
};

#endif // MAIN_H
