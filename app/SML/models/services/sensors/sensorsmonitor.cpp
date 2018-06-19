#include "sensorsmonitor.h"

SensorsMonitor::SensorsMonitor(QList<QSharedPointer<Sensor> > &sensors, QObject *parent) : QObject(parent)
{
    for(auto sensor : sensors)
    {
        QObject::connect(sensor.data(), SIGNAL(stateChanged(QString,bool)), this, SLOT(onStateChanged(QString,bool)));
    }
}

void SensorsMonitor::onStateChanged(QString name, bool state)
{
    emit stateChanged(name, state);
}
