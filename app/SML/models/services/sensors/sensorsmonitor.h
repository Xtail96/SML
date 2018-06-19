#ifndef SENSORSMONITOR_H
#define SENSORSMONITOR_H

#include <QObject>
#include "models/types/sensor/sensor.h"

class SensorsMonitor : public QObject
{
    Q_OBJECT
public:
    explicit SensorsMonitor(QList<QSharedPointer<Sensor> > &sensors, QObject *parent = nullptr);

signals:
    void stateChanged(QString sensorName, bool state);

public slots:
    void onSensor_StateChanged(QString name, bool state);
};

#endif // SENSORSMONITOR_H
