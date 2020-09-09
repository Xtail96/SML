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
    libs/json_parser/json.cpp \
    libs/gpr/gcode_program.cpp \
    libs/gpr/parser.cpp \
    libs/simple_qt_logger/simpleQtLogger.cpp \
    models/machine_tool/controllers/adapters/adapter_connection.cpp \
    models/machine_tool/controllers/adapters/adapter_gateway.cpp \
    models/machine_tool/controllers/base_controller.cpp \
    models/machine_tool/controllers/device_controller/device_controller.cpp \
    models/machine_tool/controllers/motion_controller/motion_controller.cpp \
    models/machine_tool/controllers/registrator.cpp \
    models/services/adapters/launcher/adapters_launcher.cpp \
    models/machine_tool/controllers/device_controller/sensor/sensor.cpp \
    models/machine_tool/controllers/device_controller/device/spindel.cpp \
    models/machine_tool/controllers/device_controller/device/device.cpp \
    models/machine_tool/controllers/motion_controller/axis/axis.cpp \
    gui/widgets/gcodes_editor_widget.cpp \
    gui/widgets/sensors_display_widget.cpp \
    gui/widgets/sml_commands_list_widget.cpp \
    gui/widgets/sml_editor_tree_widget.cpp \
    gui/widgets/points_table_widget.cpp \
    gui/widgets/spindel_control_widget.cpp \
    gui/utils/gcodes_syntax_highlighter.cpp \
    models/services/gcodes/view/gcodes_view_interactor.cpp \
    models/settings_manager/settings_manager.cpp \
    models/machine_tool/controllers/device_controller/device/support_device.cpp \
    models/machine_tool/machine_tool.cpp

HEADERS  += gui/mainwindow.h \
    gui/utils/colors.h \
    libs/json_parser/json.h \
    libs/gpr/gcode_program.h \
    libs/gpr/parser.h \
    libs/simple_qt_logger/simpleQtLogger.h \
    models/machine_tool/controllers/adapters/adapter_connection.h \
    models/machine_tool/controllers/adapters/adapter_gateway.h \
    models/machine_tool/controllers/base_controller.h \
    models/machine_tool/controllers/device_controller/device_controller.h \
    models/machine_tool/controllers/motion_controller/motion_controller.h \
    models/machine_tool/controllers/registrator.h \
    models/services/adapters/launcher/adapters_launcher.h \
    models/services/gcodes/view/gcodes_view_interactor.h \
    models/machine_tool/controllers/device_controller/sensor/sensor.h \
    models/machine_tool/controllers/device_controller/device/spindel.h \
    models/machine_tool/controllers/device_controller/device/device.h \
    models/machine_tool/controllers/motion_controller/axis/axis.h \
    gui/widgets/gcodes_editor_widget.h \
    gui/widgets/sensors_display_widget.h \
    gui/widgets/sml_editor_tree_widget.h \
    gui/widgets/points_table_widget.h \
    gui/widgets/spindel_control_widget.h \
    gui/widgets/sml_commands_list_widget.h \
    gui/utils/gcodes_syntax_highlighter.h \
    models/machine_tool/machine_tool.h \
    models/settings_manager/settings_manager.h \
    models/machine_tool/controllers/device_controller/device/support_device.h

FORMS    += gui/mainwindow.ui

win32:RC_FILE = application.rc
macx:ICON = $${PWD}/sml_logo.icns

RESOURCES += \
    gui/resources/images.qrc \

DISTFILES += \
    machinetool/components/movementController/about.txt \
    sml_logo.icns \
