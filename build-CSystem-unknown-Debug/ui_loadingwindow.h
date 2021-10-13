/********************************************************************************
** Form generated from reading UI file 'loadingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADINGWINDOW_H
#define UI_LOADINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loadingwindow
{
public:
    QLabel *label;
    QListView *listView;

    void setupUi(QWidget *loadingwindow)
    {
        if (loadingwindow->objectName().isEmpty())
            loadingwindow->setObjectName(QString::fromUtf8("loadingwindow"));
        loadingwindow->resize(640, 480);
        label = new QLabel(loadingwindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 40, 201, 81));
        QFont font;
        font.setPointSize(26);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setScaledContents(false);
        listView = new QListView(loadingwindow);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(40, 150, 291, 271));

        retranslateUi(loadingwindow);

        QMetaObject::connectSlotsByName(loadingwindow);
    } // setupUi

    void retranslateUi(QWidget *loadingwindow)
    {
        loadingwindow->setWindowTitle(QCoreApplication::translate("loadingwindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("loadingwindow", "Welcome", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loadingwindow: public Ui_loadingwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADINGWINDOW_H
