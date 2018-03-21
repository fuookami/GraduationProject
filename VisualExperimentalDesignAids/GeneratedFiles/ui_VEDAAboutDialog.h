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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VEDAAboutDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *MainTitle;
    QSpacerItem *verticalSpacer_5;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *Version;
    QLabel *BuildDatetime;
    QLabel *Name;
    QLabel *Code;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *ComfirmBtn;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *VEDAAboutDialog)
    {
        if (VEDAAboutDialog->objectName().isEmpty())
            VEDAAboutDialog->setObjectName(QStringLiteral("VEDAAboutDialog"));
        VEDAAboutDialog->resize(572, 287);
        VEDAAboutDialog->setMinimumSize(QSize(572, 287));
        VEDAAboutDialog->setMaximumSize(QSize(572, 287));
        VEDAAboutDialog->setStyleSheet(QLatin1String("#VEDAAboutDialog {\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout = new QVBoxLayout(VEDAAboutDialog);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 16, 0, 16);
        MainTitle = new QLabel(VEDAAboutDialog);
        MainTitle->setObjectName(QStringLiteral("MainTitle"));
        MainTitle->setMinimumSize(QSize(0, 28));
        MainTitle->setMaximumSize(QSize(16777215, 28));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font.setPointSize(16);
        MainTitle->setFont(font);
        MainTitle->setStyleSheet(QStringLiteral("color: rgb(0, 93, 164);"));
        MainTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(MainTitle);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        label = new QLabel(VEDAAboutDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(11);
        label->setFont(font1);
        label->setStyleSheet(QStringLiteral("color: rgb(150, 145, 141);"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(8);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        Version = new QLabel(VEDAAboutDialog);
        Version->setObjectName(QStringLiteral("Version"));
        Version->setMinimumSize(QSize(0, 24));
        Version->setMaximumSize(QSize(16777215, 24));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(12);
        Version->setFont(font2);
        Version->setStyleSheet(QStringLiteral("color: rgb(150, 145, 141);"));

        verticalLayout_3->addWidget(Version);

        BuildDatetime = new QLabel(VEDAAboutDialog);
        BuildDatetime->setObjectName(QStringLiteral("BuildDatetime"));
        BuildDatetime->setMinimumSize(QSize(0, 24));
        BuildDatetime->setMaximumSize(QSize(16777215, 24));
        BuildDatetime->setFont(font2);
        BuildDatetime->setStyleSheet(QStringLiteral("color: rgb(150, 145, 141);"));

        verticalLayout_3->addWidget(BuildDatetime);

        Name = new QLabel(VEDAAboutDialog);
        Name->setObjectName(QStringLiteral("Name"));
        Name->setMinimumSize(QSize(0, 24));
        Name->setMaximumSize(QSize(16777215, 24));
        Name->setFont(font2);
        Name->setStyleSheet(QStringLiteral("color: rgb(150, 145, 141);"));

        verticalLayout_3->addWidget(Name);

        Code = new QLabel(VEDAAboutDialog);
        Code->setObjectName(QStringLiteral("Code"));
        Code->setMinimumSize(QSize(0, 24));
        Code->setMaximumSize(QSize(16777215, 24));
        Code->setFont(font2);
        Code->setStyleSheet(QStringLiteral("color: rgb(150, 145, 141);"));

        verticalLayout_3->addWidget(Code);


        horizontalLayout_5->addLayout(verticalLayout_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_8);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ComfirmBtn = new QPushButton(VEDAAboutDialog);
        ComfirmBtn->setObjectName(QStringLiteral("ComfirmBtn"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        ComfirmBtn->setFont(font3);

        horizontalLayout->addWidget(ComfirmBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


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
        ComfirmBtn->setText(QApplication::translate("VEDAAboutDialog", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VEDAAboutDialog: public Ui_VEDAAboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEDAABOUTDIALOG_H
