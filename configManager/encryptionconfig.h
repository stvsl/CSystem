#ifndef ENCRYPTIONCONFIG_H
#define ENCRYPTIONCONFIG_H

#include <QObject>
#include <QTime>
#include <QCryptographicHash>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include "configManager/configmanager.h"
#include "main.h"
#include "AES/aes.h"

class EncryptionConfig : public QObject
{
    Q_OBJECT
public:
    explicit EncryptionConfig(QObject *parent = nullptr);

public:
    // 生成密码
    QString generatePassword();

    // 获取解锁密码
    QString getUnlockPassword();

    // 上传密码残片
    QString uploadPasswordFragment(); 

    // 读取
    void read();

    // 写入
    void write();

    // 数据库密码
    static QString databasePasswd_Old;

    // 密钥
    static QString key;

private:
    QTimer timer;

};

#endif // ENCRYPTIONCONFIG_H
