#-------------------------------------------------
#
# Project created by QtCreator 2016-10-08T10:16:38
#
#-------------------------------------------------

QT       += core gui
QT += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SML
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        gui/mainwindow.cpp \
    gui/widgets/console.cpp \
    libs/json_parser/json.cpp \
    libs/gpr/gcode_program.cpp \
    libs/gpr/parser.cpp \
    libs/simple_qt_logger/simpleQtLogger.cpp \
    models/machine_tool_elements/adapter_refactor/adapter_connection.cpp \
    models/machine_tool_elements/adapter_refactor/adapter_gateway.cpp \
    models/machine_tool_elements/adapter_refactor/base_controller.cpp \
    models/machine_tool_elements/adapter_refactor/device_controller.cpp \
    models/machine_tool_elements/adapter_refactor/motion_controller.cpp \
    models/machine_tool_elements/adapter/server/sml_adapter_server.cpp \
    models/repository/repository.cpp \
    models/services/adapters/get_current_state/get_adapter_current_state_interactor.cpp \
    models/services/adapters/launcher/adapters_launcher.cpp \
    models/machine_tool_elements/sensor/sensor.cpp \
    models/machine_tool_elements/device/spindel.cpp \
    models/machine_tool_elements/device/device.cpp \
    models/machine_tool_elements/axis/axis.cpp \
    models/machine_tool_elements/point/point.cpp \
    models/machine_tool_elements/gcodes/file_reader/file_reader.cpp \
    models/machine_tool_elements/gcodes/gcodes_file_manager/gcodes_file_manager.cpp \
    models/machine_tool_elements/adapter/adapter.cpp \
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
    models/services/gcodes/view/gcodes_view_interactor.cpp \
    models/settings_manager/settings_manager.cpp \
    models/machine_tool_elements/device/devices_buffer.cpp \
    models/machine_tool_elements/device/support_device.cpp \
    models/exceptions/invalid_argument_exception.cpp \
    models/exceptions/invalid_configuration_exception.cpp \
    models/exceptions/out_of_range_exception.cpp \
    models/exceptions/synchronize_state_exception.cpp \
    models/machine_tool_elements/sensor/sensors_buffer.cpp \
    models/machine_tool.cpp \
    models/services/devices/spindels/switch/switch_spindel_interactor.cpp \
    models/services/gcodes/prepare_execution_queue/prepare_execution_queue_interactor.cpp \
    gui/program_processing_dialog.cpp \
    models/errors/sml_error_flags.cpp \
    testenv.cpp

HEADERS  += gui/mainwindow.h \
    gui/widgets/console.h \
    libs/json_parser/json.h \
    libs/gpr/gcode_program.h \
    libs/gpr/parser.h \
    libs/simple_qt_logger/simpleQtLogger.h \
    models/machine_tool_elements/adapter_refactor/adapter_connection.h \
    models/machine_tool_elements/adapter_refactor/adapter_gateway.h \
    models/machine_tool_elements/adapter_refactor/base_controller.h \
    models/machine_tool_elements/adapter_refactor/device_controller.h \
    models/machine_tool_elements/adapter_refactor/motion_controller.h \
    models/machine_tool_elements/adapter/server/sml_adapter_server.h \
    models/repository/repository.h \
    models/services/adapters/get_current_state/get_adapter_current_state_interactor.h \
    models/services/adapters/launcher/adapters_launcher.h \
    models/services/gcodes/view/gcodes_view_interactor.h \
    models/structs.h \
    models/machine_tool_elements/sensor/sensor.h \
    models/machine_tool_elements/device/spindel.h \
    models/machine_tool_elements/device/device.h \
    models/machine_tool_elements/axis/axis.h \
    models/machine_tool_elements/point/point.h \
    models/exceptions/exceptions.h \
    models/machine_tool_elements/adapter/adapter.h \
    gui/widgets/gcodes_editor_widget.h \
    gui/widgets/sensors_display_widget.h \
    gui/widgets/sml_editor_tree_widget.h \
    gui/widgets/points_table_widget.h \
    gui/widgets/spindel_control_widget.h \
    gui/widgets/sml_commands_list_widget.h \
    gui/add_point_dialog.h \
    gui/utils/gcodes_syntax_highlighter.h \
    gui/sml_console_dialog.h \
    gui/to_selection_point_dialog.h \
    models/machine_tool.h \
    models/settings_manager/settings_manager.h \
    models/machine_tool_elements/device/devices_buffer.h \
    models/machine_tool_elements/device/support_device.h \
    models/exceptions/invalid_argument_exception.h \
    models/exceptions/invalid_configuration_exception.h \
    models/exceptions/out_of_range_exception.h \
    models/exceptions/synchronize_state_exception.h \
    models/machine_tool_elements/sensor/sensors_buffer.h \
    models/machine_tool_elements/gcodes/gcodes_file_manager/gcodes_file_manager.h \
    models/machine_tool_elements/gcodes/file_reader/file_reader.h \
    models/machine_tool_elements/adapter/server/u1_state.h \
    models/services/devices/spindels/switch/switch_spindel_interactor.h \
    models/services/gcodes/prepare_execution_queue/prepare_execution_queue_interactor.h \
    models/machine_tool_elements/adapter/server/u2_state.h \
    gui/program_processing_dialog.h \
    models/errors/sml_error_flags.h \
    testenv.h

FORMS    += gui/mainwindow.ui \
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

DISTFILES += \
    machinetool/components/movementController/about.txt \
    sml_logo.icns \
