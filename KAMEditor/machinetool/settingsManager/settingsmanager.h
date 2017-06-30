#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QSettings>
#include <memory>

class SettingsManager
{
private:
    std::shared_ptr<QSettings> settings;

public:
    SettingsManager();
};

#endif // SETTINGSMANAGER_H
