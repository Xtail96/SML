#include "points_monitor.h"

PointsMonitor::PointsMonitor(PointsManager *manager, QObject *parent) : QObject(parent)
{
    QObject::connect(manager, SIGNAL(pointsUpdated()), this, SLOT(onPointsUpdated()));
}

void PointsMonitor::onPointsUpdated()
{
    emit pointsUpdated();
}
