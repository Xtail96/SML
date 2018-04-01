#ifndef AXISESMANAGER_H
#define AXISESMANAGER_H

#include <QObject>

#include "models/settingsmanager/settingsmanager.h"
#include "models/axisesmanager/axis/axis.h"
#include "models/pointsmanager/point/point.h"

class AxisesManager
{
public:
    explicit AxisesManager(SettingsManager* settingsManager = nullptr);
    ~AxisesManager();

protected:
    QList< std::shared_ptr<Axis> > m_axises;
    Point m_zeroCoordinates;
    Point m_parkCoordinates;

    void setup(SettingsManager* settingsManager);
};

#endif // AXISESMANAGER_H
