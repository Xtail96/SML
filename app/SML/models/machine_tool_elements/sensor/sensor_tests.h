#ifndef SENSORTESTS_H
#define SENSORTESTS_H

#include <QObject>
#include <QtTest/QTest>
#include <QColor>

#include "sensor.h"

class SensorTests : public QObject
{
    Q_OBJECT
public:
    explicit SensorTests(QObject *parent = nullptr);

private slots:
    void sensorInitialStateTest();

};

#endif // SENSORTESTS_H
