#include "gui/mainwindow.h"
#include <QApplication>
void test();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Semil");
    QCoreApplication::setOrganizationDomain("semil.ru");
    QCoreApplication::setApplicationName("KAMEditor");
    //test();
    MainWindow w;
    w.show();
    return a.exec();
}

#include "libusb/include/libusb.h"

void test()
{

}
