#include "axis_state.h"

AxisState::AxisState(AxisId id, double currentPosition) :
    m_id(id),
    m_currentPosition(0.0),
    m_zeroPosition(0.0),
    m_parkPosition(0.0)
{
    this->setCurrentPosition(currentPosition);
    this->setZeroPosition(0.0);
    this->setParkPosition(0.0);
}

AxisState::~AxisState()
{
}

double AxisState::currentPositionFromBase() const
{
    return m_currentPosition;
}

double AxisState::currentPositionFromZero() const
{
    return m_currentPosition - m_zeroPosition;
}

void AxisState::setCurrentPosition(double absPosition)
{
    if(AxisState::isEqual(m_currentPosition, absPosition)) return;
    m_currentPosition = AxisState::decoratePosition(absPosition);
}

double AxisState::zeroPosition() const
{
    return m_zeroPosition;
}

double AxisState::parkPosition() const
{
    return m_parkPosition;
}

void AxisState::setZeroPosition(double zeroPosition)
{
    if(AxisState::isEqual(m_zeroPosition, zeroPosition)) return;
    m_zeroPosition = AxisState::decoratePosition(zeroPosition);
}

void AxisState::setParkPosition(double parkPosition)
{
    if(AxisState::isEqual(m_parkPosition, parkPosition)) return;
    m_parkPosition = AxisState::decoratePosition(parkPosition);
}

QString AxisState::toString() const
{
    QString settings = "";
    settings += QString("Идентификатор оси: ") + m_id + QString(".");
    return settings;
}

AxisId AxisState::id() const
{
    return m_id;
}

QString AxisState::decoratedId() const
{
    return AxisState::decorateId(m_id);
}

QString AxisState::decorateId(AxisId id)
{
    QString result = "";
    switch (id)
    {
    case AxisId::X:
        result = "X";
        break;
    case AxisId::Y:
        result = "Y";
        break;
    case AxisId::Z:
        result = "Z";
        break;
    case AxisId::A:
        result = "A";
        break;
    case AxisId::B:
        result = "B";
        break;
    case AxisId::C:
        result = "C";
        break;
    case AxisId::U:
        result = "U";
        break;
    case AxisId::V:
        result = "V";
        break;
    case AxisId::W:
        result = "W";
        break;
    }
    return result;
}

AxisId AxisState::idFromStr(QString value)
{
    value = value.toLower();

    if(value == "x") return AxisId::X;
    if(value == "y") return AxisId::Y;
    if(value == "z") return AxisId::Z;
    if(value == "a") return AxisId::A;
    if(value == "b") return AxisId::B;
    if(value == "c") return AxisId::C;
    if(value == "u") return AxisId::U;
    if(value == "v") return AxisId::V;
    if(value == "w") return AxisId::W;

    throw std::invalid_argument("unknown axis " + value.toStdString());
}

bool AxisState::operator==(const AxisState &other) const
{
    return (m_id == other.id());
}

bool AxisState::operator!=(const AxisState &other) const
{
    return (m_id != other.id());
}

bool AxisState::operator >=(const AxisState &other) const
{
    return (m_id >= other.id());
}

bool AxisState::operator<=(const AxisState &other) const
{
    return (m_id <= other.id());
}

bool AxisState::operator >(const AxisState &other) const
{
    return (m_id > other.id());
}

bool AxisState::operator<(const AxisState &other) const
{
    return (m_id < other.id());
}

double AxisState::decoratePosition(double pos)
{
    return qRound(pos * 1000.0) / 1000.0;
}

bool AxisState::isEqual(double pos1, double pos2)
{
    return qRound(pos1 * 1000) == qRound(pos2 * 1000);
}
