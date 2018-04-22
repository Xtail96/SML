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
    models/axisesmanager/axis/axis.cpp \
    models/axisesmanager/axisesmanager.cpp \
    models/machinetool.cpp \
    options/toollengthsensorwindow.cpp \
    options/lubricationsystemwindow.cpp \
    options/kabriolwindow.cpp \
    models/serverManager/smlkameditorserver/smlkameditorserver.cpp \
    models/serverManager/servermanager.cpp \
    models/serverManager/smlkameditorserver/adapterscontainer/adapter/adapter.cpp \
    models/serverManager/smlkameditorserver/adapterscontainer/adapterscontainer.cpp

HEADERS  += gui/mainwindow.h \
    models/settingsmanager/settingsmanager.h \
    models/structs.h \
    libs/jsonparser/json.h \
    libs/gpr/gcode_program.h \
    libs/gpr/parser.h \
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
    models/axisesmanager/axis/axis.h \
    models/axisesmanager/axisesmanager.h \
    models/machinetool.h \
    options/toollengthsensorwindow.h \
    options/lubricationsystemwindow.h \
    options/kabriolwindow.h \
    models/serverManager/smlkameditorserver/smlkameditorserver.h \
    models/serverManager/servermanager.h \
    models/serverManager/smlkameditorserver/adapterscontainer/adapter/adapter.h \
    models/serverManager/smlkameditorserver/adapterscontainer/adapterscontainer.h

FORMS    += gui/mainwindow.ui \
    gui/addpointdialog.ui \
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
