#include "axis.h"

Axis::Axis(SettingsManager *settingsManager, QObject *parent) : QObject(parent)
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

void Axis::setup(SettingsManager *settingsManager)
{

}
