#include "axis.h"

Axis::Axis(AxisId id, double initialPos, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_currentPosition(0.0)
{
    this->setCurrentPosition(initialPos);
}

Axis::~Axis()
{
}

double Axis::currentPosition() const
{
    return m_currentPosition;
}

void Axis::setCurrentPosition(double absPosition)
{
    absPosition = qRound(absPosition * 1000.0) / 1000.0;
    m_currentPosition = absPosition;
    emit this->currentPositionChanged();
}

QString Axis::axisSettings() const
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
    QString result = "";
    switch (m_id)
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

    throw std::invalid_argument("axis does not exists" + value.toStdString());
}

bool Axis::operator==(const Axis &other) const
{
    return (m_id == other.id());
}

bool Axis::operator!=(const Axis &other) const
{
    return (m_id != other.id());
}
