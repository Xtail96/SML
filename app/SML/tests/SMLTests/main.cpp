#include <QApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "../../models/hardware/controllers/device_controller/sensor/sensor_tests.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTest::qExec(new SensorTests, argc, argv);
    return 0;
}
