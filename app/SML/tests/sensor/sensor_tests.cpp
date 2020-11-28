#include "sensor_tests.h"

SensorTests::SensorTests(QObject *parent) : BaseTest(parent) {}

void SensorTests::testInitialState() {
    Sensor s1("TestSensor", "TestSensor", false, QColor("#00ff00"), this);
    Sensor s2("TestSensor", "TestSensor", true, QColor("#00ff00"), this);
    bool actual1 = s1.isEnable();
    bool actual2 = s1.isEnable();
    bool expected = false;

    QCOMPARE(actual1, expected);
    QCOMPARE(actual2, expected);
}

void SensorTests::testIsEnable()
{
    bool activeState = false;
    Sensor s1("TestSensor", "TestSensor", activeState, QColor("#00ff00"), this);
    s1.setCurrentState(true);
    QCOMPARE(s1.isEnable(), false);
    s1.setCurrentState(false);
    QCOMPARE(s1.isEnable(), true);

    activeState = true;
    Sensor s2("TestSensor", "TestSensor", activeState, QColor("#00ff00"), this);
    s2.setCurrentState(true);
    QCOMPARE(s2.isEnable(), true);
    s2.setCurrentState(false);
    QCOMPARE(s2.isEnable(), false);
}

void SensorTests::testStateChanged()
{
    bool stateChanged = false;
    Sensor s("TestSensor", "TestSensor", false, QColor("#00ff00"), this);

    QObject::connect(&s, &Sensor::stateChanged, this, [&stateChanged]() mutable {
        stateChanged = true;
    });

    s.setCurrentState(s.currentState());
    QCOMPARE(stateChanged, false);

    s.setCurrentState(!s.currentState());
    QCOMPARE(stateChanged, true);
}
