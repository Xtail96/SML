#include <QApplication>
#include <QTest>

#include "./tests/sensor_tests.h"
#include "./tests/hardware_driver_tests.h"
#include "./tests/task_tests.h"
#include "./tests/axis_tests.h"
#include "./tests/adapter_gateway_tests.h"

void noMessageHandler(QtMsgType, const QMessageLogContext&, const QString &){}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(noMessageHandler);

    QTest::qExec(new SensorTests, argc, argv);
    QTest::qExec(new TaskTests, argc, argv);
    QTest::qExec(new AxisTests, argc, argv);
    QTest::qExec(new AdapterGatewayTests, argc, argv);
    QTest::qExec(new HardwareDriverTests, argc, argv);

    return 0;
}
