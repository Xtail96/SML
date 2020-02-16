#include "points_monitor.h"

PointsMonitor::PointsMonitor(Repository &repo, QObject *parent) : QObject(parent)
{
    QObject::connect(&repo, SIGNAL(pointsUpdated()), this, SLOT(onRepository_PointsUpdated()));
}

void PointsMonitor::onRepository_PointsUpdated()
{
    emit pointsUpdated();
}
