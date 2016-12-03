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
        gui/mainwindow.cpp \
    machinetool.cpp \
    commandinterpreter.cpp \
    gui/points/addpointdialog.cpp \
    gui/points/mousetoselectionpointdialog.cpp \
    gui/points/editpointdialog.cpp

HEADERS  += gui/mainwindow.h \
    machinetool.h \
    commandinterpreter.h \
    command.h \
    vector.h \
    point.h \
    gui/points/addpointdialog.h \
    gui/points/mousetoselectionpointdialog.h \
    gui/points/editpointdialog.h

FORMS    += gui/mainwindow.ui \
    gui/points/addpointdialog.ui \
    gui/points/mousetoselectionpointdialog.ui \
    gui/points/editpointdialog.ui

win32:RC_FILE = application.rc


macx:ICON = $${PWD}/applicationOSX.icns

RESOURCES += \
    gui/images.qrc
