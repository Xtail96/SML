#include "spindel.h"

Spindel::Spindel(QString code, const SettingsManager &sm) :
    Device(code, sm)
{
    initialize(sm);
}

Spindel::~Spindel()
{

}

void Spindel::initialize(const SettingsManager &sm)
{
    try
    {
        m_upperBound = QVariant(sm.get(m_code, "UpperBound")).toULongLong();
        m_lowerBound = QVariant(sm.get(m_code, "LowerBound")).toULongLong();
        m_currentRotations = m_lowerBound;
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки устройства " + m_code, e.what()).exec();
    }
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
