#include "spindel.h"

Spindel::Spindel(QString code, const SettingsManager &sm, QObject *parent) :
    Device(code, sm, parent)
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
        m_upperBound = QVariant(sm.get(m_name, "UpperBound")).toULongLong();
        m_lowerBound = QVariant(sm.get(m_name, "LowerBound")).toULongLong();
        m_currentRotations = m_lowerBound;
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки устройства " + m_name, e.what()).exec();
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
