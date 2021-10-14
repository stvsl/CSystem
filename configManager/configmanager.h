#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QSettings>

class configManager : public QObject
{
    Q_OBJECT
public:
    explicit configManager(QObject *parent = nullptr);

signals:

private:
    //配置读取
    void reader();
    //配置写入
    void writer();

private:
    QString inipath = "./config/config.data";
    QSettings settings;
};

#endif // CONFIGMANAGER_H
