#ifndef AXIS_H
#define AXIS_H

#include "models/settingsmanager/settingsmanager.h"

class Axis
{
public:
    explicit Axis(QString name, SettingsManager* settingsManager = nullptr);

protected:
    QString m_name;
    double m_length;
    double m_step;
    double m_currentPosition;
    bool m_invertDirection;
    double m_currentVelocity;
    double m_basingVelocity;

    void setup(SettingsManager* settingsManager);
};

#endif // AXIS_H
