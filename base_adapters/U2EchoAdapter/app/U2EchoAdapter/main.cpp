#include <QCoreApplication>
#include "models/u2_serial_adapter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef Q_OS_LINUX
    U2SerialAdapter u2SerialAdapter();
    Q_UNUSED(u1SerialAdapter);
#endif
#ifdef Q_OS_MACOS
    //U1SerialAdapter u1SerialAdapter("cu.usbmodem1421");
    U2SerialAdapter u2SerialAdapter("1234");
    Q_UNUSED(u2SerialAdapter);
#endif

    return a.exec();
}
