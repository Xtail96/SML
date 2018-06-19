#include "sensorsmonitor.h"

SensorsMonitor::SensorsMonitor(QList<QSharedPointer<Sensor> > &sensors, QObject *parent) : QObject(parent)
{
    for(auto sensor : sensors)
    {
        QObject::connect(sensor.data(), SIGNAL(stateChanged(QString,bool)), this, SLOT(onSensor_StateChanged(QString,bool)));
    }
}

void SensorsMonitor::onSensor_StateChanged(QString name, bool state)
{
    emit stateChanged(name, state);
}
