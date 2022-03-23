#ifndef NODEINTERFACE_H
#define NODEINTERFACE_H

#include <QObject>
#include <netWorkUtils/netWorkUtils.h>

class NodeInterface : public QObject
{
    Q_OBJECT

signals:
    void netError(QString err);

public slots:
    void onnetError(QString err);

public:
    NodeInterface();
    // 获取最新的结点信息
    QVector<NodeInfo> *getNodeInfo();
    // 获取结点当前详情
    QVector<NodeData> *getNodeData();
};

#endif // NODEINTERFACE_H
