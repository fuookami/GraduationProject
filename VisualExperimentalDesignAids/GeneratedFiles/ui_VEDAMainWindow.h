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
    QAction *AddBtn;
    QAction *CloseBtn;
    QAction *CloseProjectBtn;
    QAction *SaveBtn;
    QAction *SaveAllBtn;
    QAction *ExitBtn;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *VEDAMainWindow)
    {
        if (VEDAMainWindow->objectName().isEmpty())
            VEDAMainWindow->setObjectName(QStringLiteral("VEDAMainWindow"));
        VEDAMainWindow->resize(800, 600);
        InitProjectBtn = new QAction(VEDAMainWindow);
        InitProjectBtn->setObjectName(QStringLiteral("InitProjectBtn"));
        OpenProjectBtn = new QAction(VEDAMainWindow);
        OpenProjectBtn->setObjectName(QStringLiteral("OpenProjectBtn"));
        AddBtn = new QAction(VEDAMainWindow);
        AddBtn->setObjectName(QStringLiteral("AddBtn"));
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
        centralwidget = new QWidget(VEDAMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        VEDAMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(VEDAMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        VEDAMainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(InitProjectBtn);
        menu->addAction(OpenProjectBtn);
        menu->addSeparator();
        menu->addAction(AddBtn);
        menu->addSeparator();
        menu->addAction(CloseBtn);
        menu->addAction(CloseProjectBtn);
        menu->addSeparator();
        menu->addAction(SaveBtn);
        menu->addAction(SaveAllBtn);
        menu->addSeparator();
        menu->addAction(ExitBtn);

        retranslateUi(VEDAMainWindow);

        QMetaObject::connectSlotsByName(VEDAMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *VEDAMainWindow)
    {
        VEDAMainWindow->setWindowTitle(QApplication::translate("VEDAMainWindow", "VEDAMainWindow", Q_NULLPTR));
        InitProjectBtn->setText(QApplication::translate("VEDAMainWindow", "\346\226\260\345\273\272\345\256\236\351\252\214", Q_NULLPTR));
        OpenProjectBtn->setText(QApplication::translate("VEDAMainWindow", "\346\211\223\345\274\200\345\256\236\351\252\214", Q_NULLPTR));
        AddBtn->setText(QApplication::translate("VEDAMainWindow", "\346\267\273\345\212\240", Q_NULLPTR));
        CloseBtn->setText(QApplication::translate("VEDAMainWindow", "\345\205\263\351\227\255", Q_NULLPTR));
        CloseProjectBtn->setText(QApplication::translate("VEDAMainWindow", "\345\205\263\351\227\255\345\256\236\351\252\214", Q_NULLPTR));
        SaveBtn->setText(QApplication::translate("VEDAMainWindow", "\344\277\235\345\255\230", Q_NULLPTR));
        SaveAllBtn->setText(QApplication::translate("VEDAMainWindow", "\344\277\235\345\255\230\345\205\250\351\203\250", Q_NULLPTR));
        ExitBtn->setText(QApplication::translate("VEDAMainWindow", "\351\200\200\345\207\272", Q_NULLPTR));
        menu->setTitle(QApplication::translate("VEDAMainWindow", "\346\226\207\344\273\266", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("VEDAMainWindow", "\345\270\256\345\212\251", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VEDAMainWindow: public Ui_VEDAMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEDAMAINWINDOW_H
