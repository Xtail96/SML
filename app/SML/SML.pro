#-------------------------------------------------
#
# Project created by QtCreator 2016-10-08T10:16:38
#
#-------------------------------------------------

QT       += core gui testlib
QT += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SML
TEMPLATE = app

CONFIG += c++11

DEFINES += QT_MESSAGELOGCONTEXT

SOURCES += main.cpp\
        gui/mainwindow.cpp \
    gui/utils/utils.cpp \
    gui/widgets/axis_push_button.cpp \
    hardware/controllers/motion_controller/axes_repository.cpp \
    libs/json_parser/json.cpp \
    libs/gpr/gcode_program.cpp \
    libs/gpr/parser.cpp \
    common/websockets/websocket_client.cpp \
    common/websockets/websocket_connection.cpp \
    common/websockets/websocket_gateway.cpp \
    hardware/controllers/base_controller.cpp \
    hardware/controllers/device_controller/device_controller.cpp \
    hardware/controllers/motion_controller/axis.cpp \
    hardware/controllers/motion_controller/motion_controller.cpp \
    hardware/controllers/registrator.cpp \
    hardware/controllers/task.cpp \
    hardware/hardware_driver.cpp \
    services/adapters_launcher.cpp \
    hardware/controllers/device_controller/sensor.cpp \
    hardware/controllers/device_controller/spindel.cpp \
    hardware/controllers/device_controller/device.cpp \
    gui/widgets/gcodes_editor_widget.cpp \
    gui/widgets/sensors_display_widget.cpp \
    gui/widgets/sml_commands_list_widget.cpp \
    gui/widgets/sml_editor_tree_widget.cpp \
    gui/widgets/points_table_widget.cpp \
    gui/widgets/spindel_control_widget.cpp \
    gui/utils/gcodes_syntax_highlighter.cpp \
    services/gcodes_view_interactor.cpp \
    common/settings/settings_manager.cpp \
    hardware/controllers/device_controller/support_device.cpp

HEADERS  += gui/mainwindow.h \
    common/interfaces/i_repository.h \
    gui/utils/colors.h \
    gui/utils/utils.h \
    gui/widgets/axis_push_button.h \
    hardware/controllers/motion_controller/axes_repository.h \
    libs/json_parser/json.h \
    libs/gpr/gcode_program.h \
    libs/gpr/parser.h \
    common/websockets/websocket_client.h \
    common/websockets/websocket_connection.h \
    common/websockets/websocket_gateway.h \
    hardware/controllers/base_controller.h \
    hardware/controllers/device_controller/device_controller.h \
    hardware/controllers/motion_controller/axis.h \
    hardware/controllers/motion_controller/motion_controller.h \
    hardware/controllers/registrator.h \
    hardware/controllers/task.h \
    hardware/hardware_driver.h \
    services/adapters_launcher.h \
    services/gcodes_view_interactor.h \
    hardware/controllers/device_controller/sensor.h \
    hardware/controllers/device_controller/spindel.h \
    hardware/controllers/device_controller/device.h \
    gui/widgets/gcodes_editor_widget.h \
    gui/widgets/sensors_display_widget.h \
    gui/widgets/sml_editor_tree_widget.h \
    gui/widgets/points_table_widget.h \
    gui/widgets/spindel_control_widget.h \
    gui/widgets/sml_commands_list_widget.h \
    gui/utils/gcodes_syntax_highlighter.h \
    common/settings/settings_manager.h \
    hardware/controllers/device_controller/support_device.h

FORMS    += gui/mainwindow.ui

win32:RC_FILE = application.rc
macx:ICON = $${PWD}/sml_logo.icns

RESOURCES += \
    gui/resources/images.qrc \

DISTFILES += \
    machinetool/components/movementController/about.txt \
    sml_logo.icns \
