#include "encryptionconfig.h"

EncryptionConfig::EncryptionConfig(QObject *parent)
    : QObject{parent}
{

}

QString EncryptionConfig::generatePassword()
{
    // 随机字符串种子
    QTime time = QTime::currentTime();
    qsrand(time.msec() + time.second() * 1000);
    QString passwd;
    // 种子字符串
    QString seed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    // 生成随机字符串
    for(int i = 0; i < 15; i++)
    {
        passwd[i] = seed[qrand() % seed.length()];
    }
    // 拼接
    passwd = passwd + QString::number(qrand() % 1000000000000);
    // 计算MD5
    QByteArray byteArray = QCryptographicHash::hash(passwd.toUtf8(), QCryptographicHash::Md5);
    return byteArray.toHex();
}

void EncryptionConfig::read(QString passwd){
    // 读取
    QFile file("data/encryption");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream in(&file);
    QString line = in.readLine();
    while(!line.isNull())
    {
        if(line.contains("databasePasswd"))
        {
            databasePasswd_Old = line.split("=")[1];
        }
        line = in.readLine();
    }
    file.close();
    // 判断是否需要加密
    if(databasePasswd_Old != passwd)
    {
        // 加密
        QString databasePasswd_New = generatePassword();
        // 写入
        write(databasePasswd_New);
    }
}
