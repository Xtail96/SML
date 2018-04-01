#ifndef AXISESMANAGER_H
#define AXISESMANAGER_H

#include <QObject>

#include "models/settingsmanager/settingsmanager.h"
#include "models/axisesmanager/axis/axis.h"
#include "models/pointsmanager/point/point.h"

class AxisesManager : public QObject
{
    Q_OBJECT
public:
    explicit AxisesManager(SettingsManager* settingsManager = nullptr, QObject *parent = nullptr);
    ~AxisesManager();

protected:
    QList< std::shared_ptr<Axis> > m_axises;
    Point zeroCoordinates;
    Point parkCoordinates;

    void setup(SettingsManager* settingsManager);

signals:

public slots:
};

#endif // AXISESMANAGER_H
