#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#include <algorithm>
#include <map>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>

#include "machinetool.h"

class SettingsManager
{
private:
    /// Настройки станка в формате словаря
    std::map<std::string, std::string> settingsMap;

    /// Директория для сохранения настроек
    std::string settingsPath = "settingsOrigin.ini";
public:
    SettingsManager();
    std::string readSettings(const std::string &path);
    void writeSettings(const std::string &path);
    void importSettings();
    void exportSettings();
    //void setupToMachineTool();

    char push_backToName(const char &e);
    std::string eraseSlashRSymbols(const std::string &settingsString);
    void parseSettings(const std::string &settings);
    std::pair<std::string, std::string> parseSettingsStep(const std::string &settings, unsigned int &position, const std::__1::string &name);

    std::map<std::string, std::string> getSettings();
    QString getSettingsPath();
};

#endif // SETTINGSMANAGER_H
