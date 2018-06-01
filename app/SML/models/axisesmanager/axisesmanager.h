#ifndef AXISESMANAGER_H
#define AXISESMANAGER_H

#include <QObject>

#include "models/settingsmanager/settingsmanager.h"
#include "models/axisesmanager/axis/axis.h"
#include "models/pointsmanager/point/point.h"

class AxisesManager
{
public:
    explicit AxisesManager(const SettingsManager &settingsManager = SettingsManager());
    ~AxisesManager();

    void updateCurrentCoordinates(Point newCoordinates);

    Point getCurrentCoordinatesFromZero();
    Point getCurrentCoordinatesFromBase();

    Point getZeroCoordinates() const;
    void setZeroCoordinates(const Point &zeroCoordinates);

    Point getParkCoordinates() const;
    void setParkCoordinates(const Point &parkCoordinates);

    QStringList getAxisesNames() const;
    QStringList getAxisesSettings() const;

    void setSoftLimitsMode(bool enable);

protected:
    QList< QSharedPointer<Axis> > m_axises;
    Point m_zeroCoordinates;
    Point m_parkCoordinates;

    void setup(const SettingsManager &settingsManager);
};

#endif // AXISESMANAGER_H
