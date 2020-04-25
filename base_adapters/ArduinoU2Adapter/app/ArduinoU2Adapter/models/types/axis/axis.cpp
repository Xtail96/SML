#include "axis.h"

Axis::Axis(QString id, Motor motor) :
    m_id(id),
    m_motor(motor),
    m_lastTask(0.0, 0.0, 0.0)
{
}

QtJson::JsonObject Axis::currentState()
{
    QtJson::JsonObject axisState = {};

    axisState["id"] = m_id;
    axisState["position"] = this->currentAxisPos();
    axisState["step"] = m_motor.step();
    axisState["feedrate"] = m_lastTask.feedrate();

    return axisState;
}

QString Axis::getId() const
{
    return m_id;
}

Motor &Axis::getMotor()
{
    return m_motor;
}

Task &Axis::getTask()
{
    return m_lastTask;
}

double Axis::currentAxisPos()
{
    return m_lastTask.initialPos() + m_lastTask.currentMotorProgress() * m_motor.step();
}

void Axis::setTask(double target, int feedrate)
{
    m_lastTask = Task(this->currentAxisPos(), target, feedrate);
}
