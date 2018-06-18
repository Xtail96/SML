#-------------------------------------------------
#
# Project created by QtCreator 2016-10-08T10:16:38
#
#-------------------------------------------------

QT       += core gui
QT += opengl
QT += websockets

#unix {
#    QT += webenginewidgets
#}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SML
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
    libs/jsonparser/json.cpp \
    libs/gpr/gcode_program.cpp \
    libs/gpr/parser.cpp \
    gui/widgets/console.cpp \
    gui/widgets/gcodeseditorwidget.cpp \
    gui/widgets/gcodesviewwidget.cpp \
    gui/widgets/smlcommandslistwidget.cpp \
    gui/widgets/smleditortreewidget.cpp \
    gui/widgets/smlpointstablewidget.cpp \
    #gui/gcodeswebviewdialog.cpp \
    gui/gcodessyntaxhighlighter.cpp \
    gui/logdialog.cpp \
    #gui/addpointdialog.cpp \
    gui/toselectionpointdialog.cpp \
    gui/smlconsoledialog.cpp \
    libs/candlevisualizer/glwidget.cpp \
    libs/candlevisualizer/drawers/shaderdrawable.cpp \
    libs/candlevisualizer/drawers/tooldrawer.cpp \
    gui/candlevisualizerdialog.cpp \
    libs/candlevisualizer/drawers/gcodedrawer.cpp \
    libs/candlevisualizer/drawers/heightmapborderdrawer.cpp \
    libs/candlevisualizer/drawers/heightmapgriddrawer.cpp \
    libs/candlevisualizer/drawers/heightmapinterpolationdrawer.cpp \
    libs/candlevisualizer/drawers/origindrawer.cpp \
    libs/candlevisualizer/drawers/selectiondrawer.cpp \
    libs/candlevisualizer/parser/arcproperties.cpp \
    libs/candlevisualizer/parser/gcodeparser.cpp \
    libs/candlevisualizer/parser/gcodepreprocessorutils.cpp \
    libs/candlevisualizer/parser/gcodeviewparse.cpp \
    libs/candlevisualizer/parser/linesegment.cpp \
    libs/candlevisualizer/parser/pointsegment.cpp \
    libs/candlevisualizer/tables/gcodetablemodel.cpp \
    libs/candlevisualizer/tables/heightmaptablemodel.cpp \
    libs/simpleqtlogger/simpleQtLogger.cpp \
    gui/widgets/spindelcontrolwidget.cpp \
    gui/widgets/sensorsdisplaywidget.cpp \
    models/repository/repository.cpp \
    models/machinetool.cpp \
    models/types/settingsmanager/settingsmanager.cpp \
    models/types/server/smlserver.cpp \
    models/types/sensor/sensor.cpp \
    models/types/device/supportdevice.cpp \
    models/types/device/spindel.cpp \
    models/types/device/device.cpp \
    models/types/axis/axis.cpp \
    models/types/point/pointsbuilder.cpp \
    models/types/point/point.cpp \
    models/types/sensor/sensorsbuffer.cpp \
    models/types/device/devicesbuffer.cpp \
    models/types/connection/connection.cpp \
    models/services/connections/connectionsmonitor.cpp

HEADERS  += gui/mainwindow.h \
    libs/jsonparser/json.h \
    libs/gpr/gcode_program.h \
    libs/gpr/parser.h \
    gui/widgets/console.h \
    gui/widgets/gcodeseditorwidget.h \
    gui/widgets/gcodesviewwidget.h \
    gui/widgets/smlcommandslistwidget.h \
    gui/widgets/smleditortreewidget.h \
    gui/widgets/smlpointstablewidget.h \
    #gui/gcodeswebviewdialog.h \
    gui/gcodessyntaxhighlighter.h \
    gui/logdialog.h \
    #gui/addpointdialog.h \
    gui/toselectionpointdialog.h \
    gui/smlconsoledialog.h \
    libs/candlevisualizer/glwidget.h \
    libs/candlevisualizer/drawers/shaderdrawable.h \
    libs/candlevisualizer/utils/interpolation.h \
    libs/candlevisualizer/utils/util.h \
    libs/candlevisualizer/drawers/tooldrawer.h \
    gui/candlevisualizerdialog.h \
    libs/candlevisualizer/drawers/gcodedrawer.h \
    libs/candlevisualizer/drawers/heightmapborderdrawer.h \
    libs/candlevisualizer/drawers/heightmapgriddrawer.h \
    libs/candlevisualizer/drawers/heightmapinterpolationdrawer.h \
    libs/candlevisualizer/drawers/origindrawer.h \
    libs/candlevisualizer/drawers/selectiondrawer.h \
    libs/candlevisualizer/parser/arcproperties.h \
    libs/candlevisualizer/parser/gcodeparser.h \
    libs/candlevisualizer/parser/gcodepreprocessorutils.h \
    libs/candlevisualizer/parser/gcodeviewparse.h \
    libs/candlevisualizer/parser/linesegment.h \
    libs/candlevisualizer/parser/pointsegment.h \
    libs/candlevisualizer/tables/gcodetablemodel.h \
    libs/candlevisualizer/tables/heightmaptablemodel.h \
    libs/simpleqtlogger/simpleQtLogger.h \
    gui/widgets/spindelcontrolwidget.h \
    gui/widgets/sensorsdisplaywidget.h \
    models/repository/repository.h \
    models/machinetool.h \
    models/types/structs.h \
    models/types/settingsmanager/settingsmanager.h \
    models/types/server/smlserver.h \
    models/types/sensor/sensor.h \
    models/types/device/supportdevice.h \
    models/types/device/spindel.h \
    models/types/device/device.h \
    models/types/axis/axis.h \
    models/types/point/pointsbuilder.h \
    models/types/point/point.h \
    models/types/sensor/sensorsbuffer.h \
    models/types/device/devicesbuffer.h \
    models/types/server/u1state.h \
    models/types/connection/connection.h \
    models/services/connections/connectionsmonitor.h

FORMS    += gui/mainwindow.ui \
    #gui/addpointdialog.ui \
    gui/toselectionpointdialog.ui \
    gui/logdialog.ui \
    gui/gcodeswebviewdialog.ui \
    gui/smlconsoledialog.ui \
    gui/candlevisualizerdialog.ui \
    options/toollengthsensorwindow.ui \
    options/lubricationsystemwindow.ui \
    options/kabriolwindow.ui

win32:RC_FILE = application.rc
macx:ICON = $${PWD}/applicationOSX.icns

RESOURCES += \
    gui/resources/pages.qrc \
    gui/resources/images.qrc \
    libs/candlevisualizer/shaders.qrc

DISTFILES += \
    machinetool/components/movementController/about.txt \
    applicationOSX.icns \
    libs/candlevisualizer/shaders/fshader.glsl \
    libs/candlevisualizer/shaders/vshader.glsl
