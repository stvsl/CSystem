#ifndef NODEINTERFACE_H
#define NODEINTERFACE_H

#include <QObject>
#include <netWorkUtils/netWorkUtils.h>

class NodeInterface : public QObject
{
    Q_OBJECT

signals:
    void netError(QString err);

public:
    NodeInterface(QVector<NodeInfo> *nodeInfoList);

    // 获取最新的结点信息
    void getNodeInfo();

private:
    QVector<NodeInfo> *nodeInfoList; // 节点数据缓存附指针
};

#endif // NODEINTERFACE_H
