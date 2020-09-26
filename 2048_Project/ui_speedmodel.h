/********************************************************************************
** Form generated from reading UI file 'speedmodel.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPEEDMODEL_H
#define UI_SPEEDMODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpeedModel
{
public:
    QAction *actionOne;
    QAction *actionTwo;
    QAction *actionThree;
    QAction *menuOne;
    QAction *menuTwo;
    QAction *action2;
    QAction *musicOne;
    QAction *musicTwo;
    QAction *actionHelp;
    QWidget *centralwidget;
    QLabel *labelOne;
    QCommandLinkButton *commandLinkButtonOne;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_4;

    void setupUi(QMainWindow *SpeedModel)
    {
        if (SpeedModel->objectName().isEmpty())
            SpeedModel->setObjectName(QString::fromUtf8("SpeedModel"));
        SpeedModel->resize(400, 501);
        SpeedModel->setMinimumSize(QSize(400, 500));
        actionOne = new QAction(SpeedModel);
        actionOne->setObjectName(QString::fromUtf8("actionOne"));
        actionTwo = new QAction(SpeedModel);
        actionTwo->setObjectName(QString::fromUtf8("actionTwo"));
        actionThree = new QAction(SpeedModel);
        actionThree->setObjectName(QString::fromUtf8("actionThree"));
        menuOne = new QAction(SpeedModel);
        menuOne->setObjectName(QString::fromUtf8("menuOne"));
        menuTwo = new QAction(SpeedModel);
        menuTwo->setObjectName(QString::fromUtf8("menuTwo"));
        action2 = new QAction(SpeedModel);
        action2->setObjectName(QString::fromUtf8("action2"));
        musicOne = new QAction(SpeedModel);
        musicOne->setObjectName(QString::fromUtf8("musicOne"));
        musicTwo = new QAction(SpeedModel);
        musicTwo->setObjectName(QString::fromUtf8("musicTwo"));
        actionHelp = new QAction(SpeedModel);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        centralwidget = new QWidget(SpeedModel);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        labelOne = new QLabel(centralwidget);
        labelOne->setObjectName(QString::fromUtf8("labelOne"));
        labelOne->setGeometry(QRect(83, 10, 201, 81));
        commandLinkButtonOne = new QCommandLinkButton(centralwidget);
        commandLinkButtonOne->setObjectName(QString::fromUtf8("commandLinkButtonOne"));
        commandLinkButtonOne->setGeometry(QRect(310, 430, 81, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        commandLinkButtonOne->setFont(font);
        SpeedModel->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SpeedModel);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        SpeedModel->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_4->menuAction());
        menu->addAction(menuOne);
        menu_2->addAction(menuTwo);
        menu_4->addAction(actionHelp);

        retranslateUi(SpeedModel);

        QMetaObject::connectSlotsByName(SpeedModel);
    } // setupUi

    void retranslateUi(QMainWindow *SpeedModel)
    {
        SpeedModel->setWindowTitle(QCoreApplication::translate("SpeedModel", "MainWindow", nullptr));
        actionOne->setText(QCoreApplication::translate("SpeedModel", "\351\207\215\346\235\245", nullptr));
        actionTwo->setText(QCoreApplication::translate("SpeedModel", "\350\257\273\345\217\226", nullptr));
        actionThree->setText(QCoreApplication::translate("SpeedModel", "\344\277\235\345\255\230", nullptr));
        menuOne->setText(QCoreApplication::translate("SpeedModel", "\351\200\200\345\207\272", nullptr));
        menuTwo->setText(QCoreApplication::translate("SpeedModel", "\346\237\245\347\234\213\346\270\270\346\210\217\346\210\220\347\273\251", nullptr));
        action2->setText(QCoreApplication::translate("SpeedModel", "2", nullptr));
        musicOne->setText(QCoreApplication::translate("SpeedModel", "\347\254\254\344\270\200\351\246\226", nullptr));
        musicTwo->setText(QCoreApplication::translate("SpeedModel", "\347\254\254\344\272\214\351\246\226", nullptr));
        actionHelp->setText(QCoreApplication::translate("SpeedModel", "\345\270\256\345\212\251\346\226\207\346\241\243", nullptr));
        commandLinkButtonOne->setText(QCoreApplication::translate("SpeedModel", "\350\277\224\345\233\236", nullptr));
        menu->setTitle(QCoreApplication::translate("SpeedModel", "\345\274\200\345\247\213", nullptr));
        menu_2->setTitle(QCoreApplication::translate("SpeedModel", "\346\237\245\347\234\213", nullptr));
        menu_4->setTitle(QCoreApplication::translate("SpeedModel", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpeedModel: public Ui_SpeedModel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPEEDMODEL_H
