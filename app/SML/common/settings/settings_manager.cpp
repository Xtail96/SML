#include "settings_manager.h"

SettingsManager::SettingsManager() : SettingsManager(DEFAULT_SETTINGS_FILE)
{
}

SettingsManager::SettingsManager(QString settingsFile)
{
#ifdef Q_OS_MACX
    QString settingsPath = qApp->applicationDirPath() + "/" + settingsFile;
#else
    QString settingsPath = DEFAULT_SETTINGS_DIR + settingsFile;
#endif

    // проверка на существование файла с настройками
    if (!QFileInfo::exists(settingsPath))
    {
        // если не существует, выводим соответствующее сообщение
        qInfo() << "Settings file not found. Generate default settings.";

        // используем настройки по умолчанию
        settings = std::shared_ptr<QSettings>( new QSettings(settingsPath, QSettings::IniFormat) );
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

        QString message = QStringLiteral("В файла настроек отсутствует ключ ") + key + QStringLiteral(" для секции ") + group;
        throw std::invalid_argument(message.toStdString());
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
    settings->beginGroup("AdapterServer");
        settings->setValue("Port", 1234);
    settings->endGroup();

    settings->beginGroup("ExternalTools");
        settings->setValue("DeviceAdapter", "/Users/xtail/Projects/SML/base_adapters/DeviceArduinoAdapter/app/build-DeviceArduinoAdapter-Desktop_Qt_5_12_8_clang_64bit-Release/DeviceArduinoAdapter");
        settings->setValue("MotionAdapter", "/Users/xtail/Projects/SML/base_adapters/MotionEchoAdapter/app/build-MotionEchoAdapter-Desktop_Qt_5_12_8_clang_64bit-Release/MotionEchoAdapter");
        //settings->setValue("MotionAdapter", "/Users/xtail/Projects/SML/base_adapters/MotionArduinoAdapter/app/build-MotionArduinoAdapter-Desktop_Qt_5_12_8_clang_64bit-Release/MotionArduinoAdapter");
#ifdef Q_OS_MACX
        //settings->setValue("GCodesViewer", "/Users/xtail/Projects/SML/gcodes_viewers/ElectronGCodesViewer/dist/mac/ElectronGCodesViewer.app/Contents/MacOS/ElectronGCodesViewer");
        settings->setValue("GCodesViewer", "/Users/xtail/Projects/SML/gcodes_viewers/CandleGCodesViewer/app/build-CandleGCodesViewer-Desktop_Qt_5_12_8_clang_64bit-Release/CandleGCodesViewer");
#else
        settings->setValue("GCodesViewer", "CandleGCodesViewer");
#endif
    settings->endGroup();

    settings->beginGroup("DefaultDirs");
        QString currentDir = QCoreApplication::applicationDirPath();
        settings->setValue("SaveDir", currentDir + "/files/programs");
        settings->setValue("OpenDir", currentDir);
        settings->setValue("ImportDir", currentDir);
        settings->setValue("ImportResDir", currentDir);
    settings->endGroup();

    // применяем изменения
    saveSettings();
}

QStringList SettingsManager::settingsKeys()
{
    return settings->allKeys();
}
