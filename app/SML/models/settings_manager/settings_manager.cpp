#include "settings_manager.h"

SettingsManager::SettingsManager() : SettingsManager(DEFAULT_SETTINGS_FILE)
{
}

SettingsManager::SettingsManager(QString settingsFile)
{
#ifdef Q_OS_MACX
    QString settingsPath = qApp->applicationDirPath() + settingsFile;
#else
    QString settingsPath = DEFAULT_SETTINGS_DIR + settingsFile;
#endif

    // проверка на существование файла с настройками
    if (!QFileInfo::exists(settingsPath))
    {
        // если не существует, выводим соответствующее сообщение
        QMessageBox(QMessageBox::Warning, "Ошибка",
                    "Файл с настройками не найден. Используем настройки по умолчанию").exec();

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

        QMessageBox(QMessageBox::Information, "Информация", "Настройки импортированы. Перезапустите приложение для их применения.").exec();
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

        QString message = QStringLiteral("Отсутствует ключ ") + key;
        throw InvalidConfigurationException(message);
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
    settings->beginGroup("Main");
        //settings->setValue("VendorId", 0x10c4);
        //settings->setValue("ProductId", 0xea61);
        //settings->setValue("Name", "semil");
        settings->setValue("AxisesCount", 5);
        settings->setValue("SensorsCount", 8);
        settings->setValue("SpindelsCount", 3);
        settings->setValue("SupportDevicesCount", 0);
        settings->setValue("SensorsBufferSize", 2);
        settings->setValue("DevicesBufferSize", 3);
    settings->endGroup();

    settings->beginGroup("ServerSettings");
        settings->setValue("ServerPort", 1234);
        settings->setValue("DebugMode", 1);
    settings->endGroup();

    settings->beginGroup("DefaultDirs");
        QString currentDir = QCoreApplication::applicationDirPath();
        settings->setValue("SaveDir", currentDir + "/files/programs");
        settings->setValue("OpenDir", currentDir);
        settings->setValue("ImportDir", currentDir);
        settings->setValue("ImportResDir", currentDir);
    settings->endGroup();

    settings->beginGroup("TableSize");
        settings->setValue("SizeX", -1374);
        settings->setValue("SizeY", 1386);
        settings->setValue("SizeZ", -306);
        settings->setValue("SizeA", -185);
        settings->setValue("SizeB", 100);
        settings->setValue("SavedSizeZ", 100);
    settings->endGroup();

    settings->beginGroup("Tools");
    settings->endGroup();

    settings->beginGroup("ExternalMCSettings");
        settings->setValue("LookAheadLength", 3);
        settings->setValue("BreakAngle", 30);
        settings->setValue("CollinearTollerance", 0.01);
        settings->setValue("CornerTollerance", 0.07);
        settings->setValue("FacetAngle", 3);
    settings->endGroup();

    settings->beginGroup("AxisX");
        settings->setValue("Label", "X");
        settings->setValue("Channel", 8);
        settings->setValue("Jerk", 10000);
        settings->setValue("Acceleration", 250);
        settings->setValue("Speed", 250);
        settings->setValue("BazaSearchSpeed", 60);
        settings->setValue("Step", 0.05);
        settings->setValue("Invert", false);
    settings->endGroup();

    settings->beginGroup("AxisY");
        settings->setValue("Label", "Y");
        settings->setValue("Channel", 8);
        settings->setValue("Jerk", 10000);
        settings->setValue("Acceleration", 400);
        settings->setValue("Speed", 250);
        settings->setValue("BazaSearchSpeed", 60);
        settings->setValue("Step", 0.05);
        settings->setValue("Invert", false);
    settings->endGroup();

    settings->beginGroup("AxisZ");
        settings->setValue("Label", "Z");
        settings->setValue("Channel", 8);
        settings->setValue("Jerk", 6000);
        settings->setValue("Acceleration", 100);
        settings->setValue("Speed", 50);
        settings->setValue("BazaSearchSpeed", 25);
        settings->setValue("Step", 0.05);
        settings->setValue("Invert", false);
    settings->endGroup();

    settings->beginGroup("AxisA");
        settings->setValue("Label", "A");
        settings->setValue("Channel", 8);
        settings->setValue("Jerk", 10000);
        settings->setValue("Acceleration", 100);
        settings->setValue("Speed", 100);
        settings->setValue("BazaSearchSpeed", 10);
        settings->setValue("Step", 0.05);
        settings->setValue("Invert", false);
    settings->endGroup();

    settings->beginGroup("AxisB");
        settings->setValue("Label", "B");
        settings->setValue("Channel", 8);
        settings->setValue("Jerk", 10000);
        settings->setValue("Acceleration", 400);
        settings->setValue("Speed", 200);
        settings->setValue("BazaSearchSpeed", 40);
        settings->setValue("Step", 0.05);
        settings->setValue("Invert", false);
    settings->endGroup();

    settings->beginGroup("Sensor0");
        settings->setValue("Uid", "SensorAxisX");
        settings->setValue("Label", "Датчик оси X");
        settings->setValue("PortNumber", 0);
        settings->setValue("InputNumber", 0);
        settings->setValue("BoardName", "portal");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("Sensor1");
        settings->setValue("Uid", "SensorAxisY");
        settings->setValue("Label", "Датчик оси Y");
        settings->setValue("PortNumber", 0);
        settings->setValue("InputNumber", 1);
        settings->setValue("BoardName", "portal");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("Sensor2");
        settings->setValue("Uid", "SensorAxisZ");
        settings->setValue("Label", "Датчик оси Z");
        settings->setValue("PortNumber", 0);
        settings->setValue("InputNumber", 2);
        settings->setValue("BoardName", "portal");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("Sensor3");
        settings->setValue("Uid", "SensorAxisA");
        settings->setValue("Label", "Датчик оси A");
        settings->setValue("PortNumber", 0);
        settings->setValue("InputNumber", 3);
        settings->setValue("BoardName", "portal");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("Sensor4");
        settings->setValue("Uid", "SensorAxisB");
        settings->setValue("Label", "Датчик оси B");
        settings->setValue("PortNumber", 0);
        settings->setValue("InputNumber", 4);
        settings->setValue("BoardName", "portal");
        settings->setValue("ActiveState", true);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("Sensor5");
        settings->setValue("Uid", "SensorAxisC");
        settings->setValue("Label", "Датчик оси C");
        settings->setValue("PortNumber", 0);
        settings->setValue("InputNumber", 5);
        settings->setValue("BoardName", "portal");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("Sensor6");
        settings->setValue("Uid", "SensorAxisD");
        settings->setValue("Label", "Датчик оси D");
        settings->setValue("PortNumber", 0);
        settings->setValue("InputNumber", 6);
        settings->setValue("BoardName", "portal");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("Sensor7");
        settings->setValue("Uid", "SensorZero");
        settings->setValue("Label", "Датчик Ноля");
        settings->setValue("PortNumber", 1);
        settings->setValue("InputNumber", 0);
        settings->setValue("BoardName", "portal");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#b22222");
    settings->endGroup();

    settings->beginGroup("Spindel0");
        settings->setValue("Uid", 0);
        settings->setValue("Label", "Фрезер");
        settings->setValue("ActiveState", false);
        settings->setValue("NeedToDisplay", true);
        settings->setValue("UpperBound", 24000);
        settings->setValue("LowerBound", 2000);
    settings->endGroup();

    settings->beginGroup("Spindel1");
        settings->setValue("Uid", 1);
        settings->setValue("Label", "Фрезер 2");
        settings->setValue("ActiveState", false);
        settings->setValue("NeedToDisplay", true);
        settings->setValue("UpperBound", 12000);
        settings->setValue("LowerBound", 8000);
    settings->endGroup();

    settings->beginGroup("Spindel2");
        settings->setValue("Uid", 2);
        settings->setValue("Label", "Шпиндель R");
        settings->setValue("ActiveState", false);
        settings->setValue("NeedToDisplay", true);
        settings->setValue("UpperBound", 2000);
        settings->setValue("LowerBound", 0);
    settings->endGroup();

    settings->beginGroup("SupportDevice0");
        settings->setValue("Uid", 3);
        settings->setValue("Label", "Муфта");
        settings->setValue("ActiveState", false);
        settings->setValue("NeedToDisplay", true);
    settings->endGroup();

    settings->beginGroup("SupportDevice1");
        settings->setValue("Uid", 4);
        settings->setValue("Label", "САС");
        settings->setValue("ActiveState", false);
        settings->setValue("NeedToDisplay", false);
    settings->endGroup();

    // применяем изменения
    saveSettings();
}

QStringList SettingsManager::settingsKeys()
{
    return settings->allKeys();
}
