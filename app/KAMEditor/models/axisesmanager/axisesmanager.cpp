#include "axisesmanager.h"

AxisesManager::AxisesManager(SettingsManager *settingsManager) :
    m_softLimitsEnable(false)
{
    if(settingsManager != nullptr)
    {
        setup(settingsManager);
    }
    else
    {
        SettingsManager* sm = new SettingsManager();
        setup(sm);
        delete sm;
    }
}

AxisesManager::~AxisesManager()
{

}

void AxisesManager::setup(SettingsManager *settingsManager)
{
    size_t axisesCount = 3;
    try
    {
        axisesCount = settingsManager->get("MachineToolInformation", "AxisesCount").toUInt();
         for(size_t i = 0; i < axisesCount; i++)
         {
             std::shared_ptr<Axis> axis = std::shared_ptr<Axis>(new Axis(SML_AXISES_NAMES.getNameByKey(i), settingsManager));
             m_axises.push_back(axis);
         }
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации", QString("Ошибка инициализации менеджера осей!") + QString(e.what())).exec();
    }
}

void AxisesManager::updateCurrentCoordinates(Point newCoordinates)
{
    // todo add soft limits
    if((size_t) newCoordinates.size() <= (size_t) m_axises.size())
    {
        for(size_t i = 0; i < newCoordinates.size(); i++)
        {
            m_axises.operator [](i)->setCurrentPosition(newCoordinates[i]);
        }
    }
    else
    {
        for(size_t i = 0; i < (size_t) m_axises.size(); i++)
        {
            m_axises.operator [](i)->setCurrentPosition(newCoordinates[i]);
        }
    }
}

Point AxisesManager::getCurrentCoordinatesFromZero()
{
    Point currentFromZero(m_axises.size());
    Point p = getCurrentCoordinatesFromBase();
    currentFromZero = p.operator -=(m_zeroCoordinates);
    return currentFromZero;
}

Point AxisesManager::getCurrentCoordinatesFromBase()
{
    QList<double> axisesCoordinates;
    for(auto axis : m_axises)
    {
        axisesCoordinates.push_back(axis->currentPosition());
    }
    return Point(axisesCoordinates.toVector().toStdVector());
}

Point AxisesManager::getZeroCoordinates() const
{
    return m_zeroCoordinates;
}

void AxisesManager::setZeroCoordinates(const Point &zeroCoordinates)
{
    m_zeroCoordinates = zeroCoordinates;
}

Point AxisesManager::getParkCoordinates() const
{
    return m_parkCoordinates;
}

void AxisesManager::setParkCoordinates(const Point &parkCoordinates)
{
    m_parkCoordinates = parkCoordinates;
}