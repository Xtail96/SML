#ifndef AXIS_H
#define AXIS_H

#include <QString>

#include "models/types/motor_state/motor_state.h"

class AxisState
{
public:
    AxisState(QString id, MotorState motor);

    QtJson::JsonObject currentState();

    QString getId() const;

    MotorState& getMotor();

    double currentAxisPos();

private:
    QString m_id;
    MotorState m_motor;

    int m_feedrate;
};

#endif // AXIS_H
