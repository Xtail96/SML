QT += gui testlib
QT += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console
#CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    libs/gpr/gcode_program.cpp \
    libs/gpr/parser.cpp \
    libs/json_parser/json.cpp \
    common/websockets/websocket_client.cpp \
    common/websockets/websocket_connection.cpp \
    common/websockets/websocket_gateway.cpp \
    hardware/controllers/base_controller.cpp \
    hardware/controllers/device_controller/device.cpp \
    hardware/controllers/device_controller/spindel.cpp \
    hardware/controllers/device_controller/support_device.cpp \
    hardware/controllers/device_controller/device_controller.cpp \
    hardware/controllers/device_controller/sensor.cpp \
    hardware/controllers/motion_controller/axis.cpp \
    hardware/controllers/motion_controller/motion_controller.cpp \
    hardware/controllers/motion_controller/axes_repository.cpp \
    hardware/controllers/registrator.cpp \
    hardware/controllers/task.cpp \
    hardware/hardware_driver.cpp \
    services/adapters_launcher.cpp \
    common/settings/settings_manager.cpp \
    tests/axis_tests.cpp \
    tests/base_test.cpp \
    tests/hardware_driver_tests.cpp \
    tests/task_tests.cpp \
    tests/websocket_gateway_tests.cpp \
    tests_main.cpp \
    tests/sensor_tests.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    libs/gpr/gcode_program.h \
    libs/gpr/parser.h \
    libs/json_parser/json.h \
    common/websockets/websocket_client.h \
    common/websockets/websocket_connection.h \
    common/websockets/websocket_gateway.h \
    hardware/controllers/base_controller.h \
    hardware/controllers/device_controller/device.h \
    hardware/controllers/device_controller/spindel.h \
    hardware/controllers/device_controller/support_device.h \
    hardware/controllers/device_controller/device_controller.h \
    hardware/controllers/device_controller/sensor.h \
    hardware/controllers/motion_controller/axis.h \
    hardware/controllers/motion_controller/motion_controller.h \
    hardware/controllers/motion_controller/axes_repository.h \
    hardware/controllers/registrator.h \
    hardware/controllers/task.h \
    hardware/hardware_driver.h \
    services/adapters_launcher.h \
    common/settings/settings_manager.h \
    tests/axis_tests.h \
    tests/base_test.h \
    tests/hardware_driver_tests.h \
    tests/sensor_tests.h \
    tests/task_tests.h \
    tests/websocket_gateway_tests.h
