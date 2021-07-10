QT -= gui
QT += serialport
QT += websockets
QT += testlib

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
    models/motion_echo_adapter.cpp \
    models/types/websockethandler/websockethandler.cpp \
    models/types/settingsmanager/settingsmanager.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    libs/jsonparser/json.h \
    models/motion_echo_adapter.h \
    models/types/websockethandler/websockethandler.h \
    models/types/settingsmanager/settingsmanager.h \
    models/structs.h
