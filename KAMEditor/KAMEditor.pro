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
  LIBS += -L$$PWD/usbxpress/libs/ -lSiUSBXp
}
macx {
  LIBS += -framework OpenGl
  LIBS += -L"$$PWD/libusb/libs"
  LIBS += -lusb-1.0
}
unix {
  LIBS += -lusb-1.0
}

INCLUDEPATH += $$PWD/usbxpress/include
DEPENDPATH += $$PWD/usbxpress/include


SOURCES += main.cpp\
        gui/mainwindow.cpp \
    gui/points/addpointdialog.cpp \
    gui/commands/linedialog.cpp \
    gui/commands/arcdialog.cpp \
#    gui/commands/labeldialog.cpp \
    gui/commands/ttlinedialog.cpp \
#    gui/commands/arc2dialog.cpp \
#    gui/commands/cycledialog.cpp \
    gui/commands/offdialog.cpp \
    gui/commands/ondialog.cpp \
#    gui/commands/rotatedialog.cpp \
#    gui/commands/gotodialog.cpp \
#    gui/commands/procdialog.cpp \
#    gui/commands/callprocdialog.cpp \
#    gui/commands/commanddialog.cpp \
#    gui/commands/scaledialog.cpp \
#    gui/commands/velocitydialog.cpp \
    gui/commands/pausedialog.cpp \
#    gui/commands/stopdialog.cpp \
    gui/commands/commentdialog.cpp \
#    gui/commands/ttzarcdialog.cpp \
#    gui/commands/tttarcdialog.cpp \
#    gui/commands/splinedialog.cpp \
#    gui/commands/ttttsplinedialog.cpp \
    gui/gcodessyntaxhighlighter.cpp \
    gui/widgets/oglwidget.cpp \
    models/machinetool/machinetool.cpp \
    models/machinetool/settingsmanager/settingsmanager.cpp \
    models/machinetool/movementshandler/axis/axis.cpp \
    models/machinetool/sensorsmanager/sensor/sensor.cpp \
    models/machinetool/devicesmanager/device/device.cpp \
#    machinetool/components/devices/spindel.cpp \
    models/machinetool/movementshandler/movementhandler.cpp \
    models/machinetool/pointsmanager/pointsmanager.cpp \
    models/machinetool/commandsinterpreter/commandsinterpreter.cpp \
    models/machinetool/commandsmanager/commandsmanager.cpp \
    models/machinetool/commandsmanager/commands/arc.cpp \
    models/machinetool/commandsmanager/commands/line.cpp \
    models/machinetool/movementshandler/dimensionsmanager/dimensionsmanager.cpp \
    models/controllerconnector/usbdevicesmanager/usbdevicesmanager.cpp \
    models/machinetool/pointsmanager/point/point.cpp \
    models/controllerconnector/debugmodule/debugmodule.cpp \
    models/controllerconnector/usbdevicesmanager/usbdevice/usbdevice.cpp \
    models/controllerconnector/usbdevicesmanager/usbdevice/kflop.cpp \
    models/controllerconnector/usbdevicesmanager/usbdevice/u1.cpp \
    models/controllerconnector/usbxpressdevicesmanager/usbxpressdevice/usbxpressdevice.cpp \
    models/controllerconnector/usbxpressdevicesmanager/usbxpressdevicemanager.cpp \
    models/controllerconnector/usbxpressdevicesmanager/usbxpressdevice/silabsu1.cpp \
    models/machinetool/sensorsmanager/sensorsmanager.cpp \
    models/machinetool/devicesmanager/devicesmanager.cpp \
    models/machinetool/commandsmanager/commands/switchon.cpp \
    models/machinetool/commandsmanager/commands/switchoff.cpp \
    models/machinetool/commandsmanager/commands/comment.cpp \
    models/machinetool/commandsmanager/commands/pause.cpp \
    gui/points/toselectionpointdialog.cpp \
    models/machinetool/filemanager/filemanager.cpp \
    gui/options/kabriolwindow.cpp \
    gui/options/toollengthsensorwindow.cpp \
    gui/options/lubricationsystemwindow.cpp \
#    models/machinetool/commandsmanager/commands/ttline.cpp \
    gui/programvisualizewindow.cpp \
    controllers/mainwindowcontroller/mainwindowbridge/mainwindowbridge.cpp \
    controllers/mainwindowcontroller/mainwindowcontroller.cpp \
    controllers/programvisualizewindowcontroller/programvisualizewindowcontroller.cpp \
    controllers/programvisualizewindowcontroller/programvisualizewindowbridge/programvisualizewindowbridge.cpp \
    gui/widgets/smleditortreewidget.cpp \
    gui/widgets/smlcommandslistwidget.cpp \
    gui/widgets/smlpointstablewidget.cpp

HEADERS  += gui/mainwindow.h \
    gui/points/addpointdialog.h \
    gui/commands/linedialog.h \
    gui/commands/arcdialog.h \
#    gui/commands/labeldialog.h \
    gui/commands/ttlinedialog.h \
#    gui/commands/arc2dialog.h \
#    gui/commands/cycledialog.h \
    gui/commands/offdialog.h \
    gui/commands/ondialog.h \
#    gui/commands/rotatedialog.h \
#    gui/commands/gotodialog.h \
#    gui/commands/procdialog.h \
#    gui/commands/callprocdialog.h \
#    gui/commands/commanddialog.h \
#    gui/commands/scaledialog.h \
#    gui/commands/velocitydialog.h \
    gui/commands/pausedialog.h \
#    gui/commands/stopdialog.h \
    gui/commands/commentdialog.h \
#    gui/commands/ttzarcdialog.h \
#    gui/commands/tttarcdialog.h \
#    gui/commands/splinedialog.h \
#    gui/commands/ttttsplinedialog.h \
    gui/gcodessyntaxhighlighter.h \
    gui/widgets/oglwidget.h \
    models/structs.h \
    models/machinetool/machinetool.h \
    models/machinetool/settingsmanager/settingsmanager.h \
    models/machinetool/movementshandler/axis/axis.h \
    models/machinetool/sensorsmanager/sensor/sensor.h \
    models/machinetool/devicesmanager/device/device.h \
#    machinetool/components/devices/spindel.h \
    models/machinetool/pointsmanager/pointsmanager.h \
    models/machinetool/commandsinterpreter/commandsinterpreter.h \
    models/machinetool/commandsmanager/commandsmanager.h \
    models/machinetool/commandsmanager/commands/arc.h \
    models/machinetool/commandsmanager/commands/line.h \
    models/machinetool/commandsmanager/commands/commands.h \
    models/machinetool/commandsmanager/commands/command.h \
    models/machinetool/movementshandler/dimensionsmanager/dimensionsmanager.h \
    models/controllerconnector/usbdevicesmanager/usbdevicesmanager.h \
    models/machinetool/pointsmanager/point/point.h \
    models/controllerconnector/debugmodule/debugmodule.h \
    models/controllerconnector/usbdevicesmanager/usbdevice/usbdevice.h \
    models/controllerconnector/usbdevicesmanager/usbdevice/kflop.h \
    models/controllerconnector/usbdevicesmanager/usbdevice/u1.h \
    models/machinetool/movementshandler/movementshandler.h \
    models/controllerconnector/usbxpressdevicesmanager/usbxpressdevicemanager.h \
    models/controllerconnector/usbxpressdevicesmanager/usbxpressdevice/usbxpressdevice.h \
    dependencies.h \
    models/controllerconnector/usbxpressdevicesmanager/usbxpressdevice/silabsu1.h \
    models/machinetool/sensorsmanager/sensorsmanager.h \
    models/machinetool/devicesmanager/devicesmanager.h \
    models/machinetool/commandsmanager/commands/switchon.h \
    models/machinetool/commandsmanager/commands/switchoff.h \
    models/machinetool/commandsmanager/commands/comment.h \
    models/machinetool/commandsmanager/commands/pause.h \
    gui/points/toselectionpointdialog.h \
    models/machinetool/filemanager/filemanager.h \
    gui/options/kabriolwindow.h \
    gui/options/toollengthsensorwindow.h \
    gui/options/lubricationsystemwindow.h \
#    models/machinetool/commandsmanager/commands/ttline.h \
    gui/programvisualizewindow.h \
    controllers/mainwindowcontroller/mainwindowbridge/mainwindowbridge.h \
    controllers/mainwindowcontroller/mainwindowcontroller.h \
    controllers/programvisualizewindowcontroller/programvisualizewindowcontroller.h \
    controllers/programvisualizewindowcontroller/programvisualizewindowbridge/programvisualizewindowbridge.h \
    gui/widgets/smleditortreewidget.h \
    gui/widgets/smlcommandslistwidget.h \
    gui/widgets/smlpointstablewidget.h


FORMS    += gui/mainwindow.ui \
    gui/points/addpointdialog.ui \
    gui/commands/linedialog.ui \
    gui/commands/arcdialog.ui \
#    gui/commands/labeldialog.ui \
    gui/commands/ttlinedialog.ui \
#    gui/commands/arc2dialog.ui \
#    gui/commands/cycledialog.ui \
    gui/commands/offdialog.ui \
    gui/commands/ondialog.ui \
#    gui/commands/rotatedialog.ui \
#    gui/commands/gotodialog.ui \
#    gui/commands/procdialog.ui \
#    gui/commands/callprocdialog.ui \
#    gui/commands/scaledialog.ui \
#    gui/commands/velocitydialog.ui \
    gui/commands/pausedialog.ui \
#    gui/commands/stopdialog.ui \
    gui/commands/commentdialog.ui \
    gui/points/toselectionpointdialog.ui \
    gui/options/kabriolwindow.ui \
    gui/options/toollengthsensorwindow.ui \
    gui/options/lubricationsystemwindow.ui \
    gui/programvisualizewindow.ui
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
