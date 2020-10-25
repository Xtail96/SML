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
    models/hardware/controllers/adapters/adapter_connection.cpp \
    models/hardware/controllers/adapters/adapter_gateway.cpp \
    models/hardware/controllers/base_controller.cpp \
    models/hardware/controllers/device_controller/device_controller.cpp \
    models/hardware/controllers/motion_controller/motion_controller.cpp \
    models/hardware/controllers/registrator.cpp \
    models/hardware/hardware_driver.cpp \
    models/services/adapters/launcher/adapters_launcher.cpp \
    models/hardware/controllers/device_controller/sensor/sensor.cpp \
    models/hardware/controllers/device_controller/device/spindel.cpp \
    models/hardware/controllers/device_controller/device/device.cpp \
    models/hardware/controllers/motion_controller/axis/axis.cpp \
    gui/widgets/gcodes_editor_widget.cpp \
    gui/widgets/sensors_display_widget.cpp \
    gui/widgets/sml_commands_list_widget.cpp \
    gui/widgets/sml_editor_tree_widget.cpp \
    gui/widgets/points_table_widget.cpp \
    gui/widgets/spindel_control_widget.cpp \
    gui/utils/gcodes_syntax_highlighter.cpp \
    models/services/gcodes/view/gcodes_view_interactor.cpp \
    models/settings_manager/settings_manager.cpp \
    models/hardware/controllers/device_controller/device/support_device.cpp

HEADERS  += gui/mainwindow.h \
    gui/utils/colors.h \
    libs/json_parser/json.h \
    libs/gpr/gcode_program.h \
    libs/gpr/parser.h \
    models/hardware/controllers/adapters/adapter_connection.h \
    models/hardware/controllers/adapters/adapter_gateway.h \
    models/hardware/controllers/base_controller.h \
    models/hardware/controllers/device_controller/device_controller.h \
    models/hardware/controllers/motion_controller/motion_controller.h \
    models/hardware/controllers/registrator.h \
    models/hardware/hardware_driver.h \
    models/services/adapters/launcher/adapters_launcher.h \
    models/services/gcodes/view/gcodes_view_interactor.h \
    models/hardware/controllers/device_controller/sensor/sensor.h \
    models/hardware/controllers/device_controller/device/spindel.h \
    models/hardware/controllers/device_controller/device/device.h \
    models/hardware/controllers/motion_controller/axis/axis.h \
    gui/widgets/gcodes_editor_widget.h \
    gui/widgets/sensors_display_widget.h \
    gui/widgets/sml_editor_tree_widget.h \
    gui/widgets/points_table_widget.h \
    gui/widgets/spindel_control_widget.h \
    gui/widgets/sml_commands_list_widget.h \
    gui/utils/gcodes_syntax_highlighter.h \
    models/settings_manager/settings_manager.h \
    models/hardware/controllers/device_controller/device/support_device.h

FORMS    += gui/mainwindow.ui

win32:RC_FILE = application.rc
macx:ICON = $${PWD}/sml_logo.icns

RESOURCES += \
    gui/resources/images.qrc \

DISTFILES += \
    machinetool/components/movementController/about.txt \
    sml_logo.icns \
