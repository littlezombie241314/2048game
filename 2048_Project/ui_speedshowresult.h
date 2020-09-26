/********************************************************************************
** Form generated from reading UI file 'speedshowresult.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPEEDSHOWRESULT_H
#define UI_SPEEDSHOWRESULT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpeedShowResult
{
public:
    QWidget *centralwidget;
    QTextEdit *textEditOne;
    QLabel *label;
    QCommandLinkButton *commandLinkButtonOne;
    QCommandLinkButton *commandLinkButtonTwo;
    QCommandLinkButton *commandLinkButtonThree;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SpeedShowResult)
    {
        if (SpeedShowResult->objectName().isEmpty())
            SpeedShowResult->setObjectName(QString::fromUtf8("SpeedShowResult"));
        SpeedShowResult->resize(400, 500);
        SpeedShowResult->setMinimumSize(QSize(400, 500));
        SpeedShowResult->setUnifiedTitleAndToolBarOnMac(true);
        centralwidget = new QWidget(SpeedShowResult);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        textEditOne = new QTextEdit(centralwidget);
        textEditOne->setObjectName(QString::fromUtf8("textEditOne"));
        textEditOne->setGeometry(QRect(20, 60, 351, 341));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        textEditOne->setFont(font);
        textEditOne->setFrameShape(QFrame::NoFrame);
        textEditOne->setReadOnly(true);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 10, 151, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\215\216\346\226\207\344\270\255\345\256\213"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        commandLinkButtonOne = new QCommandLinkButton(centralwidget);
        commandLinkButtonOne->setObjectName(QString::fromUtf8("commandLinkButtonOne"));
        commandLinkButtonOne->setEnabled(true);
        commandLinkButtonOne->setGeometry(QRect(350, 10, 31, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/circulation.png"), QSize(), QIcon::Normal, QIcon::Off);
        commandLinkButtonOne->setIcon(icon);
        commandLinkButtonOne->setIconSize(QSize(20, 20));
        commandLinkButtonOne->setCheckable(false);
        commandLinkButtonTwo = new QCommandLinkButton(centralwidget);
        commandLinkButtonTwo->setObjectName(QString::fromUtf8("commandLinkButtonTwo"));
        commandLinkButtonTwo->setGeometry(QRect(90, 410, 81, 41));
        commandLinkButtonThree = new QCommandLinkButton(centralwidget);
        commandLinkButtonThree->setObjectName(QString::fromUtf8("commandLinkButtonThree"));
        commandLinkButtonThree->setGeometry(QRect(220, 410, 141, 41));
        SpeedShowResult->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SpeedShowResult);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 26));
        SpeedShowResult->setMenuBar(menubar);
        statusbar = new QStatusBar(SpeedShowResult);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SpeedShowResult->setStatusBar(statusbar);

        retranslateUi(SpeedShowResult);

        QMetaObject::connectSlotsByName(SpeedShowResult);
    } // setupUi

    void retranslateUi(QMainWindow *SpeedShowResult)
    {
        SpeedShowResult->setWindowTitle(QCoreApplication::translate("SpeedShowResult", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("SpeedShowResult", "<html><head/><body><p><span style=\" font-size:22pt; font-weight:600; color:#a9aa4c;\">\346\210\220\347\273\251\346\230\276\347\244\272</span></p></body></html>", nullptr));
        commandLinkButtonOne->setText(QString());
        commandLinkButtonTwo->setText(QCoreApplication::translate("SpeedShowResult", "\350\277\224\345\233\236", nullptr));
        commandLinkButtonThree->setText(QCoreApplication::translate("SpeedShowResult", "\346\270\205\347\251\272\347\273\237\350\256\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpeedShowResult: public Ui_SpeedShowResult {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPEEDSHOWRESULT_H
