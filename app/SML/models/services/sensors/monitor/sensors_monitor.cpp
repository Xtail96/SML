#include "sensors_monitor.h"

SensorsMonitor::SensorsMonitor(QList<QSharedPointer<Sensor> > &sensors, QObject *parent) : QObject(parent)
{
    for(auto sensor : sensors)
    {
        QObject::connect(sensor.data(), &Sensor::stateChanged, this, [=]() {
            emit this->stateChanged(sensor.data()->uid(), sensor.data()->isEnable());
        });
    }
}
