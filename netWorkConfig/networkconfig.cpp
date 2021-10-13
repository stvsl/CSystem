#include "networkconfig.h"

//构造函数
networkconfig::networkconfig(QWidget *parent)
    :QDialog(parent)
    ,ui(new Ui::networkconfig)
{
  /*绑定信号和槽连接*/
  //建立连接槽函数
  connect(&socket,SIGNAL(connected()),this,SLOT(onConnected()));
  //断开连接槽函数
  connect(&socket,SIGNAL(disconnected()),this,SLOT(onDisconnected()));
  //表示接收消息的槽函数
  connect(&socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
  //处理网络异常的槽函数
  connect(&socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onError()));

  /*网络收发系统绑定与连接*/
  serverIP.setAddress("127.0.0.1");
  serverPort = 8080;
  //获取客户端名称
  clientname = "test";
  //发送连接请求
  socket.connectToHost(serverIP,serverPort);
}

void networkconfig::onConnected()
{
    socket.write("connect from ???");
}

void networkconfig::send(QString str)
{
    socket.write(str.toUtf8());
}
