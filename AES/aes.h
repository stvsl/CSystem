#ifndef AES_H
#define AES_H

#include <QObject>
#include <openssl/aes.h>


class AES : public QObject
{
    Q_OBJECT
public:
    explicit AES(QObject *parent = nullptr);

    // AES加密
    QString encrypt(QByteArray data);

    // AES解密
    QString decrypt(QByteArray Data);

    // AESbyte加密
    QByteArray encrypt(QByteArray data, QString key);

    // AESbyte解密
    QByteArray decrypt(QByteArray Data, QString key);

};

#endif // AES_H
