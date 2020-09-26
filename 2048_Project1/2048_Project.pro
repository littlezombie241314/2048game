#-------------------------------------------------
#
# Project created by QtCreator 2020-07-29T09:04:29
#
#-------------------------------------------------

QT       += core gui multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2048_Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    selectlevel.cpp \
    classmodel.cpp \
    registerface.cpp \
    classshowresult.cpp \
    speedmodel.cpp \
    speedshowresult.cpp \
    mybutton.cpp

HEADERS  += mainwindow.h \
    selectlevel.h \
    classmodel.h \
    registerface.h \
    classshowresult.h \
    speedmodel.h \
    speedshowresult.h \
    mybutton.h

FORMS    += mainwindow.ui \
    registerface.ui \
    classshowresult.ui \
    speedmodel.ui \
    speedshowresult.ui
CONFIG += c++11

RESOURCES += \
    res.qrc
CONFIG += resources_big
