#ifndef MOTOR_H
#define MOTOR_H

#include <QDebug>

#include "libs/jsonparser/json.h"

class MotorState
{
public:
    MotorState(int id, double step);

    int id() const;

    double step() const;

    bool isMoving() const;

    double initialPos() const;

    double targetPos() const;

    double currentPos() const;

    void setCurrentProgress(double currentProgress);

    int delay() const;

    QtJson::JsonObject prepareMotorCmd(double targetPos, int feedrate);

private:
    int m_id;

    double m_step;

    bool m_isMoving;

    double m_initialPos;
    double m_targetPos;
    double m_currentProgress;

    int m_delay;
};

#endif // MOTOR_H
