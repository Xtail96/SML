#include "sensors_monitor.h"

SensorsMonitor::SensorsMonitor(QList<QSharedPointer<Sensor> > &sensors, QObject *parent) : QObject(parent)
{
    for(auto sensor : sensors)
    {
        QObject::connect(sensor.data(), SIGNAL(stateChanged(QString,bool)), this, SLOT(onSensor_StateChanged(QString,bool)));
    }
}

void SensorsMonitor::onSensor_StateChanged(QString uid, bool enable)
{
    emit stateChanged(uid, enable);
}
