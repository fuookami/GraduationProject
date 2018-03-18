/********************************************************************************
** Form generated from reading UI file 'VEDAAboutDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEDAABOUTDIALOG_H
#define UI_VEDAABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VEDAAboutDialog
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *MainTitle;
    QLabel *label;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *Version;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *BuildDatetime;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *Name;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_7;
    QLabel *Code;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QDialog *VEDAAboutDialog)
    {
        if (VEDAAboutDialog->objectName().isEmpty())
            VEDAAboutDialog->setObjectName(QStringLiteral("VEDAAboutDialog"));
        VEDAAboutDialog->resize(572, 287);
        VEDAAboutDialog->setMinimumSize(QSize(572, 287));
        VEDAAboutDialog->setMaximumSize(QSize(572, 287));
        VEDAAboutDialog->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        verticalLayout = new QVBoxLayout(VEDAAboutDialog);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        MainTitle = new QLabel(VEDAAboutDialog);
        MainTitle->setObjectName(QStringLiteral("MainTitle"));
        MainTitle->setMinimumSize(QSize(0, 24));
        MainTitle->setMaximumSize(QSize(16777215, 24));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font.setPointSize(16);
        MainTitle->setFont(font);
        MainTitle->setStyleSheet(QStringLiteral("color: rgb(0, 93, 164);"));
        MainTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(MainTitle);

        label = new QLabel(VEDAAboutDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font1.setPointSize(11);
        label->setFont(font1);
        label->setStyleSheet(QStringLiteral("color: rgb(150, 145, 141);"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(125, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        Version = new QLabel(VEDAAboutDialog);
        Version->setObjectName(QStringLiteral("Version"));
        Version->setMinimumSize(QSize(0, 16));
        Version->setMaximumSize(QSize(16777215, 16));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font2.setPointSize(12);
        Version->setFont(font2);
        Version->setStyleSheet(QStringLiteral("color: rgb(150, 145, 141);"));

        horizontalLayout->addWidget(Version);

        horizontalSpacer = new QSpacerItem(569, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(125, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        BuildDatetime = new QLabel(VEDAAboutDialog);
        BuildDatetime->setObjectName(QStringLiteral("BuildDatetime"));
        BuildDatetime->setMinimumSize(QSize(0, 16));
        BuildDatetime->setMaximumSize(QSize(16777215, 16));
        BuildDatetime->setFont(font2);
        BuildDatetime->setStyleSheet(QStringLiteral("color: rgb(150, 145, 141);"));

        horizontalLayout_2->addWidget(BuildDatetime);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(125, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        Name = new QLabel(VEDAAboutDialog);
        Name->setObjectName(QStringLiteral("Name"));
        Name->setMinimumSize(QSize(0, 16));
        Name->setMaximumSize(QSize(16777215, 16));
        Name->setFont(font2);
        Name->setStyleSheet(QStringLiteral("color: rgb(150, 145, 141);"));

        horizontalLayout_3->addWidget(Name);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_7 = new QSpacerItem(125, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        Code = new QLabel(VEDAAboutDialog);
        Code->setObjectName(QStringLiteral("Code"));
        Code->setMinimumSize(QSize(0, 16));
        Code->setMaximumSize(QSize(16777215, 16));
        Code->setFont(font2);
        Code->setStyleSheet(QStringLiteral("color: rgb(150, 145, 141);"));

        horizontalLayout_4->addWidget(Code);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);


        retranslateUi(VEDAAboutDialog);

        QMetaObject::connectSlotsByName(VEDAAboutDialog);
    } // setupUi

    void retranslateUi(QDialog *VEDAAboutDialog)
    {
        VEDAAboutDialog->setWindowTitle(QApplication::translate("VEDAAboutDialog", "\345\205\263\344\272\216 \345\217\257\350\247\206\345\214\226\345\256\236\351\252\214\350\256\276\350\256\241\350\276\205\345\212\251\345\267\245\345\205\267", Q_NULLPTR));
        MainTitle->setText(QApplication::translate("VEDAAboutDialog", "\345\217\257\350\247\206\345\214\226\345\256\236\351\252\214\350\256\276\350\256\241\350\276\205\345\212\251\345\267\245\345\205\267", Q_NULLPTR));
        label->setText(QApplication::translate("VEDAAboutDialog", "\357\274\210\346\257\225\344\270\232\350\256\276\350\256\241\357\274\211", Q_NULLPTR));
        Version->setText(QApplication::translate("VEDAAboutDialog", "\350\275\257\344\273\266\347\211\210\346\234\254\357\274\232", Q_NULLPTR));
        BuildDatetime->setText(QApplication::translate("VEDAAboutDialog", "\347\224\237\346\210\220\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        Name->setText(QApplication::translate("VEDAAboutDialog", "\345\247\223\345\220\215\357\274\232\346\235\216\344\274\237\346\226\207", Q_NULLPTR));
        Code->setText(QApplication::translate("VEDAAboutDialog", "\345\255\246\345\217\267\357\274\232161430229", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VEDAAboutDialog: public Ui_VEDAAboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEDAABOUTDIALOG_H
