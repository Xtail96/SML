#include "axis.h"

Axis::Axis(QString name,
           double length,
           double step,
           bool invertDirection,
           double basingVelocity, QObject *parent) :
    QObject(parent),
    m_name(name),
    m_length(length),
    m_step(step),
    m_currentPosition(0.0),
    m_invertDirection(invertDirection),
    m_currentVelocity(30.0),
    m_basingVelocity(basingVelocity),
    m_softLimitsEnable(false)
{

}

Axis::~Axis()
{

}

QString Axis::name() const
{
    return m_name;
}

void Axis::setName(const QString &name)
{
    m_name = name;
}

double Axis::length() const
{
    return m_length;
}

void Axis::setLength(double length)
{
    m_length = length;
}

double Axis::step() const
{
    return m_step;
}

void Axis::setStep(double step)
{
    m_step = step;
}

double Axis::currentPosition() const
{
    return m_currentPosition;
}

void Axis::setCurrentPosition(double currentPosition)
{
    currentPosition = qRound(currentPosition * 1000.0) / 1000.0;
    m_currentPosition = currentPosition;
    emit this->currentPositionChanged(m_name, m_currentPosition);
}

bool Axis::invertDirection() const
{
    return m_invertDirection;
}

void Axis::setInvertDirection(bool invertDirection)
{
    m_invertDirection = invertDirection;
}

double Axis::currentVelocity() const
{
    return m_currentVelocity;
}

void Axis::setCurrentVelocity(double currentVelocity)
{
    m_currentVelocity = currentVelocity;
}

double Axis::basingVelocity() const
{
    return m_basingVelocity;
}

void Axis::setBasingVelocity(double basingVelocity)
{
    m_basingVelocity = basingVelocity;
}

bool Axis::softLimitsEnable() const
{
    return m_softLimitsEnable;
}

void Axis::setSoftLimitsEnable(bool softLimitsEnable)
{
    m_softLimitsEnable = softLimitsEnable;
}

QString Axis::axisSettings() const
{
    QString settings = "";
    settings += QString("Имя оси: ") + m_name + QString("; ");
    settings += QString("Длина оси: ") + QString::number(m_length) + QString("; ");
    settings += QString("Шаг по оси: ") + QString::number(m_step) + QString("; ");
    settings += QString("Обратное направление: ") + QString::number(m_invertDirection) + QString("; ");
    settings += QString("Скорость базирования: ") + QString::number(m_basingVelocity) + QString("; ");
    return settings;
}
