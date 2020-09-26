/********************************************************************************
** Form generated from reading UI file 'registerface.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERFACE_H
#define UI_REGISTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterFace
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEditOne;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEditTwo;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *RegisterFace)
    {
        if (RegisterFace->objectName().isEmpty())
            RegisterFace->setObjectName(QString::fromUtf8("RegisterFace"));
        RegisterFace->resize(400, 300);
        verticalLayout = new QVBoxLayout(RegisterFace);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        widget = new QWidget(RegisterFace);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(140, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        lineEditOne = new QLineEdit(widget);
        lineEditOne->setObjectName(QString::fromUtf8("lineEditOne"));
        lineEditOne->setMinimumSize(QSize(150, 25));

        horizontalLayout->addWidget(lineEditOne);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(RegisterFace);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(140, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        lineEditTwo = new QLineEdit(widget_2);
        lineEditTwo->setObjectName(QString::fromUtf8("lineEditTwo"));
        lineEditTwo->setMinimumSize(QSize(150, 25));
        lineEditTwo->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        horizontalLayout_2->addWidget(lineEditTwo);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(RegisterFace);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        verticalLayout->addWidget(widget_3);

        verticalSpacer_4 = new QSpacerItem(20, 90, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        retranslateUi(RegisterFace);

        QMetaObject::connectSlotsByName(RegisterFace);
    } // setupUi

    void retranslateUi(QWidget *RegisterFace)
    {
        RegisterFace->setWindowTitle(QCoreApplication::translate("RegisterFace", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterFace: public Ui_RegisterFace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERFACE_H
