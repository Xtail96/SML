#include "axises_monitor.h"

AxisesMonitor::AxisesMonitor(QList<QSharedPointer<Axis> > &axises, QObject *parent) :
    QObject(parent)
{
    for(auto axis : axises)
    {
        QObject::connect(axis.data(), &Axis::currentPositionChanged, this, [=]() {
            emit this->axisCurrentPositionChanged(axis.data()->name(), axis.data()->currentPosition());
        });
    }
}
