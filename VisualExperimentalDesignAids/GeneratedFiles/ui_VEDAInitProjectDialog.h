/********************************************************************************
** Form generated from reading UI file 'VEDAInitProjectDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEDAINITPROJECTDIALOG_H
#define UI_VEDAINITPROJECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VEDAInitProjectDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *MainTitle;
    QGridLayout *gridLayout;
    QLineEdit *ProjectLocation;
    QPushButton *SelectLocationBtn;
    QLabel *label_2;
    QLineEdit *ProjectName;
    QLabel *label;
    QCheckBox *ToInitNewDir;
    QSpacerItem *verticalSpacer_2;
    QLabel *Infomation;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *ComfirmBtn;
    QPushButton *CancelBtn;

    void setupUi(QDialog *VEDAInitProjectDialog)
    {
        if (VEDAInitProjectDialog->objectName().isEmpty())
            VEDAInitProjectDialog->setObjectName(QStringLiteral("VEDAInitProjectDialog"));
        VEDAInitProjectDialog->resize(572, 287);
        VEDAInitProjectDialog->setMinimumSize(QSize(572, 287));
        VEDAInitProjectDialog->setMaximumSize(QSize(572, 287));
        VEDAInitProjectDialog->setStyleSheet(QLatin1String("#VEDAInitProjectDialog {\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout = new QVBoxLayout(VEDAInitProjectDialog);
        verticalLayout->setSpacing(16);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        MainTitle = new QLabel(VEDAInitProjectDialog);
        MainTitle->setObjectName(QStringLiteral("MainTitle"));
        MainTitle->setMinimumSize(QSize(0, 28));
        MainTitle->setMaximumSize(QSize(16777215, 28));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font.setPointSize(16);
        MainTitle->setFont(font);
        MainTitle->setStyleSheet(QStringLiteral("color: rgb(0, 93, 164);"));
        MainTitle->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(MainTitle);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(10);
        gridLayout->setVerticalSpacing(12);
        ProjectLocation = new QLineEdit(VEDAInitProjectDialog);
        ProjectLocation->setObjectName(QStringLiteral("ProjectLocation"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font1.setPointSize(9);
        ProjectLocation->setFont(font1);

        gridLayout->addWidget(ProjectLocation, 1, 2, 1, 1);

        SelectLocationBtn = new QPushButton(VEDAInitProjectDialog);
        SelectLocationBtn->setObjectName(QStringLiteral("SelectLocationBtn"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        SelectLocationBtn->setFont(font2);
        SelectLocationBtn->setStyleSheet(QStringLiteral(""));
        SelectLocationBtn->setAutoRepeat(true);
        SelectLocationBtn->setAutoExclusive(true);
        SelectLocationBtn->setAutoDefault(true);
        SelectLocationBtn->setFlat(false);

        gridLayout->addWidget(SelectLocationBtn, 1, 3, 1, 1);

        label_2 = new QLabel(VEDAInitProjectDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(50, 0));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(11);
        label_2->setFont(font3);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        ProjectName = new QLineEdit(VEDAInitProjectDialog);
        ProjectName->setObjectName(QStringLiteral("ProjectName"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        ProjectName->setFont(font4);

        gridLayout->addWidget(ProjectName, 0, 2, 1, 1);

        label = new QLabel(VEDAInitProjectDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(50, 0));
        label->setFont(font3);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        ToInitNewDir = new QCheckBox(VEDAInitProjectDialog);
        ToInitNewDir->setObjectName(QStringLiteral("ToInitNewDir"));
        ToInitNewDir->setFont(font3);
        ToInitNewDir->setChecked(true);

        verticalLayout->addWidget(ToInitNewDir);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        Infomation = new QLabel(VEDAInitProjectDialog);
        Infomation->setObjectName(QStringLiteral("Infomation"));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font5.setPointSize(10);
        Infomation->setFont(font5);
        Infomation->setStyleSheet(QStringLiteral("color: rgb(177, 92, 86);"));
        Infomation->setWordWrap(true);

        verticalLayout->addWidget(Infomation);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        ComfirmBtn = new QPushButton(VEDAInitProjectDialog);
        ComfirmBtn->setObjectName(QStringLiteral("ComfirmBtn"));
        ComfirmBtn->setFont(font2);

        horizontalLayout_2->addWidget(ComfirmBtn);

        CancelBtn = new QPushButton(VEDAInitProjectDialog);
        CancelBtn->setObjectName(QStringLiteral("CancelBtn"));
        CancelBtn->setFont(font2);

        horizontalLayout_2->addWidget(CancelBtn);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(VEDAInitProjectDialog);

        QMetaObject::connectSlotsByName(VEDAInitProjectDialog);
    } // setupUi

    void retranslateUi(QDialog *VEDAInitProjectDialog)
    {
        VEDAInitProjectDialog->setWindowTitle(QApplication::translate("VEDAInitProjectDialog", "\346\226\260\345\273\272\345\256\236\351\252\214\351\241\271\347\233\256", Q_NULLPTR));
        MainTitle->setText(QApplication::translate("VEDAInitProjectDialog", "\346\226\260\345\273\272\345\256\236\351\252\214\351\241\271\347\233\256", Q_NULLPTR));
        SelectLocationBtn->setText(QApplication::translate("VEDAInitProjectDialog", "\346\265\217\350\247\210", Q_NULLPTR));
        label_2->setText(QApplication::translate("VEDAInitProjectDialog", "\344\275\215\347\275\256\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("VEDAInitProjectDialog", "\345\220\215\347\247\260\357\274\232", Q_NULLPTR));
        ToInitNewDir->setText(QApplication::translate("VEDAInitProjectDialog", "\344\270\272\345\256\236\351\252\214\351\241\271\347\233\256\345\210\233\345\273\272\347\233\256\345\275\225", Q_NULLPTR));
        Infomation->setText(QString());
        ComfirmBtn->setText(QApplication::translate("VEDAInitProjectDialog", "\347\241\256\345\256\232", Q_NULLPTR));
        CancelBtn->setText(QApplication::translate("VEDAInitProjectDialog", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VEDAInitProjectDialog: public Ui_VEDAInitProjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEDAINITPROJECTDIALOG_H
