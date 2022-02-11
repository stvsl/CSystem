#include "rsa.h"

rsa::rsa()
{
}

rsa::~rsa()
{
}
// 使用openssl生成公钥和私钥字符串
void RSAmake(){
    RSA * rsa = RSA_new();
    BIGNUM * bn = BN_new();
    BN_set_word(bn, RSA_F4);
    RSA_generate_key_ex(rsa, KEY_LENGTH, bn, NULL);
    // 生成公钥
    BIO * bio_pub = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(bio_pub, rsa);
    char * pub_key = NULL;
    long len = BIO_get_mem_data(bio_pub, &pub_key);
    QString pub_key_str = QString(pub_key);
    CONFIG_CORE::RSA_PUBLIC_KEY = pub_key_str;
    // 生成私钥
    BIO * bio_pri = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio_pri, rsa, NULL, NULL, 0, NULL, NULL);
    char * pri_key = NULL;
    long len2 = BIO_get_mem_data(bio_pri, &pri_key);
    QString pri_key_str = QString(pri_key);
    CONFIG_CORE::RSA_PRIVATE_KEY = pri_key_str;
}


QString rsa::rsaPubEncrypt(const QString &strPlainData, const QString &strPubKey)
{
    QByteArray pubKeyArry = strPubKey.toUtf8();
    uchar *pPubKey = (uchar *)pubKeyArry.data();
    BIO *pKeyBio = BIO_new_mem_buf(pPubKey, pubKeyArry.length());
    if (pKeyBio == NULL)
    {
        return "";
    }

    RSA *pRsa = RSA_new();
    if (strPubKey.contains(BEGIN_RSA_PUBLIC_KEY))
    {
        pRsa = PEM_read_bio_RSAPublicKey(pKeyBio, &pRsa, NULL, NULL);
    }
    else
    {
        pRsa = PEM_read_bio_RSA_PUBKEY(pKeyBio, &pRsa, NULL, NULL);
    }

    if (pRsa == NULL)
    {
        BIO_free_all(pKeyBio);
        return "";
    }

    int nLen = RSA_size(pRsa);
    char *pEncryptBuf = new char[nLen];

    //加密
    QByteArray plainDataArry = strPlainData.toUtf8();
    int nPlainDataLen = plainDataArry.length();

    int exppadding = nLen;
    if (nPlainDataLen > exppadding - 11)
        exppadding = exppadding - 11;
    int slice = nPlainDataLen / exppadding; //片数
    if (nPlainDataLen % (exppadding))
        slice++;

    QString strEncryptData = "";
    QByteArray arry;
    for (int i = 0; i < slice; i++)
    {
        QByteArray baData = plainDataArry.mid(i * exppadding, exppadding);
        nPlainDataLen = baData.length();
        memset(pEncryptBuf, 0, nLen);
        uchar *pPlainData = (uchar *)baData.data();
        int nSize = RSA_public_encrypt(nPlainDataLen,
                                       pPlainData,
                                       (uchar *)pEncryptBuf,
                                       pRsa,
                                       RSA_PKCS1_PADDING);
        if (nSize >= 0)
        {
            arry.append(QByteArray(pEncryptBuf, nSize));
        }
    }

    strEncryptData += arry.toBase64();
    //释放内存
    delete pEncryptBuf;
    BIO_free_all(pKeyBio);
    RSA_free(pRsa);
    return strEncryptData;
}

QString rsa::rsaPriDecrypt(const QString &strDecryptData, const QString &strPriKey)
{
    QByteArray priKeyArry = strPriKey.toUtf8();
    uchar *pPriKey = (uchar *)priKeyArry.data();
    BIO *pKeyBio = BIO_new_mem_buf(pPriKey, priKeyArry.length());
    if (pKeyBio == NULL)
    {
        return "";
    }

    RSA *pRsa = RSA_new();
    pRsa = PEM_read_bio_RSAPrivateKey(pKeyBio, &pRsa, NULL, NULL);
    if (pRsa == NULL)
    {
        BIO_free_all(pKeyBio);
        return "";
    }

    int nLen = RSA_size(pRsa);
    char *pPlainBuf = new char[nLen];

    //解密
    QByteArray decryptDataArry = strDecryptData.toUtf8();
    decryptDataArry = QByteArray::fromBase64(decryptDataArry);
    int nDecryptDataLen = decryptDataArry.length();

    int rsasize = nLen;
    int slice = nDecryptDataLen / rsasize; //片数
    if (nDecryptDataLen % (rsasize))
        slice++;

    QString strPlainData = "";
    for (int i = 0; i < slice; i++)
    {
        QByteArray baData = decryptDataArry.mid(i * rsasize, rsasize);
        nDecryptDataLen = baData.length();
        memset(pPlainBuf, 0, nLen);
        uchar *pDecryptData = (uchar *)baData.data();
        int nSize = RSA_private_decrypt(nDecryptDataLen,
                                        pDecryptData,
                                        (uchar *)pPlainBuf,
                                        pRsa,
                                        RSA_PKCS1_PADDING);
        if (nSize >= 0)
        {
            strPlainData += QByteArray(pPlainBuf, nSize);
        }
    }

    //释放内存
    delete pPlainBuf;
    BIO_free_all(pKeyBio);
    RSA_free(pRsa);
    return strPlainData;
}