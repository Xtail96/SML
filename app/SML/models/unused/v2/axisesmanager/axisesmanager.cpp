#include "axisesmanager.h"

AxisesManager::AxisesManager(const SettingsManager &settingsManager)
{
    initialize(settingsManager);
}

AxisesManager::~AxisesManager()
{

}

void AxisesManager::initialize(const SettingsManager &settingsManager)
{
    size_t axisesCount = 3;
    try
    {
         axisesCount = settingsManager.get("MachineToolInformation", "AxisesCount").toUInt();
         for(size_t i = 0; i < axisesCount; i++)
         {
             QSharedPointer<Axis> axis = QSharedPointer<Axis>(new Axis(SML_AXISES_NAMES.getNameByKey(i), settingsManager));
             m_axises.push_back(axis);
         }
         m_zeroCoordinates = Point(m_axises.size());
         m_parkCoordinates = Point(m_axises.size());
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

    if(p.size() == m_zeroCoordinates.size())
    {
        currentFromZero = p.operator -=(m_zeroCoordinates);
    }

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

QStringList AxisesManager::getAxisesNames() const
{
    QStringList names;
    for(auto axis : m_axises)
    {
        names.push_back(axis->name());
    }
    return names;
}

QStringList AxisesManager::getAxisesSettings() const
{
    QStringList axisesSettings;

    for(auto axis : m_axises)
    {
        axisesSettings.push_back(axis->axisSettings());
    }
    return axisesSettings;
}

void AxisesManager::setSoftLimitsMode(bool enable)
{
    for(auto axis : m_axises)
    {
        axis->setSoftLimitsEnable(enable);
    }
}
