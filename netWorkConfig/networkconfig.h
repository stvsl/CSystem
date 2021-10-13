#ifndef NETWORKCONFIG_H
#define NETWORKCONFIG_H

#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class networkconfig; }
QT_END_NAMESPACE

class networkconfig : public QDialog
{
  Q_OBJECT

public:
    networkconfig(QWidget *parent = nullptr);
    ~networkconfig();

private slots:

  //和服务器连接成功时执行的槽函数
  void onConnected();
  //和服务器断开连接时执行的槽函数
  void onDisconnected();
  //接受服务器转发的消息的槽函数
  void onReadyRead();
  //网络异常时执行的槽函数
  void onError();

private:
  void send(QString str);

private:

  //通信套接字
  QTcpSocket socket;
  //服务器IP地址
  QHostAddress serverIP;
  //服务器端口
  quint16 serverPort;
  //客户端名称
  QString clientname;

};

#endif // NETWORKCONFIG_H
