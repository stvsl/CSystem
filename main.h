#ifndef MAIN_H
#define MAIN_H

#include <QApplication>
#include <QScreen>
#include <QSplashScreen>
#include <QTranslator>
#include <QObject>
#include "csystemmain/csystemmain.h"
#include "netWorkUtils/netWorkUtils.h"
#include "configManager/configmanager.h"
#include "DButils/dbutils.h"

class runObjectUtils : public QObject
{
    Q_OBJECT

public:
    /***
    *lock:系统运行指示锁
    *状态：
    *   0 ～ 初始化
    *   1 ～ 系统正常
    *   2 ～ 网络异常
    *   3 ～ 本地数据库异常
    *   4 ～ 休眠
    *   5 ～ 停止运行
    *   6 ～ 委托重启
    ***/
    int lock = 0;
};

#endif // MAIN_H
