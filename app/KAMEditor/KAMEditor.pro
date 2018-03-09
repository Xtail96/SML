#-------------------------------------------------
#
# Project created by QtCreator 2016-10-08T10:16:38
#
#-------------------------------------------------

QT       += core gui
QT += opengl
QT += websockets
unix {
    QT += webenginewidgets
}

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
unix {
}


# from candle project
DEFINES += sNan=\"65536\"

win32: {
    QT += winextras
    DEFINES += WINDOWS
    QMAKE_LFLAGS += "-Wl,--large-address-aware"
    QMAKE_CXXFLAGS_DEBUG += -g3 -pg
    QMAKE_LFLAGS_DEBUG += -pg -lgmon
}

unix:!macx {
    DEFINES += UNIX #GL_GLEXT_PROTOTYPES
    QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/libs\'"
}

contains(QT_CONFIG, opengles.) {
    warning("GL ES detected. VAO will be disabled.")
    DEFINES += GLES
    INSTALLS += target
}
#end

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
    views/smlconsoledialog.cpp \
    views/candlevisualizer/glwidget.cpp \
    views/candlevisualizer/drawers/shaderdrawable.cpp \
    views/candlevisualizer/drawers/tooldrawer.cpp \
    views/candlevisualizerdialog.cpp \
    views/candlevisualizer/drawers/gcodedrawer.cpp \
    views/candlevisualizer/drawers/heightmapborderdrawer.cpp \
    views/candlevisualizer/drawers/heightmapgriddrawer.cpp \
    views/candlevisualizer/drawers/heightmapinterpolationdrawer.cpp \
    views/candlevisualizer/drawers/origindrawer.cpp \
    views/candlevisualizer/drawers/selectiondrawer.cpp \
    views/candlevisualizer/parser/arcproperties.cpp \
    views/candlevisualizer/parser/gcodeparser.cpp \
    views/candlevisualizer/parser/gcodepreprocessorutils.cpp \
    views/candlevisualizer/parser/gcodeviewparse.cpp \
    views/candlevisualizer/parser/linesegment.cpp \
    views/candlevisualizer/parser/pointsegment.cpp

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
    views/smlconsoledialog.h \
    views/candlevisualizer/glwidget.h \
    views/candlevisualizer/drawers/shaderdrawable.h \
    views/candlevisualizer/utils/interpolation.h \
    views/candlevisualizer/utils/util.h \
    views/candlevisualizer/drawers/tooldrawer.h \
    views/candlevisualizerdialog.h \
    views/candlevisualizer/drawers/gcodedrawer.h \
    views/candlevisualizer/drawers/heightmapborderdrawer.h \
    views/candlevisualizer/drawers/heightmapgriddrawer.h \
    views/candlevisualizer/drawers/heightmapinterpolationdrawer.h \
    views/candlevisualizer/drawers/origindrawer.h \
    views/candlevisualizer/drawers/selectiondrawer.h \
    views/candlevisualizer/parser/arcproperties.h \
    views/candlevisualizer/parser/gcodeparser.h \
    views/candlevisualizer/parser/gcodepreprocessorutils.h \
    views/candlevisualizer/parser/gcodeviewparse.h \
    views/candlevisualizer/parser/linesegment.h \
    views/candlevisualizer/parser/pointsegment.h

FORMS    += views/mainwindow.ui \
    views/points/addpointdialog.ui \
    views/points/toselectionpointdialog.ui \
    views/logdialog.ui \
    views/gcodeswebviewdialog.ui \
    views/smlconsoledialog.ui \
    views/candlevisualizerdialog.ui

win32:RC_FILE = application.rc
macx:ICON = $${PWD}/applicationOSX.icns

RESOURCES += \
    views/resources/pages.qrc \
    views/resources/images.qrc \
    views/candlevisualizer/shaders.qrc

DISTFILES += \
    machinetool/components/movementController/about.txt \
    applicationOSX.icns \
    views/candlevisualizer/shaders/fshader.glsl \
    views/candlevisualizer/shaders/vshader.glsl
