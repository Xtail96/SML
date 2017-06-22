#include "gui/mainwindow.h"
#include "library/machinetool/machinetool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
