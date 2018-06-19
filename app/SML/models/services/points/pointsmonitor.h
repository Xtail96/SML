#ifndef POINTSMONITOR_H
#define POINTSMONITOR_H

#include <QObject>
#include "models/types/point/pointsmanager.h"

class PointsMonitor : public QObject
{
    Q_OBJECT
public:
    explicit PointsMonitor(PointsManager* manager, QObject *parent = nullptr);

signals:
    void pointsUpdated();

public slots:
    void onPointsUpdated();
};

#endif // POINTSMONITOR_H
