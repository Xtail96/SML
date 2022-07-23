#ifndef HARDWAREDRIVERTESTS_H
#define HARDWAREDRIVERTESTS_H

#include "./base_test.h"
#include "../models/hardware/hardware_driver.h"
#include "../models/services/adapters/launcher/adapters_launcher.h"

class HardwareDriverTests : public BaseTest
{
    Q_OBJECT
public:
    explicit HardwareDriverTests(QObject *parent = nullptr);

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
};

#endif // HARDWAREDRIVERTESTS_H
