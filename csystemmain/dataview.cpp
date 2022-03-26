#include "dataview.h"
#include "ui_dataview.h"
#include <QGraphicsDropShadowEffect>

DataView::DataView(QWidget *parent) : QWidget(parent),
                                      ui(new Ui::DataView)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    // 阴影效果
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(ui->tableWidget);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(0, 0, 0, 100));
    shadow_effect->setBlurRadius(10);
    ui->tableWidget->setGraphicsEffect(shadow_effect);
}

DataView::~DataView()
{
    delete ui;
}
