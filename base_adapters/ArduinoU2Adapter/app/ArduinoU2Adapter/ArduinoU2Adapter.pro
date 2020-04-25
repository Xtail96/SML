QT -= gui
QT += serialport
QT += websockets

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    libs/jsonparser/json.cpp \
    models/arduino_u2_adapter.cpp \
    models/types/axis/axis.cpp \
    models/types/u2_state/u2_state.cpp \
    models/types/axis/motor/motor.cpp \
    models/types/settings_manager/settings_manager.cpp \
    models/types/web_socket_handler/web_socket_handler.cpp

HEADERS += \
    models/arduino_u2_adapter.h \
    models/structs.h \
    libs/jsonparser/json.h \
    models/types/axis/axis.h \
    models/types/u2_state/u2_state.h \
    models/types/axis/motor/motor.h \
    models/types/settings_manager/settings_manager.h \
    models/types/web_socket_handler/web_socket_handler.h
