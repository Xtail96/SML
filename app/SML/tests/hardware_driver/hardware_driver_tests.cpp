#include "hardware_driver_tests.h"

HardwareDriverTests::HardwareDriverTests(QObject *parent) : BaseTest(parent) {}

void HardwareDriverTests::testAdaptersNotConnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();
    QTest::qWait(1000);
    QCOMPARE(driver.isConnected(), false);
}

void HardwareDriverTests::testDeviceAndMotionAdapterConnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();
    auto launcher = new AdaptersLauncher(this);
    launcher->startAdapters(true, true);

    QTest::qWait(10000);

    auto actual = driver.isConnected();
    auto expected = true;
    launcher->stopAdapters();

    QCOMPARE(actual, expected);
}

void HardwareDriverTests::testOnlyDeviceAdapterConnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();
    QTest::qWait(1000);
    QCOMPARE(driver.isConnected(), false);
}

void HardwareDriverTests::testOnlyMotionAdapterConnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();
    QTest::qWait(1000);
    QCOMPARE(driver.isConnected(), false);
}
