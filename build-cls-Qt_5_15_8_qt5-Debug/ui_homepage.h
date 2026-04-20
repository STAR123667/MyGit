/********************************************************************************
** Form generated from reading UI file 'homepage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEPAGE_H
#define UI_HOMEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_homepage
{
public:
    QFrame *frame;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_motor;
    QFrame *frame_wrog;
    QLabel *label_6;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label_26;
    QFrame *frame_Tbj;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton_4;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_42;
    QLabel *label_45;
    QLabel *label_35;
    QLabel *label_40;
    QLabel *label_44;
    QLabel *label_43;
    QLabel *label_33;
    QLabel *label_36;
    QLabel *label_31;
    QLabel *label_41;
    QLabel *label_32;
    QLabel *label_34;
    QWidget *gridLayoutWidget_5;
    QGridLayout *gridLayout_3;
    QLabel *label_39;
    QLabel *label_38;
    QLabel *label_37;
    QLabel *label_48;
    QLabel *label_46;
    QLabel *label_47;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_2;
    QLabel *label_52;
    QLabel *label_54;
    QLabel *label_58;
    QLabel *label_51;
    QLabel *label_60;
    QLabel *label_50;
    QLabel *label_55;
    QLabel *label_53;
    QLabel *label_57;
    QLabel *label_56;
    QLabel *label_59;
    QComboBox *comboBox_home;
    QStackedWidget *stackedWidget_home;
    QWidget *page;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_face;
    QWidget *page_2;
    QWidget *gridLayoutWidget_6;
    QGridLayout *gridLayout_FaceTendencyChart;
    QLabel *label;

    void setupUi(QWidget *homepage)
    {
        if (homepage->objectName().isEmpty())
            homepage->setObjectName(QString::fromUtf8("homepage"));
        homepage->resize(1766, 920);
        frame = new QFrame(homepage);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(5, 15, 1755, 890));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        gridLayoutWidget_2 = new QWidget(frame);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(5, 45, 1746, 296));
        gridLayout_motor = new QGridLayout(gridLayoutWidget_2);
        gridLayout_motor->setObjectName(QString::fromUtf8("gridLayout_motor"));
        gridLayout_motor->setContentsMargins(0, 0, 0, 0);
        frame_wrog = new QFrame(frame);
        frame_wrog->setObjectName(QString::fromUtf8("frame_wrog"));
        frame_wrog->setGeometry(QRect(5, 665, 986, 220));
        frame_wrog->setFrameShape(QFrame::StyledPanel);
        frame_wrog->setFrameShadow(QFrame::Raised);
        label_6 = new QLabel(frame_wrog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 20, 81, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(false);
        label_6->setFont(font);
        pushButton = new QPushButton(frame_wrog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(110, 20, 80, 26));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 171);\n"
"color: rgb(255, 255, 255);\n"
""));
        pushButton_2 = new QPushButton(frame_wrog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(200, 20, 80, 26));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 171);\n"
"color: rgb(255, 255, 255);"));
        pushButton_3 = new QPushButton(frame_wrog);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(290, 20, 101, 26));
        pushButton_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 171);\n"
""));
        label_26 = new QLabel(frame_wrog);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(475, 110, 101, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(12);
        font1.setBold(false);
        label_26->setFont(font1);
        label_6->raise();
        label_26->raise();
        pushButton->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        frame_Tbj = new QFrame(frame);
        frame_Tbj->setObjectName(QString::fromUtf8("frame_Tbj"));
        frame_Tbj->setGeometry(QRect(993, 665, 758, 220));
        frame_Tbj->setFrameShape(QFrame::StyledPanel);
        frame_Tbj->setFrameShadow(QFrame::Raised);
        label_3 = new QLabel(frame_Tbj);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 20, 111, 21));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(14);
        font2.setBold(true);
        label_3->setFont(font2);
        label_4 = new QLabel(frame_Tbj);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 150, 91, 21));
        label_4->setFont(font2);
        pushButton_4 = new QPushButton(frame_Tbj);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(60, 185, 60, 26));
        pushButton_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        gridLayoutWidget = new QWidget(frame_Tbj);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(190, 5, 551, 137));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setHorizontalSpacing(15);
        gridLayout->setVerticalSpacing(5);
        gridLayout->setContentsMargins(10, 10, 0, 12);
        label_42 = new QLabel(gridLayoutWidget);
        label_42->setObjectName(QString::fromUtf8("label_42"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Sans Serif"));
        font3.setPointSize(16);
        font3.setBold(false);
        label_42->setFont(font3);
        label_42->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        label_42->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_42, 0, 2, 1, 1);

        label_45 = new QLabel(gridLayoutWidget);
        label_45->setObjectName(QString::fromUtf8("label_45"));
        label_45->setFont(font3);
        label_45->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        label_45->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_45, 2, 2, 1, 1);

        label_35 = new QLabel(gridLayoutWidget);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Arial"));
        font4.setPointSize(8);
        font4.setBold(false);
        label_35->setFont(font4);
        label_35->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_35, 3, 1, 1, 1);

        label_40 = new QLabel(gridLayoutWidget);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setFont(font3);
        label_40->setLayoutDirection(Qt::LeftToRight);
        label_40->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        label_40->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_40, 0, 0, 1, 1);

        label_44 = new QLabel(gridLayoutWidget);
        label_44->setObjectName(QString::fromUtf8("label_44"));
        label_44->setFont(font3);
        label_44->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        label_44->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_44, 2, 1, 1, 1);

        label_43 = new QLabel(gridLayoutWidget);
        label_43->setObjectName(QString::fromUtf8("label_43"));
        label_43->setFont(font3);
        label_43->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        label_43->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_43, 2, 0, 1, 1);

        label_33 = new QLabel(gridLayoutWidget);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Arial"));
        font5.setPointSize(8);
        font5.setBold(false);
        font5.setItalic(false);
        label_33->setFont(font5);
        label_33->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_33, 1, 2, 1, 1);

        label_36 = new QLabel(gridLayoutWidget);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setFont(font4);
        label_36->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_36, 3, 2, 1, 1);

        label_31 = new QLabel(gridLayoutWidget);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setFont(font4);
        label_31->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_31, 1, 0, 1, 1);

        label_41 = new QLabel(gridLayoutWidget);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        label_41->setFont(font3);
        label_41->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));
        label_41->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_41, 0, 1, 1, 1);

        label_32 = new QLabel(gridLayoutWidget);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setFont(font4);
        label_32->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_32, 1, 1, 1, 1);

        label_34 = new QLabel(gridLayoutWidget);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setFont(font4);
        label_34->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_34, 3, 0, 1, 1);

        gridLayoutWidget_5 = new QWidget(frame_Tbj);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(190, 145, 551, 71));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_5);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_39 = new QLabel(gridLayoutWidget_5);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setFont(font4);
        label_39->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_39, 1, 2, 1, 1);

        label_38 = new QLabel(gridLayoutWidget_5);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setFont(font4);
        label_38->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_38, 1, 1, 1, 1);

        label_37 = new QLabel(gridLayoutWidget_5);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setFont(font4);
        label_37->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_37, 1, 0, 1, 1);

        label_48 = new QLabel(gridLayoutWidget_5);
        label_48->setObjectName(QString::fromUtf8("label_48"));
        label_48->setFont(font3);
        label_48->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        label_48->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_48, 0, 0, 1, 1);

        label_46 = new QLabel(gridLayoutWidget_5);
        label_46->setObjectName(QString::fromUtf8("label_46"));
        label_46->setFont(font3);
        label_46->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        label_46->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_46, 0, 1, 1, 1);

        label_47 = new QLabel(gridLayoutWidget_5);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        label_47->setFont(font3);
        label_47->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        label_47->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_47, 0, 2, 1, 1);

        label_3->raise();
        label_4->raise();
        gridLayoutWidget->raise();
        pushButton_4->raise();
        gridLayoutWidget_5->raise();
        gridLayoutWidget_4 = new QWidget(frame);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(635, 355, 476, 26));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(10, 0, 6, 0);
        label_52 = new QLabel(gridLayoutWidget_4);
        label_52->setObjectName(QString::fromUtf8("label_52"));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Arial"));
        font6.setPointSize(9);
        font6.setBold(false);
        label_52->setFont(font6);

        gridLayout_2->addWidget(label_52, 0, 4, 1, 1);

        label_54 = new QLabel(gridLayoutWidget_4);
        label_54->setObjectName(QString::fromUtf8("label_54"));
        label_54->setFont(font6);

        gridLayout_2->addWidget(label_54, 0, 8, 1, 1);

        label_58 = new QLabel(gridLayoutWidget_4);
        label_58->setObjectName(QString::fromUtf8("label_58"));
        label_58->setFont(font6);
        label_58->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));

        gridLayout_2->addWidget(label_58, 0, 7, 1, 1);

        label_51 = new QLabel(gridLayoutWidget_4);
        label_51->setObjectName(QString::fromUtf8("label_51"));
        label_51->setFont(font6);

        gridLayout_2->addWidget(label_51, 0, 2, 1, 1);

        label_60 = new QLabel(gridLayoutWidget_4);
        label_60->setObjectName(QString::fromUtf8("label_60"));
        label_60->setFont(font6);
        label_60->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));

        gridLayout_2->addWidget(label_60, 0, 3, 1, 1);

        label_50 = new QLabel(gridLayoutWidget_4);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        label_50->setFont(font6);

        gridLayout_2->addWidget(label_50, 0, 0, 1, 1);

        label_55 = new QLabel(gridLayoutWidget_4);
        label_55->setObjectName(QString::fromUtf8("label_55"));
        label_55->setFont(font6);

        gridLayout_2->addWidget(label_55, 0, 10, 1, 1);

        label_53 = new QLabel(gridLayoutWidget_4);
        label_53->setObjectName(QString::fromUtf8("label_53"));
        label_53->setFont(font6);

        gridLayout_2->addWidget(label_53, 0, 6, 1, 1);

        label_57 = new QLabel(gridLayoutWidget_4);
        label_57->setObjectName(QString::fromUtf8("label_57"));
        label_57->setFont(font6);
        label_57->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));

        gridLayout_2->addWidget(label_57, 0, 5, 1, 1);

        label_56 = new QLabel(gridLayoutWidget_4);
        label_56->setObjectName(QString::fromUtf8("label_56"));
        label_56->setFont(font6);
        label_56->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));

        gridLayout_2->addWidget(label_56, 0, 9, 1, 1);

        label_59 = new QLabel(gridLayoutWidget_4);
        label_59->setObjectName(QString::fromUtf8("label_59"));
        label_59->setFont(font6);
        label_59->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));

        gridLayout_2->addWidget(label_59, 0, 1, 1, 1);

        comboBox_home = new QComboBox(frame);
        comboBox_home->addItem(QString());
        comboBox_home->addItem(QString());
        comboBox_home->setObjectName(QString::fromUtf8("comboBox_home"));
        comboBox_home->setGeometry(QRect(10, 355, 160, 26));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Arial"));
        font7.setPointSize(12);
        font7.setBold(true);
        comboBox_home->setFont(font7);
        comboBox_home->setMouseTracking(false);
        comboBox_home->setTabletTracking(false);
        comboBox_home->setFocusPolicy(Qt::NoFocus);
        comboBox_home->setContextMenuPolicy(Qt::DefaultContextMenu);
        comboBox_home->setAcceptDrops(false);
        comboBox_home->setToolTipDuration(-1);
        comboBox_home->setLayoutDirection(Qt::LeftToRight);
        comboBox_home->setAutoFillBackground(false);
        comboBox_home->setStyleSheet(QString::fromUtf8("QComboBox {\n"
" /*\n"
"     background-color:rgba(255,255,255,100%);\n"
"     font: 10pt  \"Microsoft  YaHei  UI\";\n"
"*/\n"
"     border:  none;  \n"
"}\n"
"QComboBox::drop-down{\n"
"   /* border-style: none;\n"
"       background-color:rgba(255,255,255,100%);\n"
"*/  \n"
"     \n"
"}\n"
""));
        comboBox_home->setEditable(false);
        comboBox_home->setMaxVisibleItems(10);
        comboBox_home->setInsertPolicy(QComboBox::InsertAtCurrent);
        comboBox_home->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        comboBox_home->setIconSize(QSize(10, 10));
        comboBox_home->setDuplicatesEnabled(false);
        comboBox_home->setFrame(true);
        comboBox_home->setModelColumn(0);
        stackedWidget_home = new QStackedWidget(frame);
        stackedWidget_home->setObjectName(QString::fromUtf8("stackedWidget_home"));
        stackedWidget_home->setGeometry(QRect(5, 390, 1746, 271));
        stackedWidget_home->setFrameShape(QFrame::StyledPanel);
        stackedWidget_home->setLineWidth(1);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayoutWidget_3 = new QWidget(page);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(5, 5, 1731, 256));
        gridLayout_face = new QGridLayout(gridLayoutWidget_3);
        gridLayout_face->setObjectName(QString::fromUtf8("gridLayout_face"));
        gridLayout_face->setContentsMargins(0, 0, 0, 0);
        stackedWidget_home->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayoutWidget_6 = new QWidget(page_2);
        gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(0, 0, 1741, 261));
        gridLayout_FaceTendencyChart = new QGridLayout(gridLayoutWidget_6);
        gridLayout_FaceTendencyChart->setObjectName(QString::fromUtf8("gridLayout_FaceTendencyChart"));
        gridLayout_FaceTendencyChart->setContentsMargins(0, 0, 0, 0);
        stackedWidget_home->addWidget(page_2);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 15, 191, 18));
        label->setFont(font7);

        retranslateUi(homepage);

        comboBox_home->setCurrentIndex(0);
        stackedWidget_home->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(homepage);
    } // setupUi

    void retranslateUi(QWidget *homepage)
    {
        homepage->setWindowTitle(QCoreApplication::translate("homepage", "Form", nullptr));
        label_6->setText(QCoreApplication::translate("homepage", "\345\256\236\346\227\266\346\212\245\350\255\246", nullptr));
        pushButton->setText(QCoreApplication::translate("homepage", "\347\241\256\350\256\244\345\275\223\345\211\215\351\241\265", nullptr));
        pushButton_2->setText(QCoreApplication::translate("homepage", "\347\241\256\350\256\244\345\205\250\351\203\250", nullptr));
        pushButton_3->setText(QCoreApplication::translate("homepage", "\346\237\245\347\234\213\346\233\264\345\244\232\346\212\245\350\255\246", nullptr));
        label_26->setText(QCoreApplication::translate("homepage", "\346\232\202\346\227\240\346\212\245\350\255\246", nullptr));
        label_3->setText(QCoreApplication::translate("homepage", "\346\266\202\345\270\203\346\234\272\344\277\241\346\201\257", nullptr));
        label_4->setText(QCoreApplication::translate("homepage", "\347\224\237\344\272\247\344\277\241\346\201\257", nullptr));
        pushButton_4->setText(QCoreApplication::translate("homepage", "\346\270\205\351\233\266", nullptr));
        label_42->setText(QCoreApplication::translate("homepage", "0", nullptr));
        label_45->setText(QCoreApplication::translate("homepage", "0", nullptr));
        label_35->setText(QCoreApplication::translate("homepage", "\345\267\246GAP\345\256\236\346\227\266\345\200\274", nullptr));
        label_40->setText(QCoreApplication::translate("homepage", "\345\205\263\351\227\255", nullptr));
        label_44->setText(QCoreApplication::translate("homepage", "0", nullptr));
        label_43->setText(QCoreApplication::translate("homepage", "0", nullptr));
        label_33->setText(QCoreApplication::translate("homepage", "\346\263\265\351\200\237\345\256\236\346\227\266\345\200\274", nullptr));
        label_36->setText(QCoreApplication::translate("homepage", "\345\217\263GAP\345\256\236\346\227\266\345\200\274", nullptr));
        label_31->setText(QCoreApplication::translate("homepage", "\346\266\202\345\270\203\347\212\266\346\200\201", nullptr));
        label_41->setText(QCoreApplication::translate("homepage", "0", nullptr));
        label_32->setText(QCoreApplication::translate("homepage", "\346\263\265\351\200\237\350\256\276\345\256\232\345\200\274", nullptr));
        label_34->setText(QCoreApplication::translate("homepage", "\346\250\241\345\244\264\346\250\252\345\220\221\344\275\215\347\275\256", nullptr));
        label_39->setText(QCoreApplication::translate("homepage", "\345\271\263\345\235\207COV", nullptr));
        label_38->setText(QCoreApplication::translate("homepage", "\345\271\263\345\235\207CPK", nullptr));
        label_37->setText(QCoreApplication::translate("homepage", "\346\200\273\347\224\237\344\272\247\347\261\263\346\225\260", nullptr));
        label_48->setText(QCoreApplication::translate("homepage", "0.00", nullptr));
        label_46->setText(QCoreApplication::translate("homepage", "00000.0", nullptr));
        label_47->setText(QCoreApplication::translate("homepage", "0.00", nullptr));
        label_52->setText(QCoreApplication::translate("homepage", "\346\234\200\345\244\247\345\200\274:", nullptr));
        label_54->setText(QCoreApplication::translate("homepage", "\345\271\263\345\235\207\345\200\274:", nullptr));
        label_58->setText(QCoreApplication::translate("homepage", "0", nullptr));
        label_51->setText(QCoreApplication::translate("homepage", "COV: ", nullptr));
        label_60->setText(QCoreApplication::translate("homepage", "0", nullptr));
        label_50->setText(QCoreApplication::translate("homepage", "CPK:  ", nullptr));
        label_55->setText(QCoreApplication::translate("homepage", "\345\211\212\350\226\204\345\214\272:", nullptr));
        label_53->setText(QCoreApplication::translate("homepage", "\346\234\200\345\260\217\345\200\274:", nullptr));
        label_57->setText(QCoreApplication::translate("homepage", "0", nullptr));
        label_56->setText(QCoreApplication::translate("homepage", "0", nullptr));
        label_59->setText(QCoreApplication::translate("homepage", "0", nullptr));
        comboBox_home->setItemText(0, QCoreApplication::translate("homepage", "\351\235\242\345\257\206\345\272\246\344\273\252\345\256\236\346\227\266\346\225\260\346\215\256", nullptr));
        comboBox_home->setItemText(1, QCoreApplication::translate("homepage", "\346\250\252\345\220\221\350\266\213\345\212\277\346\225\260\346\215\256", nullptr));

        label->setText(QCoreApplication::translate("homepage", "\347\224\265\346\235\206\345\256\236\346\227\266\344\275\215\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class homepage: public Ui_homepage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
