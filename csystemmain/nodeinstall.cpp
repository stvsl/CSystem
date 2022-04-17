#include "nodeinstall.h"
#include "ui_nodeinstall.h"
#include "csystemmain/csystemmain.h"
#include <QStringListModel>
#include <QGraphicsDropShadowEffect>
#include <QWebChannel>

QGraphicsDropShadowEffect *nodeinsdallshadow;
QWebChannel *nodeinstallchannel;

NodeInstall::NodeInstall(QWidget *parent) : QWidget(parent),
                                            ui(new Ui::NodeInstall)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    QStringList nodelist;
    for (int i = 0; i < CSystemMain::nodeInfoList->size(); i++)
    {
        nodelist.append(CSystemMain::nodeInfoList->at(i).id);
    }
    ui->NodeList->setModel(new QStringListModel(nodelist));
    ui->webView->page()->setUrl(QUrl("http://127.0.0.1:10241/pages/default/map"));
    nodeinsdallshadow = new QGraphicsDropShadowEffect(ui->nodeinfogroup);
    nodeinsdallshadow->setBlurRadius(10);
    nodeinsdallshadow->setColor(QColor(125, 164, 255, 80));
    nodeinsdallshadow->setOffset(0, 0);
    ui->nodeinfogroup->setGraphicsEffect(nodeinsdallshadow);
    nodeinstallchannel = new QWebChannel(ui->webView->page());
    ui->webView->page()->setWebChannel(nodeinstallchannel);
    nodeinstallchannel->registerObject("trans", this);
    ui->webView->page()->setWebChannel(nodeinstallchannel);
}

NodeInstall::~NodeInstall()
{
    delete ui;
    delete nodeinsdallshadow;
}
