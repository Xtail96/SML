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
        gui/mainwindow.cpp \
    models/settingsmanager/settingsmanager.cpp \
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
    gui/widgets/console.cpp \
    gui/widgets/gcodeseditorwidget.cpp \
    gui/widgets/gcodesviewwidget.cpp \
    gui/widgets/smlcommandslistwidget.cpp \
    gui/widgets/smleditortreewidget.cpp \
    gui/widgets/smlpointstablewidget.cpp \
    gui/gcodeswebviewdialog.cpp \
    gui/gcodessyntaxhighlighter.cpp \
    gui/logdialog.cpp \
    gui/addpointdialog.cpp \
    gui/toselectionpointdialog.cpp \
    gui/smlconsoledialog.cpp \
    gui/candlevisualizer/glwidget.cpp \
    gui/candlevisualizer/drawers/shaderdrawable.cpp \
    gui/candlevisualizer/drawers/tooldrawer.cpp \
    gui/candlevisualizerdialog.cpp \
    gui/candlevisualizer/drawers/gcodedrawer.cpp \
    gui/candlevisualizer/drawers/heightmapborderdrawer.cpp \
    gui/candlevisualizer/drawers/heightmapgriddrawer.cpp \
    gui/candlevisualizer/drawers/heightmapinterpolationdrawer.cpp \
    gui/candlevisualizer/drawers/origindrawer.cpp \
    gui/candlevisualizer/drawers/selectiondrawer.cpp \
    gui/candlevisualizer/parser/arcproperties.cpp \
    gui/candlevisualizer/parser/gcodeparser.cpp \
    gui/candlevisualizer/parser/gcodepreprocessorutils.cpp \
    gui/candlevisualizer/parser/gcodeviewparse.cpp \
    gui/candlevisualizer/parser/linesegment.cpp \
    gui/candlevisualizer/parser/pointsegment.cpp \
    gui/candlevisualizer/tables/gcodetablemodel.cpp \
    gui/candlevisualizer/tables/heightmaptablemodel.cpp \
    libs/simpleqtlogger/simpleQtLogger.cpp \
    models/axisesmanager/axis/axis.cpp \
    models/axisesmanager/axisesmanager.cpp \
    models/machinetool.cpp

HEADERS  += gui/mainwindow.h \
    models/settingsmanager/settingsmanager.h \
    models/structs.h \
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
    gui/widgets/console.h \
    gui/widgets/gcodeseditorwidget.h \
    gui/widgets/gcodesviewwidget.h \
    gui/widgets/smlcommandslistwidget.h \
    gui/widgets/smleditortreewidget.h \
    gui/widgets/smlpointstablewidget.h \
    gui/gcodeswebviewdialog.h \
    gui/gcodessyntaxhighlighter.h \
    gui/logdialog.h \
    gui/addpointdialog.h \
    gui/toselectionpointdialog.h \
    gui/smlconsoledialog.h \
    gui/candlevisualizer/glwidget.h \
    gui/candlevisualizer/drawers/shaderdrawable.h \
    gui/candlevisualizer/utils/interpolation.h \
    gui/candlevisualizer/utils/util.h \
    gui/candlevisualizer/drawers/tooldrawer.h \
    gui/candlevisualizerdialog.h \
    gui/candlevisualizer/drawers/gcodedrawer.h \
    gui/candlevisualizer/drawers/heightmapborderdrawer.h \
    gui/candlevisualizer/drawers/heightmapgriddrawer.h \
    gui/candlevisualizer/drawers/heightmapinterpolationdrawer.h \
    gui/candlevisualizer/drawers/origindrawer.h \
    gui/candlevisualizer/drawers/selectiondrawer.h \
    gui/candlevisualizer/parser/arcproperties.h \
    gui/candlevisualizer/parser/gcodeparser.h \
    gui/candlevisualizer/parser/gcodepreprocessorutils.h \
    gui/candlevisualizer/parser/gcodeviewparse.h \
    gui/candlevisualizer/parser/linesegment.h \
    gui/candlevisualizer/parser/pointsegment.h \
    gui/candlevisualizer/tables/gcodetablemodel.h \
    gui/candlevisualizer/tables/heightmaptablemodel.h \
    libs/simpleqtlogger/simpleQtLogger.h \
    models/axisesmanager/axis/axis.h \
    models/axisesmanager/axisesmanager.h \
    models/machinetool.h

FORMS    += gui/mainwindow.ui \
    gui/addpointdialog.ui \
    gui/toselectionpointdialog.ui \
    gui/logdialog.ui \
    gui/gcodeswebviewdialog.ui \
    gui/smlconsoledialog.ui \
    gui/candlevisualizerdialog.ui

win32:RC_FILE = application.rc
macx:ICON = $${PWD}/applicationOSX.icns

RESOURCES += \
    gui/resources/pages.qrc \
    gui/resources/images.qrc \
    gui/candlevisualizer/shaders.qrc

DISTFILES += \
    machinetool/components/movementController/about.txt \
    applicationOSX.icns \
    gui/candlevisualizer/shaders/fshader.glsl \
    gui/candlevisualizer/shaders/vshader.glsl
