/********************************************************************************
** Form generated from reading UI file 'dataface.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAFACE_H
#define UI_DATAFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dataface
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *themeLabel;
    QComboBox *themeComboBox;
    QLabel *animatedLable;
    QComboBox *animatedComboBox;
    QLabel *legendLable;
    QComboBox *legendComboBox;
    QCheckBox *antialiasCheckBox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QPushButton *Updata_Button;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *dataface)
    {
        if (dataface->objectName().isEmpty())
            dataface->setObjectName(QString::fromUtf8("dataface"));
        dataface->setWindowModality(Qt::NonModal);
        dataface->resize(1760, 900);
        gridLayout = new QGridLayout(dataface);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        themeLabel = new QLabel(dataface);
        themeLabel->setObjectName(QString::fromUtf8("themeLabel"));

        horizontalLayout->addWidget(themeLabel);

        themeComboBox = new QComboBox(dataface);
        themeComboBox->setObjectName(QString::fromUtf8("themeComboBox"));

        horizontalLayout->addWidget(themeComboBox);

        animatedLable = new QLabel(dataface);
        animatedLable->setObjectName(QString::fromUtf8("animatedLable"));

        horizontalLayout->addWidget(animatedLable);

        animatedComboBox = new QComboBox(dataface);
        animatedComboBox->setObjectName(QString::fromUtf8("animatedComboBox"));

        horizontalLayout->addWidget(animatedComboBox);

        legendLable = new QLabel(dataface);
        legendLable->setObjectName(QString::fromUtf8("legendLable"));

        horizontalLayout->addWidget(legendLable);

        legendComboBox = new QComboBox(dataface);
        legendComboBox->setObjectName(QString::fromUtf8("legendComboBox"));

        horizontalLayout->addWidget(legendComboBox);

        antialiasCheckBox = new QCheckBox(dataface);
        antialiasCheckBox->setObjectName(QString::fromUtf8("antialiasCheckBox"));

        horizontalLayout->addWidget(antialiasCheckBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(dataface);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        Updata_Button = new QPushButton(dataface);
        Updata_Button->setObjectName(QString::fromUtf8("Updata_Button"));
        Updata_Button->setCheckable(false);
        Updata_Button->setChecked(false);

        horizontalLayout->addWidget(Updata_Button);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(dataface);
        QObject::connect(themeComboBox, SIGNAL(currentIndexChanged(int)), dataface, SLOT(updateUI()));
        QObject::connect(legendComboBox, SIGNAL(currentIndexChanged(int)), dataface, SLOT(updateUI()));
        QObject::connect(antialiasCheckBox, SIGNAL(toggled(bool)), dataface, SLOT(updateUI()));
        QObject::connect(animatedComboBox, SIGNAL(currentIndexChanged(int)), dataface, SLOT(updateUI()));
        QObject::connect(Updata_Button, SIGNAL(pressed()), dataface, SLOT(updateUI()));

        QMetaObject::connectSlotsByName(dataface);
    } // setupUi

    void retranslateUi(QWidget *dataface)
    {
        dataface->setWindowTitle(QCoreApplication::translate("dataface", "Form", nullptr));
        themeLabel->setText(QCoreApplication::translate("dataface", "Theme:", nullptr));
        animatedLable->setText(QCoreApplication::translate("dataface", "Animation:", nullptr));
        legendLable->setText(QCoreApplication::translate("dataface", "Legend:", nullptr));
        antialiasCheckBox->setText(QCoreApplication::translate("dataface", "Anti-aliasing", nullptr));
        label->setText(QCoreApplication::translate("dataface", "Update_Chart:", nullptr));
        Updata_Button->setText(QCoreApplication::translate("dataface", "button", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dataface: public Ui_dataface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAFACE_H
