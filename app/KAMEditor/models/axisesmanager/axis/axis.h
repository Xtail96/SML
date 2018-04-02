#ifndef AXIS_H
#define AXIS_H

#include "models/settingsmanager/settingsmanager.h"

class Axis
{
public:
    explicit Axis(QString name, SettingsManager* settingsManager = nullptr);
    ~Axis();

    QString name() const;
    void setName(const QString &name);

    double length() const;
    void setLength(double length);

    double step() const;
    void setStep(double step);

    double currentPosition() const;
    void setCurrentPosition(double currentPosition);

    bool invertDirection() const;
    void setInvertDirection(bool invertDirection);

    double currentVelocity() const;
    void setCurrentVelocity(double currentVelocity);

    double basingVelocity() const;
    void setBasingVelocity(double basingVelocity);

    bool softLimitsEnable() const;
    void setSoftLimitsEnable(bool softLimitsEnable);

    QString axisSettings() const;

protected:
    QString m_name;
    double m_length;
    double m_step;
    double m_currentPosition;
    bool m_invertDirection;
    double m_currentVelocity;
    double m_basingVelocity;

    bool m_softLimitsEnable;

    void setup(SettingsManager* settingsManager);
};

#endif // AXIS_H
