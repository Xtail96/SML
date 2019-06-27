#include "settingsmanager.h"

SettingsManager::SettingsManager() : SettingsManager(DEFAULT_SETTINGS_PATH)
{
}

SettingsManager::SettingsManager(QString settingsPath)
{
    // проверка на существование файла с настройками
    if (!QFileInfo::exists(settingsPath))
    {
        // если не существует, выводим соответствующее сообщение
        qDebug() << "Файл с настройками не найден. Используем настройки по умолчанию";

        // используем настройки по умолчанию
        settings = std::shared_ptr<QSettings>( new QSettings(DEFAULT_SETTINGS_PATH, QSettings::IniFormat) );
        // используем кодировку юникод
        settings->setIniCodec("UTF-8");

        generateDefaultSettings();
    }
    else
    {
        settings = std::shared_ptr<QSettings>( new QSettings(settingsPath, QSettings::IniFormat) );
        // используем кодировку юникод
        settings->setIniCodec("UTF-8");
    }
}

void SettingsManager::importSettings(QString settingsPath)
{
    // проверка на существование файла с настройками
    if (QFileInfo::exists(settingsPath))
    {
        // получение настроек из файла по указанному пути
        QSettings importSettings(settingsPath, QSettings::IniFormat);

        // перезапись основных настроек
        for (QString key : importSettings.allKeys())
        {
            settings->setValue(key, importSettings.value(key));
        }

        // сохранение основных настроек
        saveSettings();

        qDebug() << "Настройки импортированы. Перезапустите приложение для их применения.";
    }
}

SettingsManager::~SettingsManager()
{
    // сохраняем настройки перед выходом
    saveSettings();
}

void SettingsManager::saveSettings()
{
    settings->sync();
}

void SettingsManager::exportSettings(QString path)
{
    QSettings expSettings(path, QSettings::IniFormat);

    for (QString key : settings->allKeys())
    {
        expSettings.setValue(key, settings->value(key));
    }

    expSettings.sync();
}

QVariant SettingsManager::get(QString group, QString key) const
{
    QVariant value;

    settings->beginGroup(group);

    if (settings->contains(key))
    {
        value = settings->value(key);
    }
    else
    {
        settings->endGroup();
        throw std::invalid_argument("Отсутствует ключ " + key.toStdString());
    }

    settings->endGroup();

    return value;
}

void SettingsManager::set(QString group, QString key, QVariant value)
{
    settings->beginGroup(group);
        settings->setValue(key, value);
    settings->endGroup();
}

void SettingsManager::generateDefaultSettings()
{
    settings->beginGroup("General");
        settings->setValue("AxisesCount", 5);
    settings->endGroup();

    settings->beginGroup("ServerSettings");
        settings->setValue("ServerAddress", "ws://localhost:1234");
        settings->setValue("DebugMode", 1);
    settings->endGroup();

    // применяем изменения
    saveSettings();
}

QStringList SettingsManager::settingsKeys()
{
    return settings->allKeys();
}
