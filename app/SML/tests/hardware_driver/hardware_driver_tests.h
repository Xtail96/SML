#ifndef HARDWAREDRIVERTESTS_H
#define HARDWAREDRIVERTESTS_H

#include "../base_test.h"
#include "../../models/hardware/hardware_driver.h"
#include "../../models/services/adapters/launcher/adapters_launcher.h"

class HardwareDriverTests : public BaseTest
{
    Q_OBJECT
public:
    explicit HardwareDriverTests(QObject *parent = nullptr);

private slots:

    void testAdaptersNotConnected();

    void testDeviceAndMotionAdaptersConnected();

    void testOnlyDeviceAdapterConnected();

    void testOnlyMotionAdapterConnected();

    void testDeviceAndMotionAdaptersDisconnected();

    void testOnlyDeviceAdapterDisconnected();

    void testOnlyMotionAdapterDisconnected();

    void testRegisterHandler();

    void testResetHandlers();

};

#endif // HARDWAREDRIVERTESTS_H
