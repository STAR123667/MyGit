/********************************************************************************
** Form generated from reading UI file 'pagewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEWIDGET_H
#define UI_PAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PageWidget
{
public:
    QLabel *leftSeparateLabel;
    QLabel *rightSeparatelabel;
    QSpinBox *spinBox;
    QLineEdit *pageLineEdit;

    void setupUi(QWidget *PageWidget)
    {
        if (PageWidget->objectName().isEmpty())
            PageWidget->setObjectName(QString::fromUtf8("PageWidget"));
        PageWidget->resize(1766, 920);
        leftSeparateLabel = new QLabel(PageWidget);
        leftSeparateLabel->setObjectName(QString::fromUtf8("leftSeparateLabel"));
        leftSeparateLabel->setGeometry(QRect(200, 310, 55, 18));
        rightSeparatelabel = new QLabel(PageWidget);
        rightSeparatelabel->setObjectName(QString::fromUtf8("rightSeparatelabel"));
        rightSeparatelabel->setGeometry(QRect(340, 310, 55, 18));
        spinBox = new QSpinBox(PageWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(230, 390, 311, 26));
        pageLineEdit = new QLineEdit(PageWidget);
        pageLineEdit->setObjectName(QString::fromUtf8("pageLineEdit"));
        pageLineEdit->setGeometry(QRect(300, 450, 113, 25));

        retranslateUi(PageWidget);

        QMetaObject::connectSlotsByName(PageWidget);
    } // setupUi

    void retranslateUi(QWidget *PageWidget)
    {
        PageWidget->setWindowTitle(QCoreApplication::translate("PageWidget", "Form", nullptr));
        leftSeparateLabel->setText(QCoreApplication::translate("PageWidget", "\345\267\246", nullptr));
        rightSeparatelabel->setText(QCoreApplication::translate("PageWidget", "\345\217\263", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PageWidget: public Ui_PageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEWIDGET_H
