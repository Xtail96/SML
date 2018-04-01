#include "axisesmanager.h"

AxisesManager::AxisesManager(SettingsManager *settingsManager)
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
