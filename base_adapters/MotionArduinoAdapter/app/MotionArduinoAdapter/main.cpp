#include <QCoreApplication>
#include "models/motion_arduino_adapter.h"

//cu.usbmodem1411
//tty.usbmodem1411

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef Q_OS_LINUX
    MotionArduinoAdapter adapter("ttyACM0");
    Q_UNUSED(adapter);
#endif
#ifdef Q_OS_MACOS
    MotionArduinoAdapter& adapter = MotionArduinoAdapter::getInstance();
    Q_UNUSED(adapter)
#endif
    return a.exec();
}
