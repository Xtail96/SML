#include <QCoreApplication>
#include "models/device_arduino_adapter.h"

//cu.usbmodem1411
//tty.usbmodem1411

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef Q_OS_LINUX
    ArduinoDeviceAdapter adapter("ttyACM0");
    Q_UNUSED(adapter);
#endif
#ifdef Q_OS_MACOS
    ArduinoDeviceAdapter adapter("tty.usbmodem14201");
    Q_UNUSED(adapter)
#endif
    return a.exec();
}
