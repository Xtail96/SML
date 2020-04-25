#include <QCoreApplication>
#include "models/u1serialadapter.h"

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
    U1SerialAdapter u1SerialAdapter("tty.usbmodem14201");
    Q_UNUSED(u1SerialAdapter);
#endif
    return a.exec();
}
