#include "sensor_tests.h"

SensorTests::SensorTests(QObject *parent) : QObject(parent)
{

}

void SensorTests::sensorInitialStateTest()
{
    Sensor s("TestSensor", "TestSensor",
             0, 0, "u1", false, QColor("#00ff00"), this);

    bool actual = s.isEnable();
    bool expected = false;

    QCOMPARE(actual, expected);
}
