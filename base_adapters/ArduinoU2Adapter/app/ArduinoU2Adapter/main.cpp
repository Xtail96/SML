#include <QCoreApplication>
#include "models/arduino_u2_adapter.h"

//cu.usbmodem1411
//tty.usbmodem1411

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef Q_OS_LINUX
    U1SerialAdapter u1SerialAdapter("ttyACM0");
    Q_UNUSED(u1SerialAdapter);
#endif
#ifdef Q_OS_MACOS
    //U1SerialAdapter u1SerialAdapter("cu.usbmodem1421");
    ArduinoU2Adapter u1SerialAdapter("tty.usbmodem14101");
    Q_UNUSED(u1SerialAdapter)
#endif
    return a.exec();
}
