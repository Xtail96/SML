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
    gui/points/addpointdialog.cpp \
    gui/points/mousetoselectionpointdialog.cpp \
    gui/points/editpointdialog.cpp \
    commandinterpreter.cpp \
    pointsmanager.cpp \
    commandhandler.cpp \
    gui/commands/linedialog.cpp \
    gui/commands/arcdialog.cpp \
    gui/commands/labeldialog.cpp \
    gui/commands/ttlinedialog.cpp \
    gui/commands/arc2dialog.cpp \
    gui/commands/tttlinedialog.cpp \
    gui/commands/cycledialog.cpp \
    gui/commands/offdialog.cpp \
    gui/commands/ondialog.cpp \
    gui/commands/rotatedialog.cpp \
    gui/commands/gotodialog.cpp \
    gui/commands/procdialog.cpp

HEADERS  += gui/mainwindow.h \
    machinetool.h \
    command.h \
    vector.h \
    point.h \
    gui/points/addpointdialog.h \
    gui/points/mousetoselectionpointdialog.h \
    gui/points/editpointdialog.h \
    commandinterpreter.h \
    pointsmanager.h \
    commandhandler.h \
    gui/commands/linedialog.h \
    gui/commands/arcdialog.h \
    gui/commands/labeldialog.h \
    gui/commands/ttlinedialog.h \
    gui/commands/arc2dialog.h \
    gui/commands/tttlinedialog.h \
    gui/commands/cycledialog.h \
    gui/commands/offdialog.h \
    gui/commands/ondialog.h \
    gui/commands/rotatedialog.h \
    gui/commands/gotodialog.h \
    gui/commands/procdialog.h

FORMS    += gui/mainwindow.ui \
    gui/points/addpointdialog.ui \
    gui/points/mousetoselectionpointdialog.ui \
    gui/points/editpointdialog.ui \
    gui/commands/linedialog.ui \
    gui/commands/arcdialog.ui \
    gui/commands/labeldialog.ui \
    gui/commands/ttlinedialog.ui \
    gui/commands/arc2dialog.ui \
    gui/commands/tttlinedialog.ui \
    gui/commands/cycledialog.ui \
    gui/commands/offdialog.ui \
    gui/commands/ondialog.ui \
    gui/commands/rotatedialog.ui \
    gui/commands/gotodialog.ui \
    gui/commands/procdialog.ui

win32:RC_FILE = application.rc


macx:ICON = $${PWD}/applicationOSX.icns

RESOURCES += \
    gui/images.qrc
