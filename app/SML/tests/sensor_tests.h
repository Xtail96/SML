#ifndef SENSORTESTS_H
#define SENSORTESTS_H

#include "./base_test.h"
#include "../hardware/controllers/device_controller/sensor.h"

class SensorTests : public BaseTest
{
    Q_OBJECT
public:
    SensorTests(QObject *parent = nullptr);

private slots:
    void testInitialState();
    void testIsEnable();
    void testStateChanged();
};

#endif // SENSORTESTS_H
