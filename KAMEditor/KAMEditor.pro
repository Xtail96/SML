#-------------------------------------------------
#
# Project created by QtCreator 2016-10-08T10:16:38
#
#-------------------------------------------------

QT       += core gui opengl\
            sensors\
            serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KAMEditor
TEMPLATE = app

CONFIG += c++11

win32 {
  LIBS += -lglu32 -lopengl32
  LIBS += -L"$$PWD/libusb/libs"
  LIBS += -llibusb-1.0.dll
}
macx {
  LIBS += -framework OpenGl
  LIBS += -L"$$PWD/libusb/libs"
  LIBS += -lusb-1.0
}
unix {
  LIBS += -lusb-1.0
}

SOURCES += main.cpp\
        gui/mainwindow.cpp \
    gui/points/addpointdialog.cpp \
    gui/points/mousetoselectionpointdialog.cpp \
    gui/points/editpointdialog.cpp \
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
    models/machinetool/machinetool.cpp \
    models/machinetool/settingsmanager/settingsmanager.cpp \
    models/machinetool/movementhandler/axis/axis.cpp \
    models/machinetool/sensorsmanager/sensor/sensor.cpp \
    models/machinetool/devicesmanager/device/device.cpp \
#    machinetool/components/devices/spindel.cpp \
    models/machinetool/movementhandler/movementhandler.cpp \
    models/machinetool/pointsmanager/pointsmanager.cpp \
    models/machinetool/commandsinterpreter/commandsinterpreter.cpp \
    models/machinetool/commandsmanager/commandsmanager.cpp \
    models/machinetool/commandsmanager/commands/arc.cpp \
    models/machinetool/commandsmanager/commands/line.cpp \
    models/machinetool/movementhandler/dimensionsmanager/dimensionsmanager.cpp \
    models/controllerconnector/usbdevicemanager/usbdevicemanager.cpp \
    models/machinetool/pointsmanager/point/point.cpp \
    models/controllerconnector/debugmodule/debugmodule.cpp \
    models/controllerconnector/usbdevicemanager/usbdevice/usbdevice.cpp \
    models/controllerconnector/usbdevicemanager/usbdevice/kflop.cpp \
    models/controllerconnector/usbdevicemanager/usbdevice/u1.cpp

HEADERS  += gui/mainwindow.h \
    gui/points/addpointdialog.h \
    gui/points/mousetoselectionpointdialog.h \
    gui/points/editpointdialog.h \
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
    models/structs.h \
    models/machinetool/machinetool.h \
    models/machinetool/settingsmanager/settingsmanager.h \
    models/machinetool/movementhandler/axis/axis.h \
    models/machinetool/sensorsmanager/sensor/sensor.h \
    models/machinetool/devicesmanager/device/device.h \
#    machinetool/components/devices/spindel.h \
    models/machinetool/movementhandler/movementhandler.h \
    models/machinetool/pointsmanager/pointsmanager.h \
    models/machinetool/commandsinterpreter/commandsinterpreter.h \
    models/machinetool/commandsmanager/commandsmanager.h \
    models/machinetool/commandsmanager/commands/arc.h \
    models/machinetool/commandsmanager/commands/line.h \
    models/machinetool/movementhandler/dimensionsmanager/dimensionsmanager.h \
    models/controllerconnector/usbdevicemanager/usbdevicemanager.h \
    models/machinetool/pointsmanager/point/point.h \
    models/controllerconnector/debugmodule/debugmodule.h \
    models/controllerconnector/usbdevicemanager/usbdevice/usbdevice.h \
    models/controllerconnector/usbdevicemanager/usbdevice/kflop.h \
    models/controllerconnector/usbdevicemanager/usbdevice/u1.h


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

DISTFILES += \
    machinetool/components/movementController/about.txt
