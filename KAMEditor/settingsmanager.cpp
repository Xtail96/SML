#include "settingsmanager.h"

SettingsManager::SettingsManager()
{
    QString settingsString = readSettings(QString::fromStdString(settingsPath));
    parseSettings(settingsString);
}

QString SettingsManager::readSettings(const QString &path)
{
    QFile inputFile(path);
    if(!inputFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", inputFile.errorString());
    }
    QTextStream in(&inputFile);
    QString settings = in.readAll();
    inputFile.close();
    return settings;
}

void SettingsManager::writeSettings()
{
    QFile outputFile(QString::fromStdString(settingsPath));
    if(!outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QMessageBox::information(0, "error", outputFile.errorString());
    }
    QTextStream out(&outputFile);
    outputFile.close();
}

void SettingsManager::importSettings()
{
    QString path = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.txt, *.ini");
    readSettings(path);
}


void SettingsManager::parseSettings(const QString &settings)
{
    std::string settingsTmp = settings.toStdString();
    bool ignoreFlag = false;
    unsigned int position = 0;
    while(position < settingsTmp.length())
    {
        if(!ignoreFlag)
        {
            if(settingsTmp[position] == '[')
            {
                ignoreFlag = true;
            }
            else
            {
                std::pair<std::string, std::string> settingsElement = parseSettingsStep(settingsTmp, position);
                settingsMap.insert(settingsElement);
            }
        }
        else
        {
            if(settingsTmp[position] == ']')
            {
                ignoreFlag = false;
                position+=2;
            }
        }
        position++;
    }
}

std::pair<std::string, std::string> SettingsManager::parseSettingsStep(const std::string &settings, unsigned int &position)
{
    std::string tmp = "";
    std::pair<std::string, std::string> currentElement;
    if(position < settings.length())
    {
        while(settings[position] != '\n' && settings[position] != '\r')
        {
            tmp += settings[position];
            if(position < settings.length() - 1)
            {
                position++;
            }
            else
            {
                break;
            }
        }
        position++;
        bool equivalentFlag = false;
        std::string firstArgument = "";
        std::string secondArgument = "";
        for(auto it : tmp)
        {
            if(it != '=')
            {
                if(!equivalentFlag)
                {
                    firstArgument += it;
                }
                else
                {
                    secondArgument += it;
                }
            }
            else
            {
                equivalentFlag = true;
            }
        }
        currentElement = std::make_pair(firstArgument, secondArgument);
    }
    else
    {
        std::make_pair('0', '0');
    }
    return currentElement;
}

std::map<std::string, std::string> SettingsManager::getSettings()
{
    return settingsMap;
}

