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
    settings->beginGroup("Main");
        settings->setValue("AvailableAxises", QStringList {
                               "X","Y","Z","A","U"});
        settings->setValue("AvailableSensors", QStringList {
                               "AxisXSensor", "AxisYSensor", "AxisZSensor", "AxisASensor",
                               "AxisBSensor", "AxisCSensor", "AxisUSensor", "AxisVSensor", "AxisWSensor", "ZeroSensor"});
        settings->setValue("SpindelsCount", 3);
        settings->setValue("SupportDevicesCount", 0);
        settings->setValue("SensorsBufferSize", 2);
        settings->setValue("DevicesBufferSize", 3);
    settings->endGroup();

    settings->beginGroup("ServerSettings");
        settings->setValue("ServerPort", 1234);
        settings->setValue("DebugMode", 1);
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

    settings->beginGroup("AxisX");
        settings->setValue("BazaSearchSpeed", 60);
        settings->setValue("LowerBound", 0);
        settings->setValue("UpperBound", 1000);
    settings->endGroup();

    settings->beginGroup("AxisY");
        settings->setValue("BazaSearchSpeed", 60);
        settings->setValue("LowerBound", 0);
        settings->setValue("UpperBound", 500);
    settings->endGroup();

    settings->beginGroup("AxisZ");
        settings->setValue("BazaSearchSpeed", 25);
        settings->setValue("LowerBound", -100);
        settings->setValue("UpperBound", 0);
    settings->endGroup();

    settings->beginGroup("AxisA");
        settings->setValue("BazaSearchSpeed", 10);
        settings->setValue("LowerBound", -90);
        settings->setValue("UpperBound", 90);
    settings->endGroup();

    settings->beginGroup("AxisB");
        settings->setValue("BazaSearchSpeed", 30);
        settings->setValue("LowerBound", -90);
        settings->setValue("UpperBound", 90);
    settings->endGroup();

    settings->beginGroup("AxisC");
        settings->setValue("BazaSearchSpeed", 30);
        settings->setValue("LowerBound", -90);
        settings->setValue("UpperBound", 90);
    settings->endGroup();

    settings->beginGroup("AxisU");
        settings->setValue("BazaSearchSpeed", 30);
        settings->setValue("LowerBound", -90);
        settings->setValue("UpperBound", 90);
    settings->endGroup();

    settings->beginGroup("AxisV");
        settings->setValue("BazaSearchSpeed", 30);
        settings->setValue("LowerBound", -90);
        settings->setValue("UpperBound", 90);
    settings->endGroup();

    settings->beginGroup("AxisW");
        settings->setValue("BazaSearchSpeed", 30);
        settings->setValue("LowerBound", -90);
        settings->setValue("UpperBound", 90);
    settings->endGroup();

    settings->beginGroup("AxisXSensor");
        settings->setValue("Label", "Датчик оси X");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("AxisYSensor");
        settings->setValue("Label", "Датчик оси Y");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("AxisZSensor");
        settings->setValue("Label", "Датчик оси Z");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("AxisASensor");
        settings->setValue("Label", "Датчик оси A");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("AxisBSensor");
        settings->setValue("Label", "Датчик оси B");
        settings->setValue("ActiveState", true);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("AxisCSensor");
        settings->setValue("Label", "Датчик оси C");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("AxisUSensor");
        settings->setValue("Label", "Датчик оси U");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("AxisVSensor");
        settings->setValue("Label", "Датчик оси V");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("AxisWSensor");
        settings->setValue("Label", "Датчик оси W");
        settings->setValue("ActiveState", false);
        settings->setValue("Color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("ZeroSensor");
        settings->setValue("Label", "Датчик Ноля");
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
