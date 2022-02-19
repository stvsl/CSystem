#ifndef ENCRYPTIONCONFIG_H
#define ENCRYPTIONCONFIG_H

#include <QObject>
#include <QTime>
#include <QCryptographicHash>
#include <QFile>
#include <QTextStream>

class EncryptionConfig : public QObject
{
    Q_OBJECT
public:
    explicit EncryptionConfig(QObject *parent = nullptr);

public:
    // 生成密码
    QString generatePassword();

    // 读取
    void read(QString passwd);
    // 写入
    void write(QString passd);

    // 数据库密码
    QString databasePasswd_Old;

signals:

};

#endif // ENCRYPTIONCONFIG_H
