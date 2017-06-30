#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QCoreApplication>
#include <QFile>
#include <QSettings>
#include <QString>
#include <QDateTime>
#include <QMessageBox>
#include <memory>

class SettingsManager
{
private:
    const QString defaultSettingsIniPath = "settings.ini";

    std::shared_ptr<QSettings> settings;

public:
    SettingsManager();
    SettingsManager(QString settingsIniPath);
    ~SettingsManager();

    void generateDefaultSettings();
};

#endif // SETTINGSMANAGER_H
