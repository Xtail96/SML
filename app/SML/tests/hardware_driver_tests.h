#ifndef HARDWAREDRIVERTESTS_H
#define HARDWAREDRIVERTESTS_H

#include "./base_test.h"
#include "../hardware/hardware_driver.h"
#include "../services/adapters_launcher.h"

class HardwareDriverTests : public BaseTest
{
    Q_OBJECT
public:
    explicit HardwareDriverTests(QObject *parent = nullptr);
    ~HardwareDriverTests();
    QtJson::JsonObject deviceControllerStateMock(QString sensorId, bool sensorState);
private slots:
    void testControllersNotConnected();

    void testDeviceAndMotionControllersConnected();

    void testOnlyDeviceControllerConnected();

    void testOnlyMotionControllerConnected();

    void testDeviceAndMotionControllersDisconnected();

    void testOnlyDeviceControllerDisconnected();

    void testOnlyMotionControllerDisconnected();

    void testRegisterHandler();

    void testResetHandlers();

    void testMove();

    void testStopMoving();

    void testSensorStateChanged();
};

#endif // HARDWAREDRIVERTESTS_H
