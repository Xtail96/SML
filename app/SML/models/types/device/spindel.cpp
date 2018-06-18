#include "spindel.h"

Spindel::Spindel(QString name, QString label, QString index, bool activeState, int mask, size_t lowerBound, size_t upperBound, QObject *parent) :
    Device(name, label, index, activeState, mask),
    m_upperBound(upperBound),
    m_lowerBound(lowerBound),
    m_currentRotations(m_lowerBound)
{
}

Spindel::~Spindel()
{

}

QStringList Spindel::getParams()
{
    QStringList params;
    params.push_back(QString::number(m_currentRotations));
    return params;
}

void Spindel::setCurrentRotations(const size_t &rotations)
{
    m_currentRotations = rotations;
}

void Spindel::setUpperBound(const size_t &upperBound)
{
    m_upperBound = upperBound;
}

void Spindel::setLowerBound(const size_t &lowerBound)
{
    m_lowerBound = lowerBound;
}

size_t Spindel::getUpperBound() const
{
    return m_upperBound;
}

size_t Spindel::getLowerBound() const
{
    return m_lowerBound;
}

size_t Spindel::getCurrentRotations() const
{
    return m_currentRotations;
}
