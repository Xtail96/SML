#ifndef MOTOR_H
#define MOTOR_H

#include <QDebug>

#include "libs/jsonparser/json.h"

class Motor
{
public:
    Motor(int id, double step);

    int id() const;

    double step() const;
    void setStep(double step);

    bool isMoving() const;
    void setIsMoving(bool isMoving);

    double initialPos() const;
    void setInitialPos(double initialPos);

    double targetPos() const;
    void setTargetPos(double targetPos);

    double currentProgress() const;
    void setCurrentProgress(double currentProgress);

    int delay() const;
    void setDelay(int delay);

    QtJson::JsonObject getMotorCmd();

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
