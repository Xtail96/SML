#include "axis_state.h"

AxisState::AxisState(QString id, MotorState motor) :
    m_id(id),
    m_motor(motor)
{
}

QtJson::JsonObject AxisState::currentState()
{
    QtJson::JsonObject axisState = {};

    axisState["id"] = m_id;
    axisState["position"] = this->currentAxisPos();
    axisState["step"] = m_motor.step();
    axisState["feedrate"] = m_motor.delay();

    return axisState;
}

QString AxisState::getId() const
{
    return m_id;
}

MotorState &AxisState::getMotor()
{
    return m_motor;
}

double AxisState::currentAxisPos()
{
    return m_motor.currentPos();
}
