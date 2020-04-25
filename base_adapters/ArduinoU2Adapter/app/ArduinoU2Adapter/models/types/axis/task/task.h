#ifndef TASK_H
#define TASK_H

#include "libs/jsonparser/json.h"

class Task
{
public:
    Task(double initalPos, double targetPos, int feedrate);

    int feedrate() const;

    double initialPos() const;

    double targetPos() const;

    void setFeedrate(int feedrate);

    void updateMotorProgress(int motorSteps);

    int currentMotorProgress() const;

    QtJson::JsonObject toJson(double step);

private:
    double m_initialPos;
    double m_targetPos;

    int m_currentMotorProgress;

    int m_feedrate;
};

#endif // TASK_H
