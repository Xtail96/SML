#include "axis.h"

Axis::Axis(QString id, Motor motor) :
    m_id(id),
    m_motor(motor)
{
}

QtJson::JsonObject Axis::currentState()
{
    QtJson::JsonObject axisState = {};

    axisState["id"] = m_id;
    axisState["position"] = this->currentAxisPos();
    axisState["step"] = m_motor.step();
    axisState["feedrate"] = m_motor.delay();

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

double Axis::currentAxisPos()
{
    return m_motor.initialPos() + m_motor.currentProgress() * m_motor.step();
}
