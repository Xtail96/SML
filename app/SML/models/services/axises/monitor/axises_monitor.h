#ifndef AXISES_MONITOR_H
#define AXISES_MONITOR_H

#include <QObject>
#include <QSharedPointer>

#include "models/machine_tool_elements/axis/axis.h"

class AxisesMonitor : public QObject
{
    Q_OBJECT
public:
    explicit AxisesMonitor(QList<QSharedPointer<Axis> > &axises, QObject *parent = nullptr);

signals:
    void axisCurrentPositionChanged(QString uid, double position);
};

#endif // AXISES_MONITOR_H
