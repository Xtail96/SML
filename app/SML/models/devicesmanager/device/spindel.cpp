#include "spindel.h"

Spindel::Spindel(QString code, const SettingsManager &sm) :
    Device(code, sm)
{

}

Spindel::~Spindel()
{

}

QStringList Spindel::getParams()
{
    QStringList params;
    params.push_back(QString::number(m_rotations));
    return params;
}

void Spindel::setRotations(const size_t &rotations)
{
    m_rotations = rotations;
}
