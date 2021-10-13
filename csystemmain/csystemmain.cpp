#include "csystemmain.h"
#include "ui_csystemmainwindow.h"

CSystemMainWindow::CSystemMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CSystemMainWindow)
{
    ui->setupUi(this);
}

CSystemMainWindow::~CSystemMainWindow()
{
    delete ui;
}

