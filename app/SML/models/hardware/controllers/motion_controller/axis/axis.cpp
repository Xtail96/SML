#include "axis.h"

Axis::Axis(AxisId id, double initialPosition, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_currentPosition(0.0),
    m_zeroPosition(0.0),
    m_parkPosition(0.0)
{
    this->setCurrentPosition(initialPosition);
    this->setZeroPosition(0.0);
    this->setParkPosition(0.0);
}

Axis::~Axis()
{
}

double Axis::currentPositionFromBase() const
{
    return m_currentPosition;
}

double Axis::currentPositionFromZero() const
{
    return m_currentPosition - m_zeroPosition;
}

void Axis::setCurrentPosition(double absPosition)
{
    if(Axis::isEqual(m_currentPosition, absPosition)) return;
    m_currentPosition = Axis::decoratePosition(absPosition);
    emit this->currentPositionChanged();
}

double Axis::parkPosition() const
{
    return m_parkPosition;
}

void Axis::setZeroPosition(double zeroPosition)
{
    if(Axis::isEqual(m_zeroPosition, zeroPosition)) return;
    m_zeroPosition = Axis::decoratePosition(zeroPosition);
}

void Axis::setParkPosition(double parkPosition)
{
    if(Axis::isEqual(m_parkPosition, parkPosition)) return;
    m_parkPosition = Axis::decoratePosition(parkPosition);
}

QString Axis::toString() const
{
    QString settings = "";
    settings += QString("Идентификатор оси: ") + m_id + QString(".");
    return settings;
}

AxisId Axis::id() const
{
    return m_id;
}

QString Axis::decoratedId() const
{
    return Axis::decorateId(m_id);
}

QString Axis::decorateId(AxisId id)
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

AxisId Axis::idFromStr(QString value)
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

bool Axis::operator==(const Axis &other) const
{
    return (m_id == other.id());
}

bool Axis::operator!=(const Axis &other) const
{
    return (m_id != other.id());
}

bool Axis::operator >=(const Axis &other) const
{
    return (m_id >= other.id());
}

bool Axis::operator<=(const Axis &other) const
{
    return (m_id <= other.id());
}

bool Axis::operator >(const Axis &other) const
{
    return (m_id > other.id());
}

bool Axis::operator<(const Axis &other) const
{
    return (m_id < other.id());
}

double Axis::decoratePosition(double pos)
{
    return qRound(pos * 1000.0) / 1000.0;
}

bool Axis::isEqual(double pos1, double pos2)
{
    return qRound(pos1 * 1000) == qRound(pos2 * 1000);
}
