#include <QCoreApplication>
#include "models/motion_echo_adapter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef Q_OS_LINUX
    U2SerialAdapter u2SerialAdapter();
    Q_UNUSED(u1SerialAdapter);
#endif
#ifdef Q_OS_MACOS
    //U1SerialAdapter adapter("cu.usbmodem1421");
    MotionEchoAdapter adapter;
    Q_UNUSED(adapter)
#endif

    return a.exec();
}
