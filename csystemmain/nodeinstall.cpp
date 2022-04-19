#include "nodeinstall.h"
#include "ui_nodeinstall.h"
#include "csystemmain/csystemmain.h"
#include <QStringListModel>
#include <QGraphicsDropShadowEffect>
#include <QWebChannel>

QGraphicsDropShadowEffect *nodeinsdallshadow;
QWebChannel *nodeinstallchannel;

QString temp;
float temp_x;
float temp_y;

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
    ui->webView->page()->setUrl(QUrl("http://127.0.0.1:10241/pages/config/map"));
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

void NodeInstall::on_NodeList_clicked(const QModelIndex &index)
{
    QString nodeid = ui->NodeList->model()->data(index).toString();
    // 获取当前结点的信息
    for (int i = 0; i < CSystemMain::nodeInfoList->size(); i++)
    {
        if (CSystemMain::nodeInfoList->at(i).id == nodeid)
        {
            switch (CSystemMain::nodeInfoList->at(i).type)
            {
            case 0:
                ui->type_normal->setChecked(true);
                break;
            case 1:
                ui->type_iron->setChecked(true);
                break;
            case 2:
                ui->type_pg->setChecked(true);
                break;
            case 3:
                ui->type_lm->setChecked(true);
                break;
            case 4:
                ui->type_js->setChecked(true);
                break;
            default:
                break;
            }
            ui->belong->setText(CSystemMain::nodeInfoList->at(i).belong);
            ui->installer->setText(CSystemMain::nodeInfoList->at(i).installer);
            ui->responser->setText(CSystemMain::nodeInfoList->at(i).principal);
            ui->maintainer->setText(CSystemMain::nodeInfoList->at(i).maintainer);
            if (CSystemMain::nodeInfoList->at(i).selfInfo == "")
            {
                ui->enableSelfCheck->setChecked(false);
            }
            else
            {
                ui->enableSelfCheck->setChecked(true);
            }
            ui->sendCheckRequest->setDisabled(true);
            ui->selfCheckCycle->setDisabled(true);
            ui->remark->setText(CSystemMain::nodeInfoList->at(i).remark);
            emit setCenter(CSystemMain::nodeInfoList->at(i).lo, CSystemMain::nodeInfoList->at(i).li);
            emit addPoint("", CSystemMain::nodeInfoList->at(i).lo, CSystemMain::nodeInfoList->at(i).li, "");
            // 按位解析配置字符串
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(0) == '1') // 特殊气体
            {
                ui->GasAuto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(0) == '0')
            {
                ui->Gas_Do->setChecked(true);
            }
            else
            {
                ui->Gas_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(1) == '1') // 温度
            {
                ui->Tem_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(1) == '0')
            {
                ui->Tem_Do->setChecked(true);
            }
            else
            {
                ui->Tem_ALL->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(2) == '1') // PH
            {
                ui->ph_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(2) == '0')
            {
                ui->ph_Do->setChecked(true);
            }
            else
            {
                ui->ph_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(3) == '1') //浑浊度
            {
                ui->den_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(3) == '0')
            {
                ui->den_Do->setChecked(true);
            }
            else
            {
                ui->den_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(4) == '1') //电导率
            {
                ui->con_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(4) == '0')
            {
                ui->con_Do->setChecked(true);
            }
            else
            {
                ui->con_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(5) == '1') //溶解氧
            {
                ui->oxy_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(5) == '0')
            {
                ui->oxy_Do->setChecked(true);
            }
            else
            {
                ui->oxy_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(6) == '1') //重金属
            {
                ui->met_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(6) == '0')
            {
                ui->met_Do->setChecked(true);
            }
            else
            {
                ui->met_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(7) == '1') //溶解性固体
            {
                ui->dso_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(7) == '0')
            {
                ui->dso_Do->setChecked(true);
            }
            else
            {
                ui->dso_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(8) == '1') // 悬浮性固体
            {
                ui->fso_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(8) == '0')
            {
                ui->fso_Do->setChecked(true);
            }
            else
            {
                ui->fso_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(9) == '1') // 总氮
            {
                ui->tn_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(9) == '0')
            {
                ui->tn_Do->setChecked(true);
            }
            else
            {
                ui->tn_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(10) == '1') // 总磷
            {
                ui->tp_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(10) == '0')
            {
                ui->tp_Do->setChecked(true);
            }
            else
            {
                ui->tp_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(11) == '1') //总有机碳
            {
                ui->oc_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(11) == '0')
            {
                ui->oc_Do->setChecked(true);
            }
            else
            {
                ui->oc_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(12) == '1') // 生物需氧量
            {
                ui->bod_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(12) == '0')
            {
                ui->bod_Do->setChecked(true);
            }
            else
            {
                ui->bod_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(13) == '1') // 化学需氧量
            {
                ui->cod_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(13) == '0')
            {
                ui->cod_Do->setChecked(true);
            }
            else
            {
                ui->cod_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(14) == '1') // 细菌总数
            {
                ui->tnb_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(14) == '0')
            {
                ui->tnb_Do->setChecked(true);
            }
            else
            {
                ui->tnb_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(15) == '1') // 大肠杆菌
            {
                ui->ec_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(15) == '0')
            {
                ui->ec_Do->setChecked(true);
            }
            else
            {
                ui->ec_All->setChecked(true);
            }
            ui->nodeLocate->setText(CSystemMain::nodeInfoList->at(i).locate);
            temp = CSystemMain::nodeInfoList->at(i).dataConfig;
            break;
        }
    }
}

void NodeInstall::on_node_Search_editingFinished()
{
    // 搜索节点
    QString nodeID = ui->node_Search->text();
    if (nodeID.isEmpty())
    {
        ui->node_Search->setText("未输入ID");
        QTimer::singleShot(1000, this, [=]()
                           { ui->node_Search->clear(); });
        return;
    }
    for (int i = 0; i < CSystemMain::nodeInfoList->size(); i++)
    {
        if (CSystemMain::nodeInfoList->at(i).id == nodeID)
        {
            // 点击节点列表的对应节点
            ui->NodeList->setCurrentIndex(ui->NodeList->model()->index(i, 0));
            on_NodeList_clicked(ui->NodeList->model()->index(i, 0));
            ui->node_Search->setText("查找成功");
            QTimer::singleShot(1000, this, [=]()
                               { ui->node_Search->clear(); });
            return;
        }
    }
    ui->node_Search->setText("查找失败");
    QTimer::singleShot(1000, this, [=]()
                       { ui->node_Search->clear(); });
}

void NodeInstall::on_addNode_clicked()
{
}

void NodeInstall::on_removeNode_clicked()
{
}

void NodeInstall::on_typr_normal_toggled(bool checked)
{
}

void NodeInstall::on_type_iron_toggled(bool checked)
{
}

void NodeInstall::on_type_pg_toggled(bool checked)
{
}

void NodeInstall::on_type_lm_toggled(bool checked)
{
}

void NodeInstall::on_type_js_toggled(bool checked)
{
}

void NodeInstall::on_enableSelfCheck_stateChanged(int arg1)
{
}

void NodeInstall::on_sendCheckRequest_stateChanged(int arg1)
{
}

void NodeInstall::on_selfCheckCycle_valueChanged(int arg1)
{
}

void NodeInstall::on_GasAuto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(0, 1, '1');
    }
}

void NodeInstall::on_Gas_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(0, 1, '0');
    }
}

void NodeInstall::on_Gas_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(0, 1, '2');
    }
}

void NodeInstall::on_Tem_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(1, 1, '1');
    }
}

void NodeInstall::on_Tem_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(1, 1, '0');
    }
}

void NodeInstall::on_Tem_ALL_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(1, 1, '2');
    }
}

void NodeInstall::on_ph_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(2, 1, '1');
    }
}

void NodeInstall::on_ph_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(2, 1, '0');
    }
}

void NodeInstall::on_ph_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(2, 1, '2');
    }
}

void NodeInstall::on_den_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(3, 1, '1');
    }
}

void NodeInstall::on_den_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(3, 1, '0');
    }
}

void NodeInstall::on_den_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(3, 1, '2');
    }
}

void NodeInstall::on_con_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(4, 1, '1');
    }
}

void NodeInstall::on_con_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(4, 1, '0');
    }
}

void NodeInstall::on_con_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(4, 1, '2');
    }
}

void NodeInstall::on_oxy_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(5, 1, '1');
    }
}

void NodeInstall::on_oxy_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(5, 1, '0');
    }
}

void NodeInstall::on_oxy_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(5, 1, '2');
    }
}

void NodeInstall::on_met_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(6, 1, '1');
    }
}

void NodeInstall::on_met_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(6, 1, '0');
    }
}

void NodeInstall::on_met_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(6, 1, '2');
    }
}

void NodeInstall::on_dso_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(7, 1, '1');
    }
}

void NodeInstall::on_dso_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(7, 1, '0');
    }
}

void NodeInstall::on_dso_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(7, 1, '2');
    }
}

void NodeInstall::on_fso_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(8, 1, '1');
    }
}

void NodeInstall::on_fso_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(8, 1, '0');
    }
}

void NodeInstall::on_fso_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(8, 1, '2');
    }
}

void NodeInstall::on_tn_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(9, 1, '1');
    }
}

void NodeInstall::on_tn_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(9, 1, '0');
    }
}

void NodeInstall::on_tn_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(9, 1, '2');
    }
}

void NodeInstall::on_tp_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(10, 1, '1');
    }
}

void NodeInstall::on_tp_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(10, 1, '0');
    }
}

void NodeInstall::on_tp_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(10, 1, '2');
    }
}

void NodeInstall::on_oc_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(11, 1, '1');
    }
}

void NodeInstall::on_oc_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(11, 1, '0');
    }
}

void NodeInstall::on_oc_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(11, 1, '2');
    }
}

void NodeInstall::on_bod_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(12, 1, '1');
    }
}

void NodeInstall::on_bod_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(12, 1, '0');
    }
}

void NodeInstall::on_bod_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(12, 1, '2');
    }
}

void NodeInstall::on_cod_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(13, 1, '1');
    }
}

void NodeInstall::on_cod_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(13, 1, '0');
    }
}

void NodeInstall::on_cod_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(13, 1, '2');
    }
}

void NodeInstall::on_tnb_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(14, 1, '1');
    }
}

void NodeInstall::on_tnb_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(14, 1, '0');
    }
}

void NodeInstall::on_tnb_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(14, 1, '2');
    }
}

void NodeInstall::on_ec_Auto_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(15, 1, '1');
    }
}

void NodeInstall::on_ec_Do_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(15, 1, '0');
    }
}

void NodeInstall::on_ec_All_toggled(bool checked)
{
    if (checked)
    {
        temp.replace(15, 1, '2');
    }
}

void NodeInstall::on_OK_btn_clicked()
{
    // 获取当前选中的节点为第几个
    int index = ui->NodeList->currentIndex().row();
    // 生成新的节点信息
    NodeInfo node = CSystemMain::nodeInfoList->at(index);
    // 判断节点类型按钮哪个被选中
    if (ui->type_normal->isChecked())
    {
        node.type = 0;
    }
    else if (ui->type_iron->isChecked())
    {
        node.type = 1;
    }
    else if (ui->type_pg->isChecked())
    {
        node.type = 2;
    }
    else if (ui->type_lm->isChecked())
    {
        node.type = 3;
    }
    else if (ui->type_js->isChecked())
    {
        node.type = 4;
    }
    node.belong = ui->belong->text();
    node.principal = ui->responser->text();
    node.installer = ui->installer->text();
    node.maintainer = ui->maintainer->text();
    node.selfInfo = ui->enableSelfCheck->isChecked();
    node.remark = ui->remark->toPlainText();
    node.dataConfig = temp;
    node.locate = ui->nodeLocate->text();
    node.lo = temp_x;
    node.li = temp_y;
    CSystemMain::nodeInfoList->replace(index, node);
}

void NodeInstall::on_recover_btn_clicked()
{
    // 获取当前NodeList被点击的结点编号
    QString nodeid = ui->NodeList->model()->data(ui->NodeList->currentIndex()).toString();
    // 获取当前结点的信息
    for (int i = 0; i < CSystemMain::nodeInfoList->size(); i++)
    {
        if (CSystemMain::nodeInfoList->at(i).id == nodeid)
        {
            switch (CSystemMain::nodeInfoList->at(i).type)
            {
            case 0:
                ui->type_normal->setChecked(true);
                break;
            case 1:
                ui->type_iron->setChecked(true);
                break;
            case 2:
                ui->type_pg->setChecked(true);
                break;
            case 3:
                ui->type_lm->setChecked(true);
                break;
            case 4:
                ui->type_js->setChecked(true);
                break;
            default:
                break;
            }
            ui->belong->setText(CSystemMain::nodeInfoList->at(i).belong);
            ui->installer->setText(CSystemMain::nodeInfoList->at(i).installer);
            ui->responser->setText(CSystemMain::nodeInfoList->at(i).principal);
            ui->maintainer->setText(CSystemMain::nodeInfoList->at(i).maintainer);
            if (CSystemMain::nodeInfoList->at(i).selfInfo == "")
            {
                ui->enableSelfCheck->setChecked(false);
            }
            else
            {
                ui->enableSelfCheck->setChecked(true);
            }
            ui->sendCheckRequest->setDisabled(true);
            ui->selfCheckCycle->setDisabled(true);
            ui->remark->setText(CSystemMain::nodeInfoList->at(i).remark);
            emit setCenter(CSystemMain::nodeInfoList->at(i).lo, CSystemMain::nodeInfoList->at(i).li);
            emit addPoint("", CSystemMain::nodeInfoList->at(i).lo, CSystemMain::nodeInfoList->at(i).li, "");
            // 按位解析配置字符串
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(0) == '1') // 特殊气体
            {
                ui->GasAuto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(0) == '0')
            {
                ui->Gas_Do->setChecked(true);
            }
            else
            {
                ui->Gas_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(1) == '1') // 温度
            {
                ui->Tem_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(1) == '0')
            {
                ui->Tem_Do->setChecked(true);
            }
            else
            {
                ui->Tem_ALL->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(2) == '1') // PH
            {
                ui->ph_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(2) == '0')
            {
                ui->ph_Do->setChecked(true);
            }
            else
            {
                ui->ph_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(3) == '1') //浑浊度
            {
                ui->den_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(3) == '0')
            {
                ui->den_Do->setChecked(true);
            }
            else
            {
                ui->den_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(4) == '1') //电导率
            {
                ui->con_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(4) == '0')
            {
                ui->con_Do->setChecked(true);
            }
            else
            {
                ui->con_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(5) == '1') //溶解氧
            {
                ui->oxy_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(5) == '0')
            {
                ui->oxy_Do->setChecked(true);
            }
            else
            {
                ui->oxy_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(6) == '1') //重金属
            {
                ui->met_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(6) == '0')
            {
                ui->met_Do->setChecked(true);
            }
            else
            {
                ui->met_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(7) == '1') //溶解性固体
            {
                ui->dso_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(7) == '0')
            {
                ui->dso_Do->setChecked(true);
            }
            else
            {
                ui->dso_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(8) == '1') // 悬浮性固体
            {
                ui->fso_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(8) == '0')
            {
                ui->fso_Do->setChecked(true);
            }
            else
            {
                ui->fso_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(9) == '1') // 总氮
            {
                ui->tn_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(9) == '0')
            {
                ui->tn_Do->setChecked(true);
            }
            else
            {
                ui->tn_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(10) == '1') // 总磷
            {
                ui->tp_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(10) == '0')
            {
                ui->tp_Do->setChecked(true);
            }
            else
            {
                ui->tp_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(11) == '1') //总有机碳
            {
                ui->oc_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(11) == '0')
            {
                ui->oc_Do->setChecked(true);
            }
            else
            {
                ui->oc_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(12) == '1') // 生物需氧量
            {
                ui->bod_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(12) == '0')
            {
                ui->bod_Do->setChecked(true);
            }
            else
            {
                ui->bod_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(13) == '1') // 化学需氧量
            {
                ui->cod_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(13) == '0')
            {
                ui->cod_Do->setChecked(true);
            }
            else
            {
                ui->cod_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(14) == '1') // 细菌总数
            {
                ui->tnb_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(14) == '0')
            {
                ui->tnb_Do->setChecked(true);
            }
            else
            {
                ui->tnb_All->setChecked(true);
            }
            if (CSystemMain::nodeInfoList->at(i).dataConfig.at(15) == '1') // 大肠杆菌
            {
                ui->ec_Auto->setChecked(true);
            }
            else if (CSystemMain::nodeInfoList->at(i).dataConfig.at(15) == '0')
            {
                ui->ec_Do->setChecked(true);
            }
            else
            {
                ui->ec_All->setChecked(true);
            }
            ui->nodeLocate->setText(CSystemMain::nodeInfoList->at(i).locate);
            temp = CSystemMain::nodeInfoList->at(i).dataConfig;
        }
    }
}

void NodeInstall::receiveLocateInfo(QString info, float x, float y)
{
    ui->nodeLocate->setText(info);
    temp_x = x;
    temp_y = y;
}
void NodeInstall::on_locateChangeByMap_clicked()
{
    ui->webView->page()->runJavaScript("enableLinstener();");
}

void NodeInstall::on_locateChangeByHand_clicked()
{
    emit searchP(ui->nodeLocate->text());
}
