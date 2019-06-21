#include "axises_monitor.h"

AxisesMonitor::AxisesMonitor(QList<QSharedPointer<Axis> > &axises, QObject *parent) :
    QObject(parent)
{
    for(auto axis : axises)
    {
        QObject::connect(axis.data(), SIGNAL(currentPositionChanged(QString,double)), this, SLOT(onAxis_CurrentPositionChanged(QString,double)));
    }
}

void AxisesMonitor::onAxis_CurrentPositionChanged(QString uid, double position)
{
    emit this->axisCurrentPositionChanged(uid, position);
}
