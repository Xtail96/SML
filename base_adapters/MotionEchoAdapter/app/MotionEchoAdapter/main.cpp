#include <QCoreApplication>
#include "models/motion_echo_adapter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef Q_OS_LINUX
    MotionEchoAdapter adapter();
    Q_UNUSED(adapter);
#endif
#ifdef Q_OS_MACOS
    MotionEchoAdapter adapter;
    Q_UNUSED(adapter)
#endif

    return a.exec();
}
