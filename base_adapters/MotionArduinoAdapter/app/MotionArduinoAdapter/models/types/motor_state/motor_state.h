#ifndef MOTOR_H
#define MOTOR_H

#include <QDebug>

#include "libs/jsonparser/json.h"

class MotorState
{
public:
    MotorState(int id);

    int id() const;

    bool isMoving() const;

    int initialPos() const;

    int targetPos() const;

    int currentPos() const;

    void setCurrentProgress(int currentProgress);

    int delay() const;

    QtJson::JsonObject prepareMotorCmd(int targetPos, int feedrate);

private:
    int m_id;

    bool m_isMoving;

    int m_initialPos;
    int m_targetPos;
    int m_currentProgress;

    int m_delay;
};

#endif // MOTOR_H
