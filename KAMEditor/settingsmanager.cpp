#include "settingsmanager.h"

SettingsManager::SettingsManager()
{
    std::string settingsString = readSettings(settingsPath);
    parseSettings(settingsString);
}

std::string SettingsManager::readSettings(const std::string &path)
{
    QString qpath = QString::fromStdString(path);
    QFile inputFile(qpath);
    if(!inputFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", inputFile.errorString());
    }
    QTextStream in(&inputFile);
    QString settings = in.readAll();
    inputFile.close();
    return settings.toStdString();
}

void SettingsManager::writeSettings(const std::string &path)
{
    QString qpath = QString::fromStdString(path);
    QFile outputFile(qpath);
    if(!outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QMessageBox::information(0, "error", outputFile.errorString());
    }
    QTextStream out(&outputFile);
    for(std::map<std::string, std::string>::iterator it = settingsMap.begin(); it != settingsMap.end(); ++it)
    {
        out << QString::fromStdString(it->first) << "=" << QString::fromStdString(it->second)<<endl;
    }
    outputFile.close();
}

void SettingsManager::importSettings()
{
    QString qpath = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.txt, *.ini");
    std::string settingsString = readSettings(qpath.toStdString());
    parseSettings(settingsString);
    writeSettings(settingsPath);
}

void SettingsManager::exportSettings()
{
    QString qpath = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.txt, *.ini");
    writeSettings(qpath.toStdString());
}

char SettingsManager::push_backToName(const char &e)
{
    char tmp = e;
    switch (tmp)
    {
    case ' ':
        tmp = '_';
        break;
    default:
        //tmp = std::tolower(tmp);
        break;
    }
    return tmp;
}

std::string SettingsManager::eraseSlashRSymbols(const std::string &settingsString)
{
    std::string tmp = "";
    for(auto it : settingsString)
    {
        if(it != '\r')
        {
            tmp+=it;
        }
    }
    return tmp;
}

void SettingsManager::parseSettings(const std::string &settings)
{
    std::string settingsString = settings;
    std::string settingsTmp = eraseSlashRSymbols(settingsString);
    bool ignoreFlag = false;
    unsigned int position = 0;
    std::string name = "";
    while(position < settingsTmp.length())
    {
        if(!ignoreFlag)
        {
            if(settingsTmp[position] == '[')
            {
                ignoreFlag = true;
                name = "";
            }
            else
            {
                std::pair<std::string, std::string> settingsElement = parseSettingsStep(settingsTmp, position, name);
                settingsMap.insert(settingsElement);
            }
        }
        else
        {
            if(settingsTmp[position] == ']')
            {
                ignoreFlag = false;
                name += '_';
                position++;
            }
            else
            {
                char newLitera = push_backToName(settingsTmp[position]);
                name += newLitera;
            }
        }
        position++;
    }
}

std::pair<std::string, std::string> SettingsManager::parseSettingsStep(const std::string &settings, unsigned int &position, const std::string &name)
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
        bool equivalentFlag = false;
        std::string firstArgument = name;
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

QString SettingsManager::getSettingsPath()
{
    return QString::fromStdString(settingsPath);
}

