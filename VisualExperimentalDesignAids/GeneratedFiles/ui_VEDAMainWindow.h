/********************************************************************************
** Form generated from reading UI file 'VEDAMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEDAMAINWINDOW_H
#define UI_VEDAMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VEDAMainWindow
{
public:
    QAction *InitProjectBtn;
    QAction *OpenProjectBtn;
    QAction *CloseBtn;
    QAction *CloseProjectBtn;
    QAction *SaveBtn;
    QAction *SaveAllBtn;
    QAction *ExitBtn;
    QAction *AboutBtn;
    QAction *InitProcessBtn;
    QAction *ImportProcessBtn;
    QAction *ExportReportBtn;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_3;
    QMenu *menu_2;
    QMenu *menu_4;

    void setupUi(QMainWindow *VEDAMainWindow)
    {
        if (VEDAMainWindow->objectName().isEmpty())
            VEDAMainWindow->setObjectName(QStringLiteral("VEDAMainWindow"));
        VEDAMainWindow->resize(800, 600);
        InitProjectBtn = new QAction(VEDAMainWindow);
        InitProjectBtn->setObjectName(QStringLiteral("InitProjectBtn"));
        OpenProjectBtn = new QAction(VEDAMainWindow);
        OpenProjectBtn->setObjectName(QStringLiteral("OpenProjectBtn"));
        CloseBtn = new QAction(VEDAMainWindow);
        CloseBtn->setObjectName(QStringLiteral("CloseBtn"));
        CloseProjectBtn = new QAction(VEDAMainWindow);
        CloseProjectBtn->setObjectName(QStringLiteral("CloseProjectBtn"));
        SaveBtn = new QAction(VEDAMainWindow);
        SaveBtn->setObjectName(QStringLiteral("SaveBtn"));
        SaveAllBtn = new QAction(VEDAMainWindow);
        SaveAllBtn->setObjectName(QStringLiteral("SaveAllBtn"));
        ExitBtn = new QAction(VEDAMainWindow);
        ExitBtn->setObjectName(QStringLiteral("ExitBtn"));
        AboutBtn = new QAction(VEDAMainWindow);
        AboutBtn->setObjectName(QStringLiteral("AboutBtn"));
        InitProcessBtn = new QAction(VEDAMainWindow);
        InitProcessBtn->setObjectName(QStringLiteral("InitProcessBtn"));
        ImportProcessBtn = new QAction(VEDAMainWindow);
        ImportProcessBtn->setObjectName(QStringLiteral("ImportProcessBtn"));
        ExportReportBtn = new QAction(VEDAMainWindow);
        ExportReportBtn->setObjectName(QStringLiteral("ExportReportBtn"));
        centralwidget = new QWidget(VEDAMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        VEDAMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(VEDAMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_3 = new QMenu(menu);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        VEDAMainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_4->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(InitProjectBtn);
        menu->addAction(OpenProjectBtn);
        menu->addSeparator();
        menu->addAction(menu_3->menuAction());
        menu->addSeparator();
        menu->addAction(CloseBtn);
        menu->addAction(CloseProjectBtn);
        menu->addSeparator();
        menu->addAction(SaveBtn);
        menu->addAction(SaveAllBtn);
        menu->addSeparator();
        menu->addAction(ExitBtn);
        menu_3->addAction(InitProcessBtn);
        menu_3->addSeparator();
        menu_3->addAction(ImportProcessBtn);
        menu_2->addAction(AboutBtn);
        menu_4->addAction(ExportReportBtn);

        retranslateUi(VEDAMainWindow);

        QMetaObject::connectSlotsByName(VEDAMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *VEDAMainWindow)
    {
        VEDAMainWindow->setWindowTitle(QApplication::translate("VEDAMainWindow", "VEDAMainWindow", Q_NULLPTR));
        InitProjectBtn->setText(QApplication::translate("VEDAMainWindow", "\346\226\260\345\273\272\345\256\236\351\252\214", Q_NULLPTR));
        OpenProjectBtn->setText(QApplication::translate("VEDAMainWindow", "\346\211\223\345\274\200\345\256\236\351\252\214", Q_NULLPTR));
        CloseBtn->setText(QApplication::translate("VEDAMainWindow", "\345\205\263\351\227\255", Q_NULLPTR));
        CloseProjectBtn->setText(QApplication::translate("VEDAMainWindow", "\345\205\263\351\227\255\345\256\236\351\252\214", Q_NULLPTR));
        SaveBtn->setText(QApplication::translate("VEDAMainWindow", "\344\277\235\345\255\230", Q_NULLPTR));
        SaveAllBtn->setText(QApplication::translate("VEDAMainWindow", "\344\277\235\345\255\230\345\205\250\351\203\250", Q_NULLPTR));
        ExitBtn->setText(QApplication::translate("VEDAMainWindow", "\351\200\200\345\207\272", Q_NULLPTR));
        AboutBtn->setText(QApplication::translate("VEDAMainWindow", "\345\205\263\344\272\216", Q_NULLPTR));
        InitProcessBtn->setText(QApplication::translate("VEDAMainWindow", "\346\226\260\345\273\272\345\256\236\351\252\214\350\277\207\347\250\213", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        InitProcessBtn->setToolTip(QApplication::translate("VEDAMainWindow", "\346\226\260\345\273\272\345\256\236\351\252\214\350\277\207\347\250\213", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        ImportProcessBtn->setText(QApplication::translate("VEDAMainWindow", "\347\216\260\346\234\211\345\256\236\351\252\214\350\277\207\347\250\213", Q_NULLPTR));
        ExportReportBtn->setText(QApplication::translate("VEDAMainWindow", "\347\224\237\346\210\220\345\256\236\351\252\214\346\212\245\345\221\212", Q_NULLPTR));
        menu->setTitle(QApplication::translate("VEDAMainWindow", "\346\226\207\344\273\266", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("VEDAMainWindow", "\346\267\273\345\212\240", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("VEDAMainWindow", "\345\270\256\345\212\251", Q_NULLPTR));
        menu_4->setTitle(QApplication::translate("VEDAMainWindow", "\347\224\237\346\210\220", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VEDAMainWindow: public Ui_VEDAMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEDAMAINWINDOW_H
