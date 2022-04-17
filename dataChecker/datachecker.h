#ifndef DATACHECKER_H
#define DATACHECKER_H

#include <QObject>
#include "cacheManager/CacheManager.h"

class dataChecker : public QObject
{
    Q_OBJECT
public:
    explicit dataChecker(QObject *parent = nullptr);
    ~dataChecker();

signals:
    QString findWarning();
    QString findError();
    QString findInfo();

public slots:
    void checkData();
};

#endif // DATACHECKER_H
