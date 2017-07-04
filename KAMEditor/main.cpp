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

void test()
{
    Point p = { 1, 2, -3 };
    Point u = { 2, -2, 3 };

    Point s1 = p + u;
    Point s2 = u + p;

    if (s1 == s2)
        qDebug() << "(p + u) == (u + p)";

    Point resl = 1.5 * p;
    Point resr = p * 1.5;

    if (resl == resr)
        qDebug() << "(1.5 * p) == (p * 1.5)";
}
