#-------------------------------------------------
#
# Project created by QtCreator 2016-07-28T09:08:26
# Copyright: lwher
# Date: 2016-8-9
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chinese_Chess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    classes.cpp \
    ui_show.cpp \
    rules.cpp \
    ai.cpp \
    ai_hard.cpp

HEADERS  += mainwindow.h \
    classes.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    picture_source.qrc
