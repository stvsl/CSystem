#ifndef RSA_H
#define RSA_H

#include <QString>
#include <configManager/configmanager.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define BEGIN_RSA_PUBLIC_KEY    "BEGIN RSA PUBLIC KEY"
#define BEGIN_RSA_PRIVATE_KEY   "BEGIN RSA PRIVATE KEY"
#define BEGIN_PUBLIC_KEY        "BEGIN PUBLIC KEY"
#define BEGIN_PRIVATE_KEY       "BEGIN PRIVATE KEY"
#define KEY_LENGTH              1024

class rsa
{
public:
    rsa();
    ~rsa();

    QString rsaPubEncrypt(const QString &strPlainData, const QString &strPubKey);

    QString rsaPriDecrypt(const QString &strDecryptData, const QString &strPriKey);
};

#endif // RSA_H