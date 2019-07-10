#-------------------------------------------------
#
# Project created by QtCreator 2016-10-08T10:16:38
#
#-------------------------------------------------

QT       += core gui
QT += opengl
QT += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SML
TEMPLATE = app

CONFIG += c++11

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
    gui/widgets/console.cpp \
    gui/candle_visualizer_dialog.cpp \
    libs/json_parser/json.cpp \
    libs/gpr/gcode_program.cpp \
    libs/gpr/parser.cpp \
    libs/candle_visualizer/drawers/gcodedrawer.cpp \
    libs/candle_visualizer/drawers/heightmapborderdrawer.cpp \
    libs/candle_visualizer/drawers/heightmapgriddrawer.cpp \
    libs/candle_visualizer/drawers/heightmapinterpolationdrawer.cpp \
    libs/candle_visualizer/drawers/origindrawer.cpp \
    libs/candle_visualizer/drawers/selectiondrawer.cpp \
    libs/candle_visualizer/parser/arcproperties.cpp \
    libs/candle_visualizer/parser/gcodeparser.cpp \
    libs/candle_visualizer/parser/gcodepreprocessorutils.cpp \
    libs/candle_visualizer/parser/gcodeviewparse.cpp \
    libs/candle_visualizer/parser/linesegment.cpp \
    libs/candle_visualizer/parser/pointsegment.cpp \
    libs/candle_visualizer/tables/gcodetablemodel.cpp \
    libs/candle_visualizer/tables/heightmaptablemodel.cpp \
    libs/simple_qt_logger/simpleQtLogger.cpp \
    libs/candle_visualizer/glwidget.cpp \
    libs/candle_visualizer/drawers/shaderdrawable.cpp \
    libs/candle_visualizer/drawers/tooldrawer.cpp \
    models/repository/repository.cpp \
    models/types/sensor/sensor.cpp \
    models/types/device/spindel.cpp \
    models/types/device/device.cpp \
    models/types/axis/axis.cpp \
    models/types/point/point.cpp \
    models/types/gcodes/file_reader/file_reader.cpp \
    models/types/gcodes/gcodes_file_manager/gcodes_file_manager.cpp \
    models/types/adapter/adapter.cpp \
    gui/widgets/gcodes_editor_widget.cpp \
    gui/widgets/sensors_display_widget.cpp \
    gui/widgets/sml_commands_list_widget.cpp \
    gui/widgets/sml_editor_tree_widget.cpp \
    gui/widgets/points_table_widget.cpp \
    gui/widgets/spindel_control_widget.cpp \
    gui/add_point_dialog.cpp \
    gui/utils/gcodes_syntax_highlighter.cpp \
    gui/sml_console_dialog.cpp \
    gui/to_selection_point_dialog.cpp \
    models/server/sml_server.cpp \
    models/services/adapters/monitor/adapters_monitor.cpp \
    models/services/devices/spindels/monitor/spindels_monitor.cpp \
    models/services/gcodes/monitor/gcodes_monitor.cpp \
    models/services/points/monitor/points_monitor.cpp \
    models/services/sensors/monitor/sensors_monitor.cpp \
    models/settings_manager/settings_manager.cpp \
    models/types/device/devices_buffer.cpp \
    models/types/device/support_device.cpp \
    models/types/exceptions/invalid_argument_exception.cpp \
    models/types/exceptions/invalid_configuration_exception.cpp \
    models/types/exceptions/out_of_range_exception.cpp \
    models/types/exceptions/synchronize_state_exception.cpp \
    models/types/point/points_manager.cpp \
    models/types/sensor/sensors_buffer.cpp \
    models/machine_tool.cpp \
    gui/utils/gcodes_visualizer.cpp \
    models/services/devices/spindels/switch/switch_spindel_interactor.cpp \
    models/services/program/prepare_execution_queue_interactor.cpp \
    gui/program_processing_dialog.cpp \
    models/services/axises/monitor/axises_monitor.cpp \
    models/types/errors/sml_error_flags.cpp \
    models/services/errors/error_flags_monitor.cpp

HEADERS  += gui/mainwindow.h \
    gui/widgets/console.h \
    libs/json_parser/json.h \
    libs/gpr/gcode_program.h \
    libs/gpr/parser.h \
    libs/candle_visualizer/glwidget.h \
    libs/candle_visualizer/drawers/shaderdrawable.h \
    libs/candle_visualizer/utils/interpolation.h \
    libs/candle_visualizer/utils/util.h \
    libs/candle_visualizer/drawers/tooldrawer.h \
    libs/candle_visualizer/drawers/gcodedrawer.h \
    libs/candle_visualizer/drawers/heightmapborderdrawer.h \
    libs/candle_visualizer/drawers/heightmapgriddrawer.h \
    libs/candle_visualizer/drawers/heightmapinterpolationdrawer.h \
    libs/candle_visualizer/drawers/origindrawer.h \
    libs/candle_visualizer/drawers/selectiondrawer.h \
    libs/candle_visualizer/parser/arcproperties.h \
    libs/candle_visualizer/parser/gcodeparser.h \
    libs/candle_visualizer/parser/gcodepreprocessorutils.h \
    libs/candle_visualizer/parser/gcodeviewparse.h \
    libs/candle_visualizer/parser/linesegment.h \
    libs/candle_visualizer/parser/pointsegment.h \
    libs/candle_visualizer/tables/gcodetablemodel.h \
    libs/candle_visualizer/tables/heightmaptablemodel.h \
    libs/simple_qt_logger/simpleQtLogger.h \
    models/repository/repository.h \
    models/types/structs.h \
    models/types/sensor/sensor.h \
    models/types/device/spindel.h \
    models/types/device/device.h \
    models/types/axis/axis.h \
    models/types/point/point.h \
    models/types/exceptions/exceptions.h \
    models/types/adapter/adapter.h \
    gui/widgets/gcodes_editor_widget.h \
    gui/widgets/sensors_display_widget.h \
    gui/widgets/sml_editor_tree_widget.h \
    gui/widgets/points_table_widget.h \
    gui/widgets/spindel_control_widget.h \
    gui/widgets/sml_commands_list_widget.h \
    gui/add_point_dialog.h \
    gui/candle_visualizer_dialog.h \
    gui/utils/gcodes_syntax_highlighter.h \
    gui/sml_console_dialog.h \
    gui/to_selection_point_dialog.h \
    models/services/adapters/monitor/adapters_monitor.h \
    models/services/devices/spindels/monitor/spindels_monitor.h \
    models/services/gcodes/monitor/gcodes_monitor.h \
    models/services/points/monitor/points_monitor.h \
    models/services/sensors/monitor/sensors_monitor.h \
    models/machine_tool.h \
    models/settings_manager/settings_manager.h \
    models/server/sml_server.h \
    models/types/device/devices_buffer.h \
    models/types/device/support_device.h \
    models/types/exceptions/invalid_argument_exception.h \
    models/types/exceptions/invalid_configuration_exception.h \
    models/types/exceptions/out_of_range_exception.h \
    models/types/exceptions/synchronize_state_exception.h \
    models/types/sensor/sensors_buffer.h \
    models/types/point/points_manager.h \
    models/types/gcodes/gcodes_file_manager/gcodes_file_manager.h \
    models/types/gcodes/file_reader/file_reader.h \
    models/server/u1_state.h \
    gui/utils/gcodes_visualizer.h \
    models/services/devices/spindels/switch/switch_spindel_interactor.h \
    models/services/program/prepare_execution_queue_interactor.h \
    models/server/u2_state.h \
    gui/program_processing_dialog.h \
    models/services/axises/monitor/axises_monitor.h \
    models/types/errors/sml_error_flags.h \
    models/services/errors/error_flags_monitor.h

FORMS    += gui/mainwindow.ui \
    gui/candle_visualizer_dialog.ui \
    gui/add_point_dialog.ui \
    gui/sml_console_dialog.ui \
    gui/to_selection_point_dialog.ui \
    options/kabriol_window.ui \
    options/lubrication_system_window.ui \
    options/tool_length_sensor_window.ui \
    gui/program_processing_dialog.ui

win32:RC_FILE = application.rc
macx:ICON = $${PWD}/sml_logo.icns

RESOURCES += \
    gui/resources/images.qrc \
    libs/candle_visualizer/shaders.qrc

DISTFILES += \
    machinetool/components/movementController/about.txt \
    sml_logo.icns \
    libs/candle_visualizer/shaders/fshader.glsl \
    libs/candle_visualizer/shaders/vshader.glsl
