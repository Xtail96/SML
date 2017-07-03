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

void test()
{
    Point p = { 1, 2, -3 };
    Point resl = 1.5 * p;
    Point resr = p * 1.5;

    if (resl == resr)
        qDebug() << "(1.5 * p) == (p * 1.5)";
}
