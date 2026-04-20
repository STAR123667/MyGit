/********************************************************************************
** Form generated from reading UI file 'manualwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALWINDOW_H
#define UI_MANUALWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_manualwindow
{
public:

    void setupUi(QWidget *manualwindow)
    {
        if (manualwindow->objectName().isEmpty())
            manualwindow->setObjectName(QString::fromUtf8("manualwindow"));
        manualwindow->resize(1518, 1010);

        retranslateUi(manualwindow);

        QMetaObject::connectSlotsByName(manualwindow);
    } // setupUi

    void retranslateUi(QWidget *manualwindow)
    {
        manualwindow->setWindowTitle(QCoreApplication::translate("manualwindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class manualwindow: public Ui_manualwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALWINDOW_H
