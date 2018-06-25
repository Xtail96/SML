#include "spindel.h"

Spindel::Spindel(QString name, QString label, QString index, bool activeState, int mask, size_t lowerBound, size_t upperBound, QObject *parent) :
    Device(name, label, index, activeState, mask, parent),
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

void Spindel::setCurrentState(bool value, QMap<QString, QString> attributes)
{
    if(m_currentState != value)
    {
        m_currentState = value;

        if(!attributes["rotations"].isEmpty())
        {
            size_t rotations = attributes["rotations"].toUInt();
            setCurrentRotations(rotations);
        }

        if(m_currentState == m_activeState)
        {
            emit stateChanged(m_index, true, m_currentRotations);
        }
        else
        {
            emit stateChanged(m_index, false, m_currentRotations);
        }
    }
}

void Spindel::setCurrentState(bool value, size_t rotations)
{
    QMap<QString, QString> spindelAttributes;
    spindelAttributes.insert(QStringLiteral("rotations"), QString::number(rotations));
    setCurrentState(value, spindelAttributes);
}

void Spindel::setCurrentRotations(const size_t &rotations)
{
    if(rotations >= m_lowerBound)
    {
        if(rotations <= m_upperBound)
        {
            m_currentRotations = rotations;
        }
        else
        {
            m_currentRotations = m_upperBound;
        }
    }
    else
    {
        m_currentRotations = m_lowerBound;
    }
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

void Spindel::update(bool state, size_t rotations)
{
    QMap<QString, QString> params;
    params.insert(QStringLiteral("rotations"), QString::number(rotations));

    setCurrentState(state, params);
}
