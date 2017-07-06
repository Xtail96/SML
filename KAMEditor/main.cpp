#include "gui/mainwindow.h"
#include <QApplication>
void test();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Semil");
    QCoreApplication::setOrganizationDomain("semil.ru");
    QCoreApplication::setApplicationName("KAMEditor");
    test();
    MainWindow w;
    w.show();
    return a.exec();
}

#ifdef linux
#include <libusb-1.0/libusb.h>
#elif _WIN32
#include "libusb/include/libusb.h"
#endif

void test()
{

}
