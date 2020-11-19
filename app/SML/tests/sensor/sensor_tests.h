#ifndef SENSORTESTS_H
#define SENSORTESTS_H

#include "../base_test.h"
#include "../../models/hardware/controllers/device_controller/sensor/sensor.h"

class SensorTests : public BaseTest
{
    Q_OBJECT
public:
    SensorTests(QObject *parent = nullptr);

private slots:
    void testSensor_InitialState();
};

#endif // SENSORTESTS_H
