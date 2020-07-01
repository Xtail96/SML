#include <QApplication>
#include "gui/mainwindow.h"

#include "testenv.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QCoreApplication::setOrganizationName("Semil");
    //QCoreApplication::setOrganizationDomain("semil.ru");
    //QCoreApplication::setApplicationName("SMLKAMEditor");

    //MainWindow w;
    //w.show();

    //Test t;

    TestEnv s(nullptr);

    return a.exec();
}
