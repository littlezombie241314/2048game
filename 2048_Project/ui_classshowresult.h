/********************************************************************************
** Form generated from reading UI file 'classshowresult.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLASSSHOWRESULT_H
#define UI_CLASSSHOWRESULT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClassShowResult
{
public:
    QCommandLinkButton *commandLinkButtonOne;
    QTextEdit *textEditOne;
    QLabel *labelOne;
    QCommandLinkButton *commandLinkButtonTwo;
    QCommandLinkButton *commandLinkButtonThree;

    void setupUi(QWidget *ClassShowResult)
    {
        if (ClassShowResult->objectName().isEmpty())
            ClassShowResult->setObjectName(QString::fromUtf8("ClassShowResult"));
        ClassShowResult->resize(400, 500);
        ClassShowResult->setMinimumSize(QSize(400, 500));
        commandLinkButtonOne = new QCommandLinkButton(ClassShowResult);
        commandLinkButtonOne->setObjectName(QString::fromUtf8("commandLinkButtonOne"));
        commandLinkButtonOne->setGeometry(QRect(90, 430, 81, 41));
        textEditOne = new QTextEdit(ClassShowResult);
        textEditOne->setObjectName(QString::fromUtf8("textEditOne"));
        textEditOne->setGeometry(QRect(13, 60, 371, 361));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        textEditOne->setFont(font);
        textEditOne->setFrameShape(QFrame::NoFrame);
        textEditOne->setReadOnly(true);
        labelOne = new QLabel(ClassShowResult);
        labelOne->setObjectName(QString::fromUtf8("labelOne"));
        labelOne->setGeometry(QRect(100, 0, 191, 51));
        labelOne->setFrameShape(QFrame::Box);
        labelOne->setLineWidth(0);
        labelOne->setTextFormat(Qt::AutoText);
        labelOne->setMargin(1);
        labelOne->setIndent(5);
        commandLinkButtonTwo = new QCommandLinkButton(ClassShowResult);
        commandLinkButtonTwo->setObjectName(QString::fromUtf8("commandLinkButtonTwo"));
        commandLinkButtonTwo->setGeometry(QRect(360, 0, 31, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/circulation.png"), QSize(), QIcon::Normal, QIcon::Off);
        commandLinkButtonTwo->setIcon(icon);
        commandLinkButtonThree = new QCommandLinkButton(ClassShowResult);
        commandLinkButtonThree->setObjectName(QString::fromUtf8("commandLinkButtonThree"));
        commandLinkButtonThree->setGeometry(QRect(210, 430, 121, 41));
        commandLinkButtonThree->setAutoRepeatDelay(300);

        retranslateUi(ClassShowResult);

        QMetaObject::connectSlotsByName(ClassShowResult);
    } // setupUi

    void retranslateUi(QWidget *ClassShowResult)
    {
        ClassShowResult->setWindowTitle(QCoreApplication::translate("ClassShowResult", "Form", nullptr));
        commandLinkButtonOne->setText(QCoreApplication::translate("ClassShowResult", "\350\277\224\345\233\236", nullptr));
        labelOne->setText(QCoreApplication::translate("ClassShowResult", "<html><head/><body><p><span style=\" font-size:26pt; font-weight:600; color:#ffba4b;\">\346\270\270\346\210\217\346\210\220\347\273\251</span></p></body></html>", nullptr));
        commandLinkButtonTwo->setText(QString());
        commandLinkButtonThree->setText(QCoreApplication::translate("ClassShowResult", "\346\270\205\347\251\272\347\273\237\350\256\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClassShowResult: public Ui_ClassShowResult {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLASSSHOWRESULT_H
