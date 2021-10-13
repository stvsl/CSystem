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

class Ui_CSystemMainWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CSystemMainWindow)
    {
        if (CSystemMainWindow->objectName().isEmpty())
            CSystemMainWindow->setObjectName(QString::fromUtf8("CSystemMainWindow"));
        CSystemMainWindow->resize(800, 600);
        centralwidget = new QWidget(CSystemMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        CSystemMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CSystemMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        CSystemMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CSystemMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CSystemMainWindow->setStatusBar(statusbar);

        retranslateUi(CSystemMainWindow);

        QMetaObject::connectSlotsByName(CSystemMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CSystemMainWindow)
    {
        CSystemMainWindow->setWindowTitle(QCoreApplication::translate("CSystemMainWindow", "CSystemMainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CSystemMainWindow: public Ui_CSystemMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSYSTEMMAIN_H
