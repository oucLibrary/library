#-------------------------------------------------
#
# Project created by QtCreator 2016-11-16T20:35:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = oucLibrary
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    dbdemo.cpp \
    login.cpp \
    register.cpp \
    tablewidget.cpp \
    PageWidget.cpp \
    changeperson.cpp \
    dialog.cpp \
    test.cpp

HEADERS  += widget.h \
    dbdemo.h \
    login.h \
    register.h \
    tablewidget.h \
    pagewidget.h \
    changeperson.h \
    dialog.h \
    test.h

FORMS    += \
    PageWidget.ui \
    changeperson.ui \
    test.ui
