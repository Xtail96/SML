#include "hardware_driver_tests.h"

HardwareDriverTests::HardwareDriverTests(QObject *parent) : BaseTest(parent) {}

void HardwareDriverTests::testAdaptersNotConnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Регистрируем обработчики событий, чтобы проверить, что сигналы подключения не будут испущены.
    auto signalEmitted = false;
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [&signalEmitted]() mutable {
       signalEmitted = true;
    });
    driver.registerHandler(HARDWARE_EVENT::MotionControllerConnected, [&signalEmitted]() mutable {
       signalEmitted = true;
    });
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerDisconnected, [&signalEmitted]() mutable {
       signalEmitted = true;
    });
    driver.registerHandler(HARDWARE_EVENT::MotionControllerDisconnected, [&signalEmitted]() mutable {
       signalEmitted = true;
    });

    // Ждем некоторое время.
    QTest::qWait(5000);
    auto actual = driver.isConnected();

    // Чистим за собой.
    driver.resetHandlers();

    // Проверяем состояние подключения.
    QCOMPARE(actual, false);

    // Проверяем, что сигналов не было испущено.
    QCOMPARE(signalEmitted, false);
}

void HardwareDriverTests::testDeviceAndMotionAdaptersConnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Запускаем адаптеры.
    auto launcher = new AdaptersLauncher(this);
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [=]() {
        launcher->startAdapters(false, true);
    });
    launcher->startAdapters(true, false);

    // Ждем некоторое время.
    QTest::qWait(5000);
    auto actual = driver.isConnected();

    // Чистим за собой.
    launcher->stopAdapters();
    driver.resetHandlers();

    // Проверяем состояние подключения.
    QCOMPARE(actual, true);
}

void HardwareDriverTests::testOnlyDeviceAdapterConnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Регистрируем обработчики событий.
    auto signalEmitted = false;
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [&signalEmitted]() mutable {
       signalEmitted = true;
    });

    // Запускаем адаптер.
    auto launcher = new AdaptersLauncher(this);
    launcher->startAdapters(true, false);

    // Ждем некоторое время.
    QTest::qWait(5000);
    auto actual = driver.isConnected();

    // Чистим за собой.
    launcher->stopAdapters();
    driver.resetHandlers();

    // Проверяем состояние подключения.
    QCOMPARE(actual, false);

    // Проверяем, что сигнал подключения был испущен.
    QCOMPARE(signalEmitted, true);
}

void HardwareDriverTests::testOnlyMotionAdapterConnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Регистрируем обработчики событий.
    auto signalEmitted = false;
    driver.registerHandler(HARDWARE_EVENT::MotionControllerConnected, [&signalEmitted]() mutable {
       signalEmitted = true;
    });

    // Запускаем адаптер.
    auto launcher = new AdaptersLauncher(this);
    launcher->startAdapters(false, true);

    // Ждем некотрое время.
    QTest::qWait(5000);
    auto actual = driver.isConnected();

    // Чистим за собой.
    launcher->stopAdapters();
    driver.resetHandlers();

    // Проверяем состояние подключения.
    QCOMPARE(actual, false);

    // Проверяем, что сигнал подключения был испущен.
    QCOMPARE(signalEmitted, true);
}

void HardwareDriverTests::testDeviceAndMotionAdaptersDisconnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Запускаем адаптеры
    auto launcher = new AdaptersLauncher(this);
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [=]() {
        launcher->startAdapters(false, true);
    });
    launcher->startAdapters(true, false);

    // Ждем некотрое время.
    QTest::qWait(5000);

    // Проверяем, что адаптеры успешно подключились.
    if(!driver.isConnected())
    {
        // Чистим за собой.
        launcher->stopAdapters();
        driver.resetHandlers();

        // Делаем так, чтобы тест упал.
        QCOMPARE(true, false);
    }

    // Останавливаем адаптеры.
    launcher->stopAdapters();

    // Чистим за собой.
    driver.resetHandlers();

    // Ждем некотрое время.
    QTest::qWait(5000);

    // Проверяем состояние подключения.
    QCOMPARE(driver.isConnected(), false);
}

void HardwareDriverTests::testDeviceAdapterDisconnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Регистрируем обработчики событий.
    auto signalEmitted = false;
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerDisconnected, [&signalEmitted]() mutable {
       signalEmitted = true;
    });

    // Запускаем адаптеры.
    auto launcher = new AdaptersLauncher(this);
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [=]() {
        launcher->startAdapters(false, true);
    });
    launcher->startAdapters(true, false);

    // Ждем некоторое время.
    QTest::qWait(5000);

    // Проверяем, что адаптеры успешно подключились.
    if(!driver.isConnected())
    {
        // Чистим за собой.
        launcher->stopAdapters();
        driver.resetHandlers();

        // Делаем так, чтобы тест упал.
        QCOMPARE(true, false);
    }

    // Останавливаем адаптер.
    launcher->stopAdapters(true, false);

    // Ждем некотрое время
    QTest::qWait(5000);

    // Запоминаем состояние подключения.
    auto actual = driver.isConnected();

    // Чистим за собой.
    launcher->stopAdapters(false, true);
    driver.resetHandlers();

    // Проверяем состояние подключения.
    QCOMPARE(actual, false);

    // Проверяем, что сигнал отключения был испущен.
    QCOMPARE(signalEmitted, true);
}

void HardwareDriverTests::testMotionAdapterDisconnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Регистрируем обработчики событий.
    auto signalEmitted = false;
    driver.registerHandler(HARDWARE_EVENT::MotionControllerDisconnected, [&signalEmitted]() mutable {
       signalEmitted = true;
    });

    // Запускаем адаптеры.
    auto launcher = new AdaptersLauncher(this);
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [=]() {
        launcher->startAdapters(false, true);
    });
    launcher->startAdapters(true, false);

    // Ждем некотрое время.
    QTest::qWait(5000);

    // Проверяем, что адаптеры успешно подключились.
    // Проверяем, что адаптеры успешно подключились.
    if(!driver.isConnected())
    {
        // Чистим за собой.
        launcher->stopAdapters();
        driver.resetHandlers();

        // Делаем так, чтобы тест упал.
        QCOMPARE(true, false);
    }

    // Останавливаем адаптер.
    launcher->stopAdapters(false, true);

    // Ждем некоторое время.
    QTest::qWait(5000);

    // Запоминаем состояние подключения.
    auto actual = driver.isConnected();

    // Чистим за собой.
    launcher->stopAdapters(true, false);
    driver.resetHandlers();

    // Проверяем состояние подключения.
    QCOMPARE(actual, false);

    // Проверяем, что сигнал отключения был испущен.
    QCOMPARE(signalEmitted, true);
}

void HardwareDriverTests::testRegisterHandler()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Регистрируем обработчик.
    bool connected = false;
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [&connected]() mutable -> void {
        connected = true;
    });

    // Создаем условие, чтобы обработчик сработал.
    auto launcher = new AdaptersLauncher(this);
    launcher->startAdapters(true, false);

    // Ждем, чтобы обработчик сработал.
    QTest::qWait(5000);

    // Чистим за собой.
    launcher->stopAdapters();
    driver.resetHandlers();

    // Проверяем, что обработчик сработал.
    QCOMPARE(connected, true);
}

void HardwareDriverTests::testResetHandlers()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Регистрируем обработчики.
    bool connected = false;
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [&connected]() mutable -> void {
        connected = true;
    });
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerDisconnected, [&connected]() mutable -> void {
        connected = false;
    });

    // Создаем условие чтобы первый обработчик сработал.
    auto launcher = new AdaptersLauncher(this);
    launcher->startAdapters(true, false);

    // Ждем некоторое время.
    QTest::qWait(5000);

    // Отключаем обработчики.
    driver.resetHandlers();

    // Создваем условие, чтобы второй обработчик сработал, если бы не был отключен.
    launcher->stopAdapters();

    // Чистим за собой.
    driver.resetHandlers();

    // Проверяем, что первый обработчик сработал, а второй - нет.
    QCOMPARE(connected, true);
}
