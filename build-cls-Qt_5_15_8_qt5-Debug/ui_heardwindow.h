/********************************************************************************
** Form generated from reading UI file 'heardwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HEARDWINDOW_H
#define UI_HEARDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_heardWindow
{
public:
    QWidget *centralwidget;
    QFrame *heard_frame;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;

    void setupUi(QMainWindow *heardWindow)
    {
        if (heardWindow->objectName().isEmpty())
            heardWindow->setObjectName(QString::fromUtf8("heardWindow"));
        heardWindow->resize(1500, 1010);
        centralwidget = new QWidget(heardWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        heard_frame = new QFrame(centralwidget);
        heard_frame->setObjectName(QString::fromUtf8("heard_frame"));
        heard_frame->setGeometry(QRect(370, 3, 740, 50));
        heard_frame->setFrameShape(QFrame::StyledPanel);
        heard_frame->setFrameShadow(QFrame::Raised);
        radioButton_1 = new QRadioButton(heard_frame);
        radioButton_1->setObjectName(QString::fromUtf8("radioButton_1"));
        radioButton_1->setGeometry(QRect(30, 10, 57, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        font.setBold(false);
        radioButton_1->setFont(font);
        radioButton_1->setStyleSheet(QString::fromUtf8(""));
        radioButton_1->setChecked(true);
        radioButton_2 = new QRadioButton(heard_frame);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(100, 10, 91, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(12);
        radioButton_2->setFont(font1);
        radioButton_2->setStyleSheet(QString::fromUtf8(""));
        radioButton_3 = new QRadioButton(heard_frame);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(200, 10, 111, 30));
        radioButton_3->setFont(font1);
        radioButton_3->setLayoutDirection(Qt::LeftToRight);
        radioButton_3->setStyleSheet(QString::fromUtf8(""));
        radioButton_4 = new QRadioButton(heard_frame);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setGeometry(QRect(300, 10, 91, 30));
        radioButton_4->setFont(font1);
        radioButton_4->setStyleSheet(QString::fromUtf8(""));
        radioButton_5 = new QRadioButton(heard_frame);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setGeometry(QRect(400, 10, 91, 30));
        radioButton_5->setFont(font1);
        radioButton_5->setStyleSheet(QString::fromUtf8(""));
        radioButton_6 = new QRadioButton(heard_frame);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));
        radioButton_6->setGeometry(QRect(510, 10, 91, 30));
        radioButton_6->setFont(font1);
        radioButton_6->setStyleSheet(QString::fromUtf8(""));
        radioButton_7 = new QRadioButton(heard_frame);
        radioButton_7->setObjectName(QString::fromUtf8("radioButton_7"));
        radioButton_7->setGeometry(QRect(610, 10, 101, 30));
        radioButton_7->setFont(font1);
        radioButton_7->setStyleSheet(QString::fromUtf8(""));
        heardWindow->setCentralWidget(centralwidget);

        retranslateUi(heardWindow);

        QMetaObject::connectSlotsByName(heardWindow);
    } // setupUi

    void retranslateUi(QMainWindow *heardWindow)
    {
        heardWindow->setWindowTitle(QCoreApplication::translate("heardWindow", "MainWindow", nullptr));
        radioButton_1->setText(QCoreApplication::translate("heardWindow", "\351\246\226\351\241\265", nullptr));
        radioButton_2->setText(QCoreApplication::translate("heardWindow", "\346\211\213\345\212\250\346\223\215\344\275\234", nullptr));
        radioButton_3->setText(QCoreApplication::translate("heardWindow", "\351\205\215\347\275\256\347\256\241\347\220\206", nullptr));
        radioButton_4->setText(QCoreApplication::translate("heardWindow", "\346\225\260\346\215\256\347\256\241\347\220\206", nullptr));
        radioButton_5->setText(QCoreApplication::translate("heardWindow", "\347\263\273\347\273\237\347\256\241\347\220\206", nullptr));
        radioButton_6->setText(QCoreApplication::translate("heardWindow", "\346\225\260\346\215\256\351\235\242\346\235\277", nullptr));
        radioButton_7->setText(QCoreApplication::translate("heardWindow", "\344\275\234\344\270\232\347\256\241\347\220\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class heardWindow: public Ui_heardWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HEARDWINDOW_H
