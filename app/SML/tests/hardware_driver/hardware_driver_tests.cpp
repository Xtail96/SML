#include "hardware_driver_tests.h"

HardwareDriverTests::HardwareDriverTests(QObject *parent) : BaseTest(parent) {}

void HardwareDriverTests::testAdaptersNotConnected()
{
    auto actual = true;
    auto expected = false;

    HardwareDriver& driver = HardwareDriver::getInstance();

    QTest::qWait(5000);
    actual = driver.isConnected();

    QCOMPARE(actual, expected);
}

void HardwareDriverTests::testDeviceAndMotionAdapterConnected()
{
    auto actual = false;
    auto expected = true;

    HardwareDriver& driver = HardwareDriver::getInstance();
    auto launcher = new AdaptersLauncher(this);

    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnectionStateChanged, [=]() {
        launcher->startAdapters(false, true);
    });
    launcher->startAdapters(true, false);

    QTest::qWait(5000);
    actual = driver.isConnected();
    launcher->stopAdapters();

    QCOMPARE(actual, expected);
}

void HardwareDriverTests::testOnlyDeviceAdapterConnected()
{
    auto actual = true;
    auto expected = false;

    HardwareDriver& driver = HardwareDriver::getInstance();
    auto launcher = new AdaptersLauncher(this);
    launcher->startAdapters(true, false);

    QTest::qWait(5000);
    actual = driver.isConnected();
    launcher->stopAdapters();

    QCOMPARE(actual, expected);
}

void HardwareDriverTests::testOnlyMotionAdapterConnected()
{
    auto actual = true;
    auto expected = false;

    HardwareDriver& driver = HardwareDriver::getInstance();
    auto launcher = new AdaptersLauncher(this);
    launcher->startAdapters(false, true);

    QTest::qWait(5000);
    actual = driver.isConnected();
    launcher->stopAdapters();

    QCOMPARE(actual, expected);
}
