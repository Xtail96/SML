#include "motor.h"

Motor::Motor(int id, double step) :
    m_id(id),
    m_step(step),
    m_isMoving(false)
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
