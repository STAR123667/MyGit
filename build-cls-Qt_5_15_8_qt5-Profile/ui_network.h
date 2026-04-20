/********************************************************************************
** Form generated from reading UI file 'network.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORK_H
#define UI_NETWORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_network
{
public:

    void setupUi(QWidget *network)
    {
        if (network->objectName().isEmpty())
            network->setObjectName(QString::fromUtf8("network"));
        network->resize(400, 300);

        retranslateUi(network);

        QMetaObject::connectSlotsByName(network);
    } // setupUi

    void retranslateUi(QWidget *network)
    {
        network->setWindowTitle(QCoreApplication::translate("network", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class network: public Ui_network {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORK_H
