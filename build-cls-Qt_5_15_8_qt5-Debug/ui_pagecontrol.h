/********************************************************************************
** Form generated from reading UI file 'pagecontrol.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGECONTROL_H
#define UI_PAGECONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageControl
{
public:
    QFrame *frame;

    void setupUi(QWidget *PageControl)
    {
        if (PageControl->objectName().isEmpty())
            PageControl->setObjectName(QString::fromUtf8("PageControl"));
        PageControl->setWindowModality(Qt::NonModal);
        PageControl->setEnabled(true);
        PageControl->resize(1766, 920);
        PageControl->setFocusPolicy(Qt::NoFocus);
        PageControl->setContextMenuPolicy(Qt::NoContextMenu);
        PageControl->setAcceptDrops(false);
        PageControl->setAutoFillBackground(false);
        frame = new QFrame(PageControl);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(5, 15, 1755, 880));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        retranslateUi(PageControl);

        QMetaObject::connectSlotsByName(PageControl);
    } // setupUi

    void retranslateUi(QWidget *PageControl)
    {
        PageControl->setWindowTitle(QCoreApplication::translate("PageControl", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageControl: public Ui_PageControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGECONTROL_H
