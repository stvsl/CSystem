/********************************************************************************
** Form generated from reading UI file 'csystemmain.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSYSTEMMAIN_H
#define UI_CSYSTEMMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CSystemMain
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CSystemMain)
    {
        if (CSystemMain->objectName().isEmpty())
            CSystemMain->setObjectName(QString::fromUtf8("CSystemMain"));
        CSystemMain->resize(800, 600);
        menubar = new QMenuBar(CSystemMain);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        CSystemMain->setMenuBar(menubar);
        centralwidget = new QWidget(CSystemMain);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        CSystemMain->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(CSystemMain);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CSystemMain->setStatusBar(statusbar);

        retranslateUi(CSystemMain);

        QMetaObject::connectSlotsByName(CSystemMain);
    } // setupUi

    void retranslateUi(QMainWindow *CSystemMain)
    {
        CSystemMain->setWindowTitle(QCoreApplication::translate("CSystemMain", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CSystemMain: public Ui_CSystemMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSYSTEMMAIN_H
