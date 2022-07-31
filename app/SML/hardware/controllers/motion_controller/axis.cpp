#include "axis.h"

Axis::State::State(Axis::Id id, double currentPosition) :
    m_id(id),
    m_currentPosition(0.0),
    m_zeroPosition(0.0),
    m_parkPosition(0.0)
{
    this->setCurrentPosition(currentPosition);
    this->setZeroPosition(0.0);
    this->setParkPosition(0.0);
}

Axis::State::~State()
{
}

double Axis::State::currentPositionFromBase() const
{
    return m_currentPosition;
}

double Axis::State::currentPositionFromZero() const
{
    return m_currentPosition - m_zeroPosition;
}

void Axis::State::setCurrentPosition(double absPosition)
{
    if(Axis::State::isPosEqual(m_currentPosition, absPosition)) return;
    m_currentPosition = Axis::State::decoratePosition(absPosition);
}

double Axis::State::zeroPosition() const
{
    return m_zeroPosition;
}

double Axis::State::parkPosition() const
{
    return m_parkPosition;
}

void Axis::State::setZeroPosition(double zeroPosition)
{
    if(Axis::State::isPosEqual(m_zeroPosition, zeroPosition)) return;
    m_zeroPosition = Axis::State::decoratePosition(zeroPosition);
}

void Axis::State::setParkPosition(double parkPosition)
{
    if(Axis::State::isPosEqual(m_parkPosition, parkPosition)) return;
    m_parkPosition = Axis::State::decoratePosition(parkPosition);
}

QString Axis::State::toString() const
{
    QString settings = "";
    settings += QString("Идентификатор оси: ") + m_id + QString(".");
    return settings;
}

Axis::Id Axis::State::id() const
{
    return m_id;
}

QString Axis::State::decoratedId() const
{
    return Axis::decorateId(m_id);
}

QString Axis::decorateId(Axis::Id id)
{
    QString result = "";
    switch (id)
    {
    case Axis::Id::X:
        result = "X";
        break;
    case Axis::Id::Y:
        result = "Y";
        break;
    case Axis::Id::Z:
        result = "Z";
        break;
    case Axis::Id::A:
        result = "A";
        break;
    case Axis::Id::B:
        result = "B";
        break;
    case Axis::Id::C:
        result = "C";
        break;
    case Axis::Id::U:
        result = "U";
        break;
    case Axis::Id::V:
        result = "V";
        break;
    case Axis::Id::W:
        result = "W";
        break;
    }
    return result;
}

Axis::Id Axis::idFromStr(QString value)
{
    value = value.toLower();

    if(value == "x") return Axis::Id::X;
    if(value == "y") return Axis::Id::Y;
    if(value == "z") return Axis::Id::Z;
    if(value == "a") return Axis::Id::A;
    if(value == "b") return Axis::Id::B;
    if(value == "c") return Axis::Id::C;
    if(value == "u") return Axis::Id::U;
    if(value == "v") return Axis::Id::V;
    if(value == "w") return Axis::Id::W;

    throw std::invalid_argument("unknown axis " + value.toStdString());
}

bool Axis::State::operator==(const Axis::State &other) const
{
    return (m_id == other.id());
}

bool Axis::State::operator!=(const Axis::State &other) const
{
    return (m_id != other.id());
}

bool Axis::State::operator >=(const Axis::State &other) const
{
    return (m_id >= other.id());
}

bool Axis::State::operator<=(const Axis::State &other) const
{
    return (m_id <= other.id());
}

bool Axis::State::operator >(const Axis::State &other) const
{
    return (m_id > other.id());
}

bool Axis::State::operator<(const Axis::State &other) const
{
    return (m_id < other.id());
}

double Axis::State::decoratePosition(double pos)
{
    return qRound(pos * 1000.0) / 1000.0;
}

bool Axis::State::isPosEqual(double pos1, double pos2)
{
    return qRound(pos1 * 1000) == qRound(pos2 * 1000);
}
