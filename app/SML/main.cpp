#include <QApplication>
#include "gui/mainwindow.h"

#include "testenv.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //TestEnv s(nullptr);

    QCoreApplication::setOrganizationName("SEMIL");
    QCoreApplication::setOrganizationDomain("semil.ru");
    QCoreApplication::setApplicationName("SML");

    MainWindow w;
    w.show();

    return a.exec();
}
