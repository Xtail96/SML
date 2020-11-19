#include "sensor_tests.h"

SensorTests::SensorTests(QObject *parent) : BaseTest(parent) {}

void SensorTests::testSensor_InitialState() {
    Sensor s1("TestSensor", "TestSensor",
             0, 0, "portal", false, QColor("#00ff00"), this);
    Sensor s2("TestSensor", "TestSensor",
             0, 0, "portal", true, QColor("#00ff00"), this);
    bool actual1 = s1.isEnable();
    bool actual2 = s1.isEnable();
    bool expected = false;

    QCOMPARE(actual1, expected);
    QCOMPARE(actual2, expected);
}
