#-------------------------------------------------
#
# Project created by QtCreator 2016-10-08T10:16:38
#
#-------------------------------------------------

QT       += core gui opengl\
            sensors

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KAMEditor
TEMPLATE = app

CONFIG += c++11

win32 {
  LIBS += -lglu32 -lopengl32
}
macx {
  LIBS += -framework OpenGl
}

SOURCES += main.cpp\
        gui/mainwindow.cpp \
    machinetool/machinetool.cpp \
    gui/points/addpointdialog.cpp \
    gui/points/mousetoselectionpointdialog.cpp \
    gui/points/editpointdialog.cpp \
    editor/pointsEditor/pointsManager/pointsmanager.cpp \
#    gui/commands/linedialog.cpp \
#    gui/commands/arcdialog.cpp \
#    gui/commands/labeldialog.cpp \
#    gui/commands/ttlinedialog.cpp \
#    gui/commands/arc2dialog.cpp \
#    gui/commands/cycledialog.cpp \
#    gui/commands/offdialog.cpp \
#    gui/commands/ondialog.cpp \
#    gui/commands/rotatedialog.cpp \
#    gui/commands/gotodialog.cpp \
#    gui/commands/procdialog.cpp \
#    gui/commands/callprocdialog.cpp \
#    gui/commands/commanddialog.cpp \
#    gui/commands/scaledialog.cpp \
#    gui/commands/velocitydialog.cpp \
#    gui/commands/pausedialog.cpp \
#    gui/commands/stopdialog.cpp \
#    gui/commands/commentdialog.cpp \
#    gui/commands/ttzarcdialog.cpp \
#    gui/commands/tttarcdialog.cpp \
#    gui/commands/splinedialog.cpp \
#    gui/commands/ttttsplinedialog.cpp \
    gui/commands/adddevicedialog.cpp \
    gui/gcodessyntaxhighlighter.cpp \
    gui/oglwidget.cpp \
    editor/commands/commandinterpreter.cpp \
    editor/commands/arc.cpp \
    editor/commands/line.cpp \
    machinetool/settings/settingsManager/settingsmanager.cpp \
    machinetool/components/axis/axis.cpp \
    machinetool/components/sensors/sensor.cpp \
    machinetool/components/devices/device.cpp \
    mcuLinksProvider/controllerConnector/controllerconnector.cpp \
    machinetool/components/devices/spindel.cpp \
    mcuLinksProvider/binaryMaskHandler/binaryMaskHandler.cpp

HEADERS  += gui/mainwindow.h \
    machinetool/machinetool.h \
    editor/pointsEditor/point/point.h \
    gui/points/addpointdialog.h \
    gui/points/mousetoselectionpointdialog.h \
    gui/points/editpointdialog.h \
    editor/pointsEditor/pointsManager/pointsmanager.h \
#    gui/commands/linedialog.h \
#    gui/commands/arcdialog.h \
#    gui/commands/labeldialog.h \
#    gui/commands/ttlinedialog.h \
#    gui/commands/arc2dialog.h \
#    gui/commands/cycledialog.h \
#    gui/commands/offdialog.h \
#    gui/commands/ondialog.h \
#    gui/commands/rotatedialog.h \
#    gui/commands/gotodialog.h \
#    gui/commands/procdialog.h \
#    gui/commands/callprocdialog.h \
#    gui/commands/commanddialog.h \
#    gui/commands/scaledialog.h \
#    gui/commands/velocitydialog.h \
#    gui/commands/pausedialog.h \
#    gui/commands/stopdialog.h \
#    gui/commands/commentdialog.h \
#    gui/commands/ttzarcdialog.h \
#    gui/commands/tttarcdialog.h \
#    gui/commands/splinedialog.h \
#    gui/commands/ttttsplinedialog.h \
    gui/commands/adddevicedialog.h \
    gui/gcodessyntaxhighlighter.h \
    gui/oglwidget.h \
    editor/commands/command.h \
    editor/commands/commands.h \
    editor/commands/commandinterpreter.h \
    editor/commands/arc.h \
    editor/commands/line.h \
    machinetool/settings/settingsManager/settingsmanager.h \
    structs.h \
    machinetool/components/axis/axis.h \
    machinetool/components/sensors/sensor.h \
    machinetool/components/devices/device.h \
    mcuLinksProvider/controllerConnector/controllerconnector.h \
    machinetool/components/devices/spindel.h \
    mcuLinksProvider/binaryMaskHandler/binaryMaskHandler.h

FORMS    += gui/mainwindow.ui \
    gui/points/addpointdialog.ui \
    gui/points/mousetoselectionpointdialog.ui \
    gui/points/editpointdialog.ui \
    gui/commands/adddevicedialog.ui \
#    gui/commands/linedialog.ui \
#    gui/commands/arcdialog.ui \
#    gui/commands/labeldialog.ui \
#    gui/commands/ttlinedialog.ui \
#    gui/commands/arc2dialog.ui \
#    gui/commands/cycledialog.ui \
#    gui/commands/offdialog.ui \
#    gui/commands/ondialog.ui \
#    gui/commands/rotatedialog.ui \
#    gui/commands/gotodialog.ui \
#    gui/commands/procdialog.ui \
#    gui/commands/callprocdialog.ui \
#    gui/commands/scaledialog.ui \
#    gui/commands/velocitydialog.ui \
#    gui/commands/pausedialog.ui \
#    gui/commands/stopdialog.ui \
#    gui/commands/commentdialog.ui \
#    gui/commands/ttzarcdialog.ui \
#    gui/commands/tttarcdialog.ui \
#    gui/commands/splinedialog.ui \
#    gui/commands/ttttsplinedialog.ui

win32:RC_FILE = application.rc
macx:ICON = $${PWD}/applicationOSX.icns

RESOURCES += \
    gui/images.qrc
