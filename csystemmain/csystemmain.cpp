#include "csystemmain.h"
#include "ui_csystemmain.h"

CSystemMain::CSystemMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSystemMain)
{
    ui->setupUi(this);
}

CSystemMain::~CSystemMain()
{
    delete ui;
}
