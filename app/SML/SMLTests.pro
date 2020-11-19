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
    libs/json_parser/json.cpp \
    models/hardware/controllers/adapters/adapter_connection.cpp \
    models/hardware/controllers/adapters/adapter_gateway.cpp \
    models/hardware/controllers/base_controller.cpp \
    models/hardware/controllers/device_controller/device/device.cpp \
    models/hardware/controllers/device_controller/device/spindel.cpp \
    models/hardware/controllers/device_controller/device/support_device.cpp \
    models/hardware/controllers/device_controller/device_controller.cpp \
    models/hardware/controllers/device_controller/sensor/sensor.cpp \
    models/hardware/controllers/motion_controller/axis/axis.cpp \
    models/hardware/controllers/motion_controller/motion_controller.cpp \
    models/hardware/controllers/registrator.cpp \
    models/hardware/hardware_driver.cpp \
    models/services/adapters/launcher/adapters_launcher.cpp \
    models/settings_manager/settings_manager.cpp \
    tests/base_test.cpp \
    tests/hardware_driver/hardware_driver_tests.cpp \
    tests_main.cpp \
    tests/sensor/sensor_tests.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    libs/json_parser/json.h \
    models/hardware/controllers/adapters/adapter_connection.h \
    models/hardware/controllers/adapters/adapter_gateway.h \
    models/hardware/controllers/base_controller.h \
    models/hardware/controllers/device_controller/device/device.h \
    models/hardware/controllers/device_controller/device/spindel.h \
    models/hardware/controllers/device_controller/device/support_device.h \
    models/hardware/controllers/device_controller/device_controller.h \
    models/hardware/controllers/device_controller/sensor/sensor.h \
    models/hardware/controllers/motion_controller/axis/axis.h \
    models/hardware/controllers/motion_controller/motion_controller.h \
    models/hardware/controllers/registrator.h \
    models/hardware/hardware_driver.h \
    models/services/adapters/launcher/adapters_launcher.h \
    models/settings_manager/settings_manager.h \
    tests/base_test.h \
    tests/hardware_driver/hardware_driver_tests.h \
    tests/sensor/sensor_tests.h
