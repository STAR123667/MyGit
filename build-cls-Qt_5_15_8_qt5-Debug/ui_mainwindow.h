/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *main;
    QFrame *frame_Tkuai;
    QLabel *label_7;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_5;
    QLabel *label_21;
    QSlider *T_OPEN;
    QLabel *label_start;
    QLabel *label_close;
    QFrame *frame_BenSu;
    QLabel *label_8;
    QLabel *label_22;
    QLabel *label_13;
    QLabel *label_23;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_24;
    QSlider *BS_OPEN;
    QLabel *label_close2;
    QLabel *label_start2;
    QFrame *frame_GAP;
    QLabel *label_9;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_25;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QSlider *CAP_OPEN;
    QLabel *label_close3;
    QLabel *label_start3;
    QFrame *frame_CCD;
    QLabel *label_ccd;
    QLabel *label_ccdState;
    QLabel *t_year_label;
    QLabel *t_date_label;
    QTabWidget *tabWidget;
    QWidget *tab_7;
    QWidget *tab_6;
    QWidget *tab_5;
    QWidget *tab_4;
    QWidget *tab_3;
    QWidget *tab_2;
    QWidget *tab;
    QLabel *label_30;
    QLabel *log_label;
    QFrame *frame;
    QLabel *label_CAN;
    QLabel *label_start_CAN;
    QLabel *label_close_CAN;
    QSlider *CAN_OPEN;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1780, 1010);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        main = new QWidget(MainWindow);
        main->setObjectName(QString::fromUtf8("main"));
        main->setCursor(QCursor(Qt::UpArrowCursor));
        frame_Tkuai = new QFrame(main);
        frame_Tkuai->setObjectName(QString::fromUtf8("frame_Tkuai"));
        frame_Tkuai->setGeometry(QRect(5, 940, 385, 66));
        frame_Tkuai->setFrameShape(QFrame::StyledPanel);
        frame_Tkuai->setFrameShadow(QFrame::Raised);
        label_7 = new QLabel(frame_Tkuai);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(70, 40, 46, 18));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(9);
        font.setItalic(false);
        label_7->setFont(font);
        label_11 = new QLabel(frame_Tkuai);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(180, 40, 55, 18));
        label_12 = new QLabel(frame_Tkuai);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(280, 40, 55, 18));
        label_5 = new QLabel(frame_Tkuai);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(195, 15, 16, 18));
        QFont font1;
        font1.setPointSize(10);
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        label_21 = new QLabel(frame_Tkuai);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(285, 15, 55, 18));
        label_21->setFont(font1);
        label_21->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        T_OPEN = new QSlider(frame_Tkuai);
        T_OPEN->setObjectName(QString::fromUtf8("T_OPEN"));
        T_OPEN->setGeometry(QRect(65, 15, 50, 20));
        T_OPEN->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"     border: none;\n"
"     background-color:  rgb(255,0,0);\n"
"    border-radius:  10px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"     width:  20px;\n"
"    height:  30px; \n"
"    background-color:  white;\n"
"    border-radius:10px; \n"
"}\n"
"QSlider:: handle:hover  {\n"
"        background-color:  white;\n"
"}\n"
"QSlider:: handle:checked  {\n"
"        background-color: blue;\n"
"}\n"
""));
        T_OPEN->setMaximum(1);
        T_OPEN->setSingleStep(0);
        T_OPEN->setOrientation(Qt::Horizontal);
        T_OPEN->setTickInterval(1);
        label_start = new QLabel(frame_Tkuai);
        label_start->setObjectName(QString::fromUtf8("label_start"));
        label_start->setGeometry(QRect(71, 14, 26, 21));
        QFont font2;
        font2.setPointSize(8);
        label_start->setFont(font2);
        label_start->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));
        label_close = new QLabel(frame_Tkuai);
        label_close->setObjectName(QString::fromUtf8("label_close"));
        label_close->setGeometry(QRect(87, 14, 26, 21));
        label_close->setFont(font2);
        label_close->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        frame_BenSu = new QFrame(main);
        frame_BenSu->setObjectName(QString::fromUtf8("frame_BenSu"));
        frame_BenSu->setGeometry(QRect(390, 940, 510, 66));
        frame_BenSu->setFrameShape(QFrame::StyledPanel);
        frame_BenSu->setFrameShadow(QFrame::Raised);
        label_8 = new QLabel(frame_BenSu);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(80, 40, 55, 18));
        label_22 = new QLabel(frame_BenSu);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(205, 15, 20, 21));
        label_22->setFont(font1);
        label_22->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        label_13 = new QLabel(frame_BenSu);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(190, 40, 55, 18));
        label_23 = new QLabel(frame_BenSu);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(300, 15, 21, 21));
        label_23->setFont(font1);
        label_23->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        label_14 = new QLabel(frame_BenSu);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(285, 40, 55, 18));
        label_15 = new QLabel(frame_BenSu);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(385, 40, 55, 18));
        label_24 = new QLabel(frame_BenSu);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(390, 15, 71, 21));
        label_24->setFont(font1);
        label_24->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        BS_OPEN = new QSlider(frame_BenSu);
        BS_OPEN->setObjectName(QString::fromUtf8("BS_OPEN"));
        BS_OPEN->setGeometry(QRect(80, 15, 50, 20));
        BS_OPEN->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"     border: none;\n"
"     background-color:  rgb(255,0,0);\n"
"    border-radius:   10px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"     width:  20px;\n"
"    height:  30px; \n"
"    background-color:  white;\n"
"    border-radius:10px; \n"
"}\n"
"QSlider:: handle:hover  {\n"
"        background-color:  white;\n"
"}\n"
"QSlider:: handle:checked  {\n"
"        background-color: blue;\n"
"}\n"
""));
        BS_OPEN->setMaximum(1);
        BS_OPEN->setSingleStep(0);
        BS_OPEN->setOrientation(Qt::Horizontal);
        BS_OPEN->setTickInterval(1);
        label_close2 = new QLabel(frame_BenSu);
        label_close2->setObjectName(QString::fromUtf8("label_close2"));
        label_close2->setGeometry(QRect(102, 14, 26, 21));
        label_close2->setFont(font2);
        label_close2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_start2 = new QLabel(frame_BenSu);
        label_start2->setObjectName(QString::fromUtf8("label_start2"));
        label_start2->setGeometry(QRect(86, 14, 26, 21));
        label_start2->setFont(font2);
        label_start2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        frame_GAP = new QFrame(main);
        frame_GAP->setObjectName(QString::fromUtf8("frame_GAP"));
        frame_GAP->setGeometry(QRect(900, 940, 540, 66));
        frame_GAP->setFrameShape(QFrame::StyledPanel);
        frame_GAP->setFrameShadow(QFrame::Raised);
        label_9 = new QLabel(frame_GAP);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(60, 40, 55, 18));
        label_16 = new QLabel(frame_GAP);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(150, 40, 81, 18));
        label_17 = new QLabel(frame_GAP);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(250, 40, 91, 18));
        label_19 = new QLabel(frame_GAP);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(350, 40, 81, 18));
        label_20 = new QLabel(frame_GAP);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(445, 40, 55, 18));
        label_25 = new QLabel(frame_GAP);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(180, 15, 21, 18));
        label_25->setFont(font1);
        label_25->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        label_27 = new QLabel(frame_GAP);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(280, 15, 21, 18));
        label_27->setFont(font1);
        label_27->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        label_28 = new QLabel(frame_GAP);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(380, 15, 16, 18));
        label_28->setFont(font1);
        label_28->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        label_29 = new QLabel(frame_GAP);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(450, 15, 55, 18));
        label_29->setFont(font1);
        label_29->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        CAP_OPEN = new QSlider(frame_GAP);
        CAP_OPEN->setObjectName(QString::fromUtf8("CAP_OPEN"));
        CAP_OPEN->setGeometry(QRect(60, 15, 50, 20));
        CAP_OPEN->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"     border: none;\n"
"     background-color:  rgb(255,0,0);\n"
"    border-radius:   10px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"     width:  20px;\n"
"    height:  30px; \n"
"    background-color:  white;\n"
"    border-radius:10px; \n"
"}\n"
"QSlider:: handle:hover  {\n"
"        background-color:  white;\n"
"}\n"
"QSlider:: handle:checked  {\n"
"        background-color: blue;\n"
"}\n"
""));
        CAP_OPEN->setMaximum(1);
        CAP_OPEN->setSingleStep(0);
        CAP_OPEN->setOrientation(Qt::Horizontal);
        CAP_OPEN->setTickInterval(1);
        label_close3 = new QLabel(frame_GAP);
        label_close3->setObjectName(QString::fromUtf8("label_close3"));
        label_close3->setGeometry(QRect(82, 14, 26, 21));
        label_close3->setFont(font2);
        label_close3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_start3 = new QLabel(frame_GAP);
        label_start3->setObjectName(QString::fromUtf8("label_start3"));
        label_start3->setGeometry(QRect(66, 14, 26, 21));
        label_start3->setFont(font2);
        label_start3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        frame_CCD = new QFrame(main);
        frame_CCD->setObjectName(QString::fromUtf8("frame_CCD"));
        frame_CCD->setGeometry(QRect(1440, 940, 125, 66));
        frame_CCD->setFrameShape(QFrame::StyledPanel);
        frame_CCD->setFrameShadow(QFrame::Raised);
        label_ccd = new QLabel(frame_CCD);
        label_ccd->setObjectName(QString::fromUtf8("label_ccd"));
        label_ccd->setGeometry(QRect(50, 40, 41, 20));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(12);
        label_ccd->setFont(font3);
        label_ccdState = new QLabel(frame_CCD);
        label_ccdState->setObjectName(QString::fromUtf8("label_ccdState"));
        label_ccdState->setGeometry(QRect(50, 15, 45, 18));
        label_ccdState->setFont(font1);
        t_year_label = new QLabel(main);
        t_year_label->setObjectName(QString::fromUtf8("t_year_label"));
        t_year_label->setGeometry(QRect(190, 8, 76, 25));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Arial"));
        font4.setPointSize(11);
        t_year_label->setFont(font4);
        t_year_label->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        t_year_label->setFrameShape(QFrame::NoFrame);
        t_date_label = new QLabel(main);
        t_date_label->setObjectName(QString::fromUtf8("t_date_label"));
        t_date_label->setGeometry(QRect(270, 8, 80, 25));
        t_date_label->setFont(font4);
        t_date_label->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        t_date_label->setFrameShape(QFrame::NoFrame);
        tabWidget = new QTabWidget(main);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(5, 5, 1766, 935));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Arial"));
        font5.setPointSize(12);
        font5.setBold(false);
        tabWidget->setFont(font5);
        tabWidget->setLayoutDirection(Qt::RightToLeft);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setTabsClosable(false);
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        tabWidget->addTab(tab_7, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        tabWidget->addTab(tab_6, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        tabWidget->addTab(tab_5, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidget->addTab(tab_4, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        label_30 = new QLabel(main);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(75, 5, 111, 30));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Arial"));
        font6.setPointSize(12);
        font6.setBold(true);
        label_30->setFont(font6);
        log_label = new QLabel(main);
        log_label->setObjectName(QString::fromUtf8("log_label"));
        log_label->setGeometry(QRect(10, 5, 51, 30));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Arial"));
        font7.setPointSize(20);
        font7.setItalic(true);
        log_label->setFont(font7);
        log_label->setLayoutDirection(Qt::LeftToRight);
        log_label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 171);"));
        log_label->setFrameShape(QFrame::NoFrame);
        frame = new QFrame(main);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(1565, 940, 206, 66));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_CAN = new QLabel(frame);
        label_CAN->setObjectName(QString::fromUtf8("label_CAN"));
        label_CAN->setGeometry(QRect(20, 25, 101, 21));
        label_CAN->setFont(font1);
        label_start_CAN = new QLabel(frame);
        label_start_CAN->setObjectName(QString::fromUtf8("label_start_CAN"));
        label_start_CAN->setGeometry(QRect(145, 25, 10, 21));
        label_start_CAN->setFont(font2);
        label_start_CAN->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));
        label_close_CAN = new QLabel(frame);
        label_close_CAN->setObjectName(QString::fromUtf8("label_close_CAN"));
        label_close_CAN->setGeometry(QRect(152, 25, 26, 21));
        label_close_CAN->setFont(font2);
        label_close_CAN->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        CAN_OPEN = new QSlider(frame);
        CAN_OPEN->setObjectName(QString::fromUtf8("CAN_OPEN"));
        CAN_OPEN->setGeometry(QRect(130, 26, 50, 20));
        CAN_OPEN->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"     border: none;\n"
"     background-color:  rgb(255,0,0);\n"
"    border-radius:  10px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"     width:  20px;\n"
"    height:  30px; \n"
"    background-color:  white;\n"
"    border-radius:10px; \n"
"}\n"
"QSlider:: handle:hover  {\n"
"        background-color:  white;\n"
"}\n"
"QSlider:: handle:checked  {\n"
"        background-color: blue;\n"
"}\n"
""));
        CAN_OPEN->setMaximum(1);
        CAN_OPEN->setSingleStep(0);
        CAN_OPEN->setOrientation(Qt::Horizontal);
        CAN_OPEN->setTickInterval(1);
        label_CAN->raise();
        CAN_OPEN->raise();
        label_start_CAN->raise();
        label_close_CAN->raise();
        MainWindow->setCentralWidget(main);
        tabWidget->raise();
        t_year_label->raise();
        t_date_label->raise();
        label_30->raise();
        log_label->raise();
        frame_Tkuai->raise();
        frame_BenSu->raise();
        frame_GAP->raise();
        frame_CCD->raise();
        frame->raise();

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\256\235\350\267\257\347\233\233\351\227\255\347\216\257\347\263\273\347\273\237", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "T\345\235\227\351\227\255\347\216\257", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\345\200\222\350\256\241\346\227\266", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\350\260\203\350\212\202\347\212\266\346\200\201", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "\347\255\211\345\276\205\344\270\255", nullptr));
        label_start->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\220\257", nullptr));
        label_close->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\346\263\265\351\200\237\351\227\255\347\216\257", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\345\200\222\350\256\241\346\227\266", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\350\260\203\350\212\202\351\207\217", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "\350\260\203\350\212\202\347\212\266\346\200\201", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "\347\255\211\345\276\205\344\270\255", nullptr));
        label_close2->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
        label_start2->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\220\257", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "CAP\351\227\255\347\216\257", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\345\267\246GAP\350\260\203\350\212\202\351\207\217", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\345\217\263GAP\350\260\203\350\212\202\351\207\217", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\345\257\271\351\275\220\350\260\203\350\212\202\351\207\217", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "\350\260\203\350\212\202\347\212\266\346\200\201", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "\347\255\211\345\276\205\344\270\255", nullptr));
        label_close3->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
        label_start3->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\220\257", nullptr));
        label_ccd->setText(QCoreApplication::translate("MainWindow", "CCD", nullptr));
        label_ccdState->setText(QCoreApplication::translate("MainWindow", "\346\234\252\350\277\236\346\216\245", nullptr));
        t_year_label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        t_date_label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QCoreApplication::translate("MainWindow", "\344\275\234\344\270\232\347\256\241\347\220\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237\347\256\241\347\220\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\347\256\241\347\220\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "\351\205\215\347\275\256\347\256\241\347\220\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\351\235\242\346\235\277", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\346\211\213\345\212\250\346\223\215\344\275\234", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\351\246\226\351\241\265", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "\346\231\272\350\203\275\351\227\255\347\216\257\347\263\273\347\273\237", nullptr));
        log_label->setText(QCoreApplication::translate("MainWindow", "BLS", nullptr));
        label_CAN->setText(QCoreApplication::translate("MainWindow", "\346\216\247\345\210\266\347\233\222\346\234\252\350\277\236\346\216\245", nullptr));
        label_start_CAN->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\220\257", nullptr));
        label_close_CAN->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
