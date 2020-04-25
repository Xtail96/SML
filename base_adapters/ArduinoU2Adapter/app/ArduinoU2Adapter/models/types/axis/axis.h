#ifndef AXIS_H
#define AXIS_H

#include <QString>

#include "models/types/axis/motor/motor.h"
#include "models/types/axis/task/task.h"

class Axis
{
public:
    Axis(QString id, Motor motor);

    QtJson::JsonObject currentState();

    QString getId() const;

    Motor& getMotor();
    Task& getTask();

    double currentAxisPos();
    void setTask(double target, int feedrate);

private:
    QString m_id;
    Motor m_motor;
    Task m_lastTask;

    int m_feedrate;
};

#endif // AXIS_H
