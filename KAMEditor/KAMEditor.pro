#-------------------------------------------------
#
# Project created by QtCreator 2016-10-08T10:16:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KAMEditor
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    machinetool.cpp \
    commandinterpreter.cpp

HEADERS  += mainwindow.h \
    machinetool.h \
    commandinterpreter.h \
    command.h \
    vector.h \
    point.h

FORMS    += mainwindow.ui

win32:RC_FILE = application.rc
