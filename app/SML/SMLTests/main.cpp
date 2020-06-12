#include <QCoreApplication>
#include "../models/machine_tool_elements/sensor/sensor_tests.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTest::qExec(new SensorTests, argc, argv);
    return 0;
}
