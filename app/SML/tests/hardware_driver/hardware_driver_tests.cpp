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

    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [=]() {
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

void HardwareDriverTests::testDeviceAdapterAndMotionAdapterDisconnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();
    auto launcher = new AdaptersLauncher(this);

    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [=]() {
        launcher->startAdapters(false, true);
    });
    launcher->startAdapters(true, false);

    QTest::qWait(5000);
    QCOMPARE(driver.isConnected(), true);

    launcher->stopAdapters();
    QTest::qWait(5000);

    QCOMPARE(driver.isConnected(), false);
}

void HardwareDriverTests::testDeviceAdapterDisconnected()
{
    auto actual = true;
    auto expected = false;

    HardwareDriver& driver = HardwareDriver::getInstance();
    auto launcher = new AdaptersLauncher(this);

    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [=]() {
        launcher->startAdapters(false, true);
    });
    launcher->startAdapters(true, false);

    QTest::qWait(5000);
    QCOMPARE(driver.isConnected(), true);

    launcher->stopAdapters(true, false);
    QTest::qWait(5000);

    actual = driver.isConnected();
    launcher->stopAdapters(false, true);

    QCOMPARE(actual, expected);
}

void HardwareDriverTests::testMotionAdapterDisconnected()
{
    auto actual = true;
    auto expected = false;

    HardwareDriver& driver = HardwareDriver::getInstance();
    auto launcher = new AdaptersLauncher(this);

    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [=]() {
        launcher->startAdapters(false, true);
    });
    launcher->startAdapters(true, false);

    QTest::qWait(5000);
    QCOMPARE(driver.isConnected(), true);

    launcher->stopAdapters(false, true);
    QTest::qWait(5000);

    actual = driver.isConnected();
    launcher->stopAdapters(true, false);

    QCOMPARE(actual, expected);
}

void HardwareDriverTests::testRegisterHandler()
{
    bool connected = false;
    HardwareDriver& driver = HardwareDriver::getInstance();
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [&connected]() mutable -> void {
        connected = true;
    });

    auto launcher = new AdaptersLauncher(this);
    launcher->startAdapters(true, false);
    QTest::qWait(5000);
    launcher->stopAdapters();
    QCOMPARE(connected, true);
}

void HardwareDriverTests::testResetHandlers()
{
    bool connected = false;
    HardwareDriver& driver = HardwareDriver::getInstance();
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [&connected]() mutable -> void {
        connected = true;
    });

    driver.registerHandler(HARDWARE_EVENT::DeviceControllerDisconnected, [&connected]() mutable -> void {
        connected = false;
    });

    auto launcher = new AdaptersLauncher(this);
    launcher->startAdapters(true, false);
    QTest::qWait(5000);
    driver.resetHandlers();
    launcher->stopAdapters();
    QCOMPARE(connected, true);
}
