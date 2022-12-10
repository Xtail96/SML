#include "spindel.h"

Spindel::Spindel(QString id,
                 bool enabled,
                 size_t currentRotations,
                 size_t minRotations,
                 size_t maxRotations,
                 QString label) :
    Device(id, enabled, label),
    m_maxRotations(maxRotations),
    m_minRotations(minRotations),
    m_currentRotations(currentRotations)
{
    if(m_currentRotations > m_maxRotations)
        m_currentRotations = m_maxRotations;
    if(m_currentRotations < m_minRotations)
        m_currentRotations = m_minRotations;
}

Spindel::~Spindel()
{

}
