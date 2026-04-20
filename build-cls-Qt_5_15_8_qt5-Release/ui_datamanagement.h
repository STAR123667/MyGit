/********************************************************************************
** Form generated from reading UI file 'datamanagement.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAMANAGEMENT_H
#define UI_DATAMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_datamanagement
{
public:
    QFrame *frame;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QTableWidget *tableWidget;
    QWidget *page_2;
    QLabel *label_2;

    void setupUi(QWidget *datamanagement)
    {
        if (datamanagement->objectName().isEmpty())
            datamanagement->setObjectName(QString::fromUtf8("datamanagement"));
        datamanagement->resize(1766, 920);
        frame = new QFrame(datamanagement);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(5, 15, 1755, 880));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton_1 = new QPushButton(frame);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setGeometry(QRect(45, 30, 80, 26));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(130, 30, 80, 26));
        stackedWidget = new QStackedWidget(frame);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 75, 1736, 791));
        stackedWidget->setFrameShape(QFrame::NoFrame);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        tableWidget = new QTableWidget(page);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget->rowCount() < 50)
            tableWidget->setRowCount(50);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem7);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(15, 10, 1721, 771));
        tableWidget->setRowCount(50);
        tableWidget->setColumnCount(6);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        label_2 = new QLabel(page_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(780, 355, 55, 18));
        stackedWidget->addWidget(page_2);

        retranslateUi(datamanagement);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(datamanagement);
    } // setupUi

    void retranslateUi(QWidget *datamanagement)
    {
        datamanagement->setWindowTitle(QCoreApplication::translate("datamanagement", "Form", nullptr));
        pushButton_1->setText(QCoreApplication::translate("datamanagement", "\347\224\237\344\272\247\346\225\260\346\215\256", nullptr));
        pushButton_2->setText(QCoreApplication::translate("datamanagement", "\346\212\245\350\255\246\346\225\260\346\215\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("datamanagement", "\346\223\215\344\275\234\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("datamanagement", "\346\225\260\346\215\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("datamanagement", "\346\234\200\345\244\247\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("datamanagement", "\346\234\200\345\260\217\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("datamanagement", "COV", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("datamanagement", "CPK", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(0, 0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("datamanagement", "2025-11-17", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        label_2->setText(QCoreApplication::translate("datamanagement", "\346\212\245\350\255\246\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class datamanagement: public Ui_datamanagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAMANAGEMENT_H
