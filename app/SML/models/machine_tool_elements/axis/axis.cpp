#include "axis.h"

Axis::Axis(QString name,
           double lowerBound,
           double upperBound,
           double basingFeedrate,
           QObject *parent) :
    QObject(parent),
    m_name(name),
    m_currentPosition(0.0),
    m_basingFeedrate(basingFeedrate),
    m_lowerBound(lowerBound),
    m_upperBound(upperBound)
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

double Axis::currentPosition() const
{
    return m_currentPosition;
}

void Axis::setCurrentPosition(double currentPosition)
{
    currentPosition = qRound(currentPosition * 1000.0) / 1000.0;
    m_currentPosition = currentPosition;
    emit this->currentPositionChanged();
}

double Axis::basingFeedrate() const
{
    return m_basingFeedrate;
}

void Axis::setBasingFeedrate(double basingFeedrate)
{
    m_basingFeedrate = basingFeedrate;
}

QString Axis::axisSettings() const
{
    QString settings = "";
    settings += QString("Имя оси: ") + m_name + QString("; ");
    settings += QString("Минимальное значение: ") + QString::number(m_lowerBound) + QString("; ");
    settings += QString("Максимальное значение: ") + QString::number(m_upperBound) + QString(".");
    settings += QString("Скорость базирования: ") + QString::number(m_basingFeedrate) + QString("; ");
    return settings;
}

double Axis::lowerBound() const
{
    return m_lowerBound;
}

void Axis::setLowerBound(double lowerBound)
{
    m_lowerBound = lowerBound;
}

double Axis::upperBound() const
{
    return m_upperBound;
}

void Axis::setUpperBound(double upperBound)
{
    m_upperBound = upperBound;
}
