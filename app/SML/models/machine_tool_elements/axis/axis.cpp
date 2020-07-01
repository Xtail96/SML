#include "axis.h"

Axis::Axis(QString id, double initialPos, QObject *parent) :
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

void Axis::setCurrentPosition(double currentPosition)
{
    currentPosition = qRound(currentPosition * 1000.0) / 1000.0;
    m_currentPosition = currentPosition;
    emit this->currentPositionChanged();
}

QString Axis::axisSettings() const
{
    QString settings = "";
    settings += QString("Идентификатор оси: ") + m_id + QString(".");
    return "";
}

QString Axis::id() const
{
    return m_id;
}
