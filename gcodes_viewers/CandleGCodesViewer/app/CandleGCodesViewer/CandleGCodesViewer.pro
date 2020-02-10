QT += gui
QT += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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

SOURCES += \
        libs/candle_visualizer/drawers/gcodedrawer.cpp \
        libs/candle_visualizer/drawers/heightmapborderdrawer.cpp \
        libs/candle_visualizer/drawers/heightmapgriddrawer.cpp \
        libs/candle_visualizer/drawers/heightmapinterpolationdrawer.cpp \
        libs/candle_visualizer/drawers/origindrawer.cpp \
        libs/candle_visualizer/drawers/selectiondrawer.cpp \
        libs/candle_visualizer/drawers/shaderdrawable.cpp \
        libs/candle_visualizer/drawers/tooldrawer.cpp \
        libs/candle_visualizer/glwidget.cpp \
        libs/candle_visualizer/parser/arcproperties.cpp \
        libs/candle_visualizer/parser/gcodeparser.cpp \
        libs/candle_visualizer/parser/gcodepreprocessorutils.cpp \
        libs/candle_visualizer/parser/gcodeviewparse.cpp \
        libs/candle_visualizer/parser/linesegment.cpp \
        libs/candle_visualizer/parser/pointsegment.cpp \
        libs/candle_visualizer/tables/gcodetablemodel.cpp \
        libs/candle_visualizer/tables/heightmaptablemodel.cpp \
        main.cpp \
        widget/candle_visualizer_dialog.cpp \
        widget/gcodes_visualizer.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    widget/candle_visualizer_dialog.ui

HEADERS += \
    libs/candle_visualizer/drawers/gcodedrawer.h \
    libs/candle_visualizer/drawers/heightmapborderdrawer.h \
    libs/candle_visualizer/drawers/heightmapgriddrawer.h \
    libs/candle_visualizer/drawers/heightmapinterpolationdrawer.h \
    libs/candle_visualizer/drawers/origindrawer.h \
    libs/candle_visualizer/drawers/selectiondrawer.h \
    libs/candle_visualizer/drawers/shaderdrawable.h \
    libs/candle_visualizer/drawers/tooldrawer.h \
    libs/candle_visualizer/glwidget.h \
    libs/candle_visualizer/parser/arcproperties.h \
    libs/candle_visualizer/parser/gcodeparser.h \
    libs/candle_visualizer/parser/gcodepreprocessorutils.h \
    libs/candle_visualizer/parser/gcodeviewparse.h \
    libs/candle_visualizer/parser/linesegment.h \
    libs/candle_visualizer/parser/pointsegment.h \
    libs/candle_visualizer/tables/gcodetablemodel.h \
    libs/candle_visualizer/tables/heightmaptablemodel.h \
    libs/candle_visualizer/utils/interpolation.h \
    libs/candle_visualizer/utils/util.h \
    widget/candle_visualizer_dialog.h \
    widget/gcodes_visualizer.h

RESOURCES += \
    libs/candle_visualizer/shaders.qrc \
    resources/resources.qrc

DISTFILES += \
    libs/candle_visualizer/shaders/fshader.glsl \
    libs/candle_visualizer/shaders/vshader.glsl
