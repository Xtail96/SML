#ifndef SENSOR_H
#define SENSOR_H
#include <string>
#include <QSensor>
#include <QPressureSensor>

class Sensor
{
protected:

public:
    Sensor();
    //! Методы получения и установки значений
private slots:
    void update();
};

#endif // SENSOR_H
