#include <QApplication>
#include <QTest>

#include "./tests/sensor/sensor_tests.h"
#include "./tests/hardware_driver/hardware_driver_tests.h"

void noMessageHandler(QtMsgType, const QMessageLogContext&, const QString &){}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(noMessageHandler);

    QTest::qExec(new SensorTests, argc, argv);
    QTest::qExec(new HardwareDriverTests, argc, argv);

    return 0;
}
