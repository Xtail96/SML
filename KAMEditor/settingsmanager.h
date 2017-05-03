#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#include <map>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>

class SettingsManager
{
private:
    /// Настройки станка в формате словаря
    std::map<std::string, std::string> settingsMap;

    /// Директория для сохранения настроек
    std::string settingsPath = "settings.ini";
public:
    SettingsManager();
    QString readSettings(const QString &path);
    void writeSettings();
    void importSettings();

    void parseSettings(const QString &settings);
    std::pair<std::string, std::string> parseSettingsStep(const std::string &settings, unsigned int &position);

    std::map<std::string, std::string> getSettings();
};

#endif // SETTINGSMANAGER_H
