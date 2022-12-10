#include "hardware_driver_tests.h"

HardwareDriverTests::HardwareDriverTests(QObject *parent) : BaseTest(parent) {}

void HardwareDriverTests::testControllersNotConnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Регистрируем обработчики событий, чтобы проверить, что сигналы подключения не будут испущены.
    auto signalEmitted = false;
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [&signalEmitted](HARDWARE_EVENT_DATA) mutable {
       signalEmitted = true;
    });
    driver.registerHandler(HARDWARE_EVENT::MotionControllerConnected, [&signalEmitted](HARDWARE_EVENT_DATA) mutable {
       signalEmitted = true;
    });
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerDisconnected, [&signalEmitted](HARDWARE_EVENT_DATA) mutable {
       signalEmitted = true;
    });
    driver.registerHandler(HARDWARE_EVENT::MotionControllerDisconnected, [&signalEmitted](HARDWARE_EVENT_DATA) mutable {
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

void HardwareDriverTests::testDeviceAndMotionControllersConnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Запускаем адаптеры.
    auto launcher = new AdaptersLauncher(this);
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [=](HARDWARE_EVENT_DATA) {
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

void HardwareDriverTests::testOnlyDeviceControllerConnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Регистрируем обработчики событий.
    auto signalEmitted = false;
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [&signalEmitted](HARDWARE_EVENT_DATA) mutable {
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

void HardwareDriverTests::testOnlyMotionControllerConnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Регистрируем обработчики событий.
    auto signalEmitted = false;
    driver.registerHandler(HARDWARE_EVENT::MotionControllerConnected, [&signalEmitted](HARDWARE_EVENT_DATA) mutable {
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

void HardwareDriverTests::testDeviceAndMotionControllersDisconnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Запускаем адаптеры
    auto launcher = new AdaptersLauncher(this);
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [=](HARDWARE_EVENT_DATA) {
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

void HardwareDriverTests::testOnlyDeviceControllerDisconnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Регистрируем обработчики событий.
    auto signalEmitted = false;
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerDisconnected, [&signalEmitted](HARDWARE_EVENT_DATA) mutable {
       signalEmitted = true;
    });

    // Запускаем адаптеры.
    auto launcher = new AdaptersLauncher(this);
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [=](HARDWARE_EVENT_DATA) {
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

void HardwareDriverTests::testOnlyMotionControllerDisconnected()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Регистрируем обработчики событий.
    auto signalEmitted = false;
    driver.registerHandler(HARDWARE_EVENT::MotionControllerDisconnected, [&signalEmitted](HARDWARE_EVENT_DATA) mutable {
       signalEmitted = true;
    });

    // Запускаем адаптеры.
    auto launcher = new AdaptersLauncher(this);
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [=](HARDWARE_EVENT_DATA) {
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
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [&connected](HARDWARE_EVENT_DATA) mutable -> void {
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
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, [&connected](HARDWARE_EVENT_DATA) mutable -> void {
        connected = true;
    });
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerDisconnected, [&connected](HARDWARE_EVENT_DATA) mutable -> void {
        connected = false;
    });

    // Создаем условие чтобы первый обработчик сработал.
    auto launcher = new AdaptersLauncher(this);
    launcher->startAdapters(true, false);

    // Ждем некоторое время.
    QTest::qWait(5000);

    // Отключаем обработчики.
    driver.resetHandlers();

    // Создаем условие, чтобы второй обработчик сработал, если бы не был отключен.
    launcher->stopAdapters();

    // Чистим за собой.
    driver.resetHandlers();

    // Проверяем, что первый обработчик сработал, а второй - нет.
    QCOMPARE(connected, true);
}

void HardwareDriverTests::testMove()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Запускаем адаптеры.
    auto launcher = new AdaptersLauncher(this);
    launcher->startAdapters();

    // Ждем некоторое время, чтобы адаптеры успели запуститься и подключиться.
    QTest::qWait(30000);

    // Получаем начальное состояние осей.
    QList<Axis::State> intialAxesState = driver.getMotionController().getAll();

    // Если адаптеры так и не подключились, завершаем тест с ошибкой.
    if(!driver.isConnected())
    {
        // Чистим за собой.
        driver.resetHandlers();
        launcher->stopAdapters();
        QCOMPARE(true, false);
    }

    // Если осей нет, то завершаем тест с ошибкой, т.к. нет осей для перемещения.
    if(intialAxesState.length() <= 0)
    {
        // Чистим за собой.
        driver.resetHandlers();
        launcher->stopAdapters();
        QCOMPARE(true, false);
    }

    // Получаем состояние первой оси из списка.
    Axis::State firstAxisState = intialAxesState.first();

    // Формируем задание на перемещение.
    QMap<Axis::Id, double> task = {
        { firstAxisState.id(), firstAxisState.currentPositionFromBase() + 10 }
    };

    // Формируем ожидаемый результат после перемещения.
    QList<Axis::State> expectedAxesState = intialAxesState;
    expectedAxesState.first().setCurrentPosition(firstAxisState.currentPositionFromBase() + 10);

    // Выполняем перемещение.
    driver.moveTo(task);

    // Ждем некоторое время, чтобы перемещение успело выполниться.
    QTest::qWait(5000);

    // Получаем актуальное состояние осей после перемещения.
    QList<Axis::State> actualAxisState = driver.getMotionController().getAll();

    // Чистим за собой и останавливаем адаптеры.
    driver.resetHandlers();
    launcher->stopAdapters();

    // Проеряем, что число осей до и после перемещения совпадает.
    QCOMPARE(actualAxisState.length(), expectedAxesState.length());

    // Проверяем, что состояние каждой оси после перемщения соответствует ожидаемому значению.
    for(int i = 0; i < expectedAxesState.length(); i++)
    {
        QCOMPARE(actualAxisState[i].currentPositionFromBase(), expectedAxesState[i].currentPositionFromBase());
    }
}

void HardwareDriverTests::testStopMoving()
{
    HardwareDriver& driver = HardwareDriver::getInstance();

    // Запускаем адаптеры.
    auto launcher = new AdaptersLauncher(this);
    launcher->startAdapters();

    // Ждем некоторое время, чтобы адаптеры успели запуститься и подключиться.
    QTest::qWait(30000);

    // Получаем начальное состояние осей.
    QList<Axis::State> intialAxesState = driver.getMotionController().getAll();

    // Если адаптеры так и не подключились, завершаем тест с ошибкой.
    if(!driver.isConnected())
    {
        // Чистим за собой.
        driver.resetHandlers();
        launcher->stopAdapters();
        QCOMPARE(true, false);
    }

    // Если осей нет, то завершаем тест с ошибкой, т.к. нет осей для перемещения.
    if(intialAxesState.length() <= 0)
    {
        // Чистим за собой.
        driver.resetHandlers();
        launcher->stopAdapters();
        QCOMPARE(true, false);
    }

    // Получаем состояние первой оси из списка.
    Axis::State firstAxisState = intialAxesState.first();

    // Формируем задание на перемещение.
    double targetPosition = firstAxisState.currentPositionFromBase() + 100;
    QMap<Axis::Id, double> task = {
        { firstAxisState.id(), targetPosition }
    };

    // Выполняем перемещение.
    driver.moveTo(task);

    // Ждем некоторое, чтобы команда начала выполняться.
    QTest::qWait(100);

    // Останавливаем перемещение.
    driver.stopMoving();

    // Ждем некоторое время, за которое перемещение успело бы выполниться.
    QTest::qWait(5000);

    // Получаем актуальное состояние осей после перемещения.
    QList<Axis::State> actualAxisState = driver.getMotionController().getAll();

    // Чистим за собой и останавливаем адаптеры.
    driver.resetHandlers();
    launcher->stopAdapters();

    // Проеряем, что число осей до и после перемещения совпадает.
    QCOMPARE(actualAxisState.length(), intialAxesState.length());

    // Проверяем, что ось, по которой выполнялось перемещение не выполнила задание.
    QCOMPARE(actualAxisState.first().currentPositionFromBase() < targetPosition, true);
}
