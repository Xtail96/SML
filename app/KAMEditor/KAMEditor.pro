#-------------------------------------------------
#
# Project created by QtCreator 2016-10-08T10:16:38
#
#-------------------------------------------------

QT       += core gui
QT += opengl
QT += webenginewidgets
QT += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KAMEditor
TEMPLATE = app

CONFIG += c++11

win32 {
  #LIBS += -lglu32 -lopengl32
}
macx {
  #LIBS += -framework OpenGl
}
unix {
}


SOURCES += main.cpp\
        views/mainwindow.cpp \
    models/settingsmanager/settingsmanager.cpp \
    presenters/mainwindowpresenter/mainwindowpresenter.cpp \
    presenters/mainwindowpresenter/mainwindowbridge/mainwindowbridge.cpp \
    libs/jsonparser/json.cpp \
    libs/gpr/gcode_program.cpp \
    libs/gpr/parser.cpp \
    models/serverconnectionmanager/serverconnectionmanager.cpp \
    models/devicesmanager/devicesmanager.cpp \
    models/devicesmanager/device/device.cpp \
    models/sensorsmanager/sensorsmanager.cpp \
    models/sensorsmanager/sensor/sensor.cpp \
    models/filesmanager/gcodesfilesmanager/gcodesfilesmanager.cpp \
    models/gcodesmanager/gcodesmanager.cpp \
    models/pointsmanager/pointsmanager.cpp \
    models/pointsmanager/point/point.cpp \
    models/pointsmanager/point/pointsbuilder.cpp \
    views/widgets/console.cpp \
    views/widgets/gcodeseditorwidget.cpp \
    views/widgets/gcodesviewwidget.cpp \
    views/widgets/smlcommandslistwidget.cpp \
    views/widgets/smleditortreewidget.cpp \
    views/widgets/smlpointstablewidget.cpp \
    views/gcodeswebviewdialog.cpp \
    views/gcodessyntaxhighlighter.cpp \
    views/logdialog.cpp \
    views/points/addpointdialog.cpp \
    views/points/toselectionpointdialog.cpp \
    views/smlconsoledialog.cpp

HEADERS  += views/mainwindow.h \
    models/settingsmanager/settingsmanager.h \
    models/structs.h \
    presenters/mainwindowpresenter/mainwindowpresenter.h \
    presenters/mainwindowpresenter/mainwindowbridge/mainwindowbridge.h \
    libs/jsonparser/json.h \
    libs/gpr/gcode_program.h \
    libs/gpr/parser.h \
    models/serverconnectionmanager/serverconnectionmanager.h \
    models/devicesmanager/devicesmanager.h \
    models/devicesmanager/device/device.h \
    models/sensorsmanager/sensorsmanager.h \
    models/sensorsmanager/sensor/sensor.h \
    models/structs.h \
    models/filesmanager/gcodesfilesmanager/gcodesfilesmanager.h \
    models/gcodesmanager/gcodesmanager.h \
    models/pointsmanager/pointsmanager.h \
    models/pointsmanager/point/point.h \
    models/pointsmanager/point/pointsbuilder.h \
    views/widgets/console.h \
    views/widgets/gcodeseditorwidget.h \
    views/widgets/gcodesviewwidget.h \
    views/widgets/smlcommandslistwidget.h \
    views/widgets/smleditortreewidget.h \
    views/widgets/smlpointstablewidget.h \
    views/gcodeswebviewdialog.h \
    views/gcodessyntaxhighlighter.h \
    views/logdialog.h \
    views/points/addpointdialog.h \
    views/points/toselectionpointdialog.h \
    views/smlconsoledialog.h

FORMS    += views/mainwindow.ui \
    views/points/addpointdialog.ui \
    views/points/toselectionpointdialog.ui \
    views/logdialog.ui \
    views/gcodeswebviewdialog.ui \
    views/smlconsoledialog.ui \

win32:RC_FILE = application.rc
macx:ICON = $${PWD}/applicationOSX.icns

RESOURCES += \
    views/resources/pages.qrc \
    views/resources/images.qrc

DISTFILES += \
    machinetool/components/movementController/about.txt \
    applicationOSX.icns
