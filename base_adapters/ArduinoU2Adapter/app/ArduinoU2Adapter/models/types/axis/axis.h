#ifndef AXIS_H
#define AXIS_H

#include <QString>

#include "models/types/axis/motor/motor.h"

class Axis
{
public:
    Axis(QString id, Motor motor);

    QtJson::JsonObject currentState();

    QString getId() const;

    Motor& getMotor();

    double currentAxisPos();

private:
    QString m_id;
    Motor m_motor;

    int m_feedrate;
};

#endif // AXIS_H
