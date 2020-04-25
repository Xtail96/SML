#include "task.h"

Task::Task(double initialPos, double targetPos, int feedrate) :
    m_initialPos(initialPos),
    m_targetPos(targetPos),
    m_currentMotorProgress(0),
    m_feedrate(feedrate)
{

}

int Task::feedrate() const
{
    return m_feedrate;
}

double Task::initialPos() const
{
    return m_initialPos;
}

double Task::targetPos() const
{
    return m_targetPos;
}

void Task::updateMotorProgress(int motorSteps)
{
    m_currentMotorProgress = motorSteps;
}

int Task::currentMotorProgress() const
{
    return m_currentMotorProgress;
}

QtJson::JsonObject Task::toJson(double step)
{
    QtJson::JsonObject motorCmd = {};

    double posRelative = m_targetPos - m_initialPos;
    motorCmd["steps"] = int(posRelative / step);
    motorCmd["delay"] = int(m_feedrate * 0.20);
    return motorCmd;
}
