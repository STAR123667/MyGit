/********************************************************************************
** Form generated from reading UI file 'workmanagement.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKMANAGEMENT_H
#define UI_WORKMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_workmanagement
{
public:
    QFrame *frame;

    void setupUi(QWidget *workmanagement)
    {
        if (workmanagement->objectName().isEmpty())
            workmanagement->setObjectName(QString::fromUtf8("workmanagement"));
        workmanagement->resize(1766, 920);
        frame = new QFrame(workmanagement);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(5, 15, 1755, 880));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        retranslateUi(workmanagement);

        QMetaObject::connectSlotsByName(workmanagement);
    } // setupUi

    void retranslateUi(QWidget *workmanagement)
    {
        workmanagement->setWindowTitle(QCoreApplication::translate("workmanagement", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class workmanagement: public Ui_workmanagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKMANAGEMENT_H
