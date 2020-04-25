#include "motor.h"

Motor::Motor(int id, double step) :
    m_id(id),
    m_step(step),
    m_isMoving(false),
    m_initialPos(0.0),
    m_targetPos(0.0),
    m_currentProgress(0)
{

}

int Motor::id() const
{
    return m_id;
}

double Motor::step() const
{
    return m_step;
}

void Motor::setStep(double step)
{
    m_step = step;
}

bool Motor::isMoving() const
{
    return m_isMoving;
}

void Motor::setIsMoving(bool isMoving)
{
    m_isMoving = isMoving;
}

double Motor::initialPos() const
{
    return m_initialPos;
}

void Motor::setInitialPos(double initialPos)
{
    m_initialPos = initialPos;
}

double Motor::targetPos() const
{
    return m_targetPos;
}

void Motor::setTargetPos(double targetPos)
{
    m_targetPos = targetPos;
}

double Motor::currentProgress() const
{
    return m_currentProgress;
}

void Motor::setCurrentProgress(double currentProgress)
{
    m_currentProgress = currentProgress;
}

int Motor::delay() const
{
    return m_delay;
}

void Motor::setDelay(int delay)
{
    m_delay = delay;
}

QtJson::JsonObject Motor::getMotorCmd()
{
    QtJson::JsonObject result = {};

    double posRelative = m_targetPos - m_initialPos;

    result["steps"] = int(posRelative / m_step);
    result["delay"] = m_delay;
    return result;
}
