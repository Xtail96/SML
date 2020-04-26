#include "motor_state.h"

MotorState::MotorState(int id, double step) :
    m_id(id),
    m_step(step),
    m_isMoving(false),
    m_initialPos(0.0),
    m_targetPos(0.0),
    m_currentProgress(0)
{

}

int MotorState::id() const
{
    return m_id;
}

double MotorState::step() const
{
    return m_step;
}

bool MotorState::isMoving() const
{
    return m_isMoving;
}

double MotorState::initialPos() const
{
    return m_initialPos;
}

double MotorState::targetPos() const
{
    return m_targetPos;
}

double MotorState::currentPos() const
{
    return m_initialPos + m_currentProgress * m_step;
}

void MotorState::setCurrentProgress(double currentProgress)
{
    m_currentProgress = currentProgress;
    (fabs((m_currentProgress * m_step + m_initialPos) - m_targetPos) < 0.0001) ?
        m_isMoving = false : m_isMoving = true;
}

int MotorState::delay() const
{
    return m_delay;
}

QtJson::JsonObject MotorState::prepareMotorCmd(double targetPos, int feedrate)
{
    m_initialPos = this->currentPos();
    m_targetPos = targetPos;
    m_delay = 1 / (feedrate + 1) + 6;
    m_isMoving = true;
    double posRelative = m_targetPos - m_initialPos;

    QtJson::JsonObject result = {};
    result["steps"] = int(posRelative / m_step);
    result["delay"] = m_delay;
    return result;
}
