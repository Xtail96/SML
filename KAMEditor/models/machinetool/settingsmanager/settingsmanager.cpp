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
        QMessageBox(QMessageBox::Warning, "Ошибка",
                    "Файл с настройками не найден. Используем настройки по умолчанию").exec();

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
    settings->beginGroup("MachineToolInformation");
        settings->setValue("VendorId", 0x10c4);
        settings->setValue("ProductId", 0xea61);
        settings->setValue("Name", "semil");
        settings->setValue("AxisCount", 5);
    settings->endGroup();

    settings->beginGroup("Times");
        settings->setValue("StartTime", QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
        settings->setValue("Filter", 3629);
        settings->setValue("Oil", 130);
        settings->setValue("OilSystem", 130);
        settings->setValue("TotalTime", 2.50631638860796);
        settings->setValue("WorkTime", 0.0866218629525974);
    settings->endGroup();

    settings->beginGroup("DefaultDirs");
        QString currentDir = QCoreApplication::applicationDirPath();
        settings->setValue("SaveDir", currentDir + "/files/programs");
        settings->setValue("OpenDir", currentDir);
        settings->setValue("ImportDir", currentDir);
        settings->setValue("ImportResDir", currentDir);
    settings->endGroup();

    settings->beginGroup("Mashin_Info");
        settings->setValue("MagneticSystem", 1);
        settings->setValue("Measure24V", 1);
        settings->setValue("SoftZeroSensor", 0);
        settings->setValue("SoftToolSensor", 1);
        settings->setValue("SurfCoeff", 1);
        settings->setValue("SurfDiscr", 0.001);
        settings->setValue("SplinePointsDivider", 4);
        settings->setValue("MaxSpeed", 250);
        settings->setValue("LastSpeed", 76);
        settings->setValue("AnoterSteps", 1);
        settings->setValue("MaxAngle", 12);
        settings->setValue("AltStepsX", 0.015625);
        settings->setValue("AltStepsY", 0.015625);
        settings->setValue("AltStepsZ", 0.00625);
        settings->setValue("AltStepsA", 0.0225);
        settings->setValue("AltStepsB", 0.0166666666666667);
        settings->setValue("InvertX", 0);
        settings->setValue("InvertY", 1);
        settings->setValue("InvertZ", 0);
        settings->setValue("InvertA", 0);
        settings->setValue("InvertB", 0);
        settings->setValue("StepX", 0);
        settings->setValue("StepY", 0);
        settings->setValue("StepZ", 0);
        settings->setValue("StepA", 0);
        settings->setValue("StepB", 0);
        settings->setValue("ControlLimitMode", 1);
    settings->endGroup();

    settings->beginGroup("Corrections");
        settings->setValue("CorXLin", 1);
        settings->setValue("CorYLin", 1);
        settings->setValue("CorZLin", 1);
        settings->setValue("CorALin", 1);
        settings->setValue("CorBLin", 1);
        settings->setValue("CorXDisp", 1);
        settings->setValue("CorYDisp", 1);
        settings->setValue("CorZDisp", 1);
        settings->setValue("CorADisp", 1);
        settings->setValue("CorBDisp", 1);
    settings->endGroup();

    settings->beginGroup("Table_Size");
        settings->setValue("SizeX", -1374);
        settings->setValue("SizeY", 1386);
        settings->setValue("SizeZ", -306);
        settings->setValue("SizeA", -185);
        settings->setValue("SizeB", 100);
        settings->setValue("SavedSizeZ", 100);
    settings->endGroup();

    settings->beginGroup("Home");
        settings->setValue("X", -15278);
        settings->setValue("Y", 9256);
        settings->setValue("Z", 1143);
        settings->setValue("A", -4166);
        settings->setValue("B", 0);
        settings->setValue("BazaX", -23810);
        settings->setValue("BazaY", 895);
        settings->setValue("BazaZ", -14658);
        settings->setValue("BazaA", 0);
        settings->setValue("BazaB", 0);
        settings->setValue("ParkX", 16390);
        settings->setValue("ParkY", 69372);
        settings->setValue("ParkZ", 2200);
        settings->setValue("ParkA", -4118);
        settings->setValue("ParkB", 0);
    settings->endGroup();

    settings->beginGroup("Drill_Mashin_Info");
        settings->setValue("DrillSpeed0", 1);
        settings->setValue("DrillSpeed1", 1);
        settings->setValue("DrillSpeed2", 1);
        settings->setValue("DrillSpeed3", 1);
        settings->setValue("DrillSpeed4", 1);
        settings->setValue("DrillSpeed5", 1);
    settings->endGroup();

    settings->beginGroup("Software_Info");
        settings->setValue("SafeZLowMode", 0);
        settings->setValue("SlowRenderMode", 1);
        settings->setValue("IgnoreBlocking", 0);
        settings->setValue("ZeroSensorHeight", 7.95);
        settings->setValue("UseElte", 1);
        settings->setValue("UseExtSensor", 0);
        settings->setValue("Prec", 1);
        settings->setValue("Norm", 1);
        settings->setValue("ParamA", 191.64);
        settings->setValue("ParamR", 73.14);
        settings->setValue("ParamD", 0.1);
        settings->setValue("Radius", 100);
        settings->setValue("ACorr", -92.745);
        settings->setValue("coeff", 235.97);
        settings->setValue("fromRotary", 137);
        settings->setValue("fromBazaToSensor", 362.21);
        settings->setValue("Dist4Sensor", 0);
        settings->setValue("JerkAngle", 45);
        settings->setValue("JerkDelay", 1);
        settings->setValue("critAngle", 2.5);
        settings->setValue("OnBazaSpeed", 10);
        settings->setValue("FromBazaSpeed", 5);
        settings->setValue("COMNum", 1);
        settings->setValue("BaseATypeA", 1);
        settings->setValue("MaxDelay", 50000);
        settings->setValue("Temperature", 37);
        settings->setValue("LaserDX", 241.656);
        settings->setValue("LaserDY", -144.625);
        settings->setValue("LaserDZ", -32.382);
        settings->setValue("LaserYP", 200);
        settings->setValue("LaserYM", 200);
        settings->setValue("LaserScanDelta", 0);
        settings->setValue("LaserRezCount", 1);
        settings->setValue("LaserScanSpeed", 10);
        settings->setValue("PolyPower", 12);
        settings->setValue("Depth", 6);
        settings->setValue("DepthCoeff", 0.375);
        settings->setValue("Spindle24k", 1);
        settings->setValue("AutoToolChanger", 1);
        settings->setValue("OilLength", 10);
        settings->setValue("OilPeriod", 8);
        settings->setValue("UseOilSystem", 0);
        settings->setValue("LastOilTime", "0:00:00");
        settings->setValue("safeZLevel", 1);
        settings->setValue("UseGearbox", 1);
        settings->setValue("VRef", 3.4);
        settings->setValue("useSplineApproximation", 0);
        settings->setValue("splineCoeff", 2);
        settings->setValue("paramB", 210.966);
        settings->setValue("autoCorr", 1);
        settings->setValue("MinSensorSearchSpeed", 5);
        settings->setValue("LaserCorrCount", 1);
        settings->setValue("tempCorr", 0);
        settings->setValue("controlPower", 0);
        settings->setValue("spindleDelay", 2);
        settings->setValue("useFanControl", 0);
        settings->setValue("ZeroSearchSpeed", 5);
        settings->setValue("LengthSearchSpeed", 5);
        settings->setValue("Precision", 0);
        settings->setValue("BazaSearchSpeed", 100);
        settings->setValue("DistFromZero", 0);
    settings->endGroup();

    settings->beginGroup("Tools");
    settings->endGroup();

    settings->beginGroup("ExternalMCSettings");
        settings->setValue("lookAheadLength", 3);
        settings->setValue("breakAngle", 30);
        settings->setValue("collinearTollerance", 0.01);
        settings->setValue("cornerTollerance", 0.07);
        settings->setValue("facetAngle", 3);
    settings->endGroup();

    settings->beginGroup("X Axis");
        settings->setValue("channel", 8);
        settings->setValue("jerk", 10000);
        settings->setValue("acceleration", 250);
        settings->setValue("speed", 250);
        settings->setValue("bazaSearchSpeed", 60);
    settings->endGroup();

    settings->beginGroup("Y Axis");
        settings->setValue("channel", 8);
        settings->setValue("jerk", 10000);
        settings->setValue("acceleration", 400);
        settings->setValue("speed", 250);
        settings->setValue("bazaSearchSpeed", 60);
    settings->endGroup();

    settings->beginGroup("Z Axis");
        settings->setValue("channel", 8);
        settings->setValue("jerk", 6000);
        settings->setValue("acceleration", 100);
        settings->setValue("speed", 50);
        settings->setValue("bazaSearchSpeed", 25);
    settings->endGroup();

    settings->beginGroup("A Axis");
        settings->setValue("channel", 8);
        settings->setValue("jerk", 10000);
        settings->setValue("acceleration", 100);
        settings->setValue("speed", 100);
        settings->setValue("bazaSearchSpeed", 10);
    settings->endGroup();

    settings->beginGroup("B Axis");
        settings->setValue("channel", 8);
        settings->setValue("jerk", 10000);
        settings->setValue("acceleration", 400);
        settings->setValue("speed", 200);
        settings->setValue("bazaSearchSpeed", 40);
    settings->endGroup();

    settings->beginGroup("Sensors");
        settings->setValue("count", 8);
        settings->setValue("0", "Датчик оси X");
        settings->setValue("1", "Датчик оси Y");
        settings->setValue("2", "Датчик оси Z");
        settings->setValue("3", "Датчик оси A");
        settings->setValue("4", "Датчик оси B");
        settings->setValue("5", "Датчик оси C");
        settings->setValue("6", "Датчик оси D");
        settings->setValue("7", "Датчик Ноля");
    settings->endGroup();

    settings->beginGroup("Датчик оси X");
        settings->setValue("portNumber", 1);
        settings->setValue("inputNumber", 0);
        settings->setValue("boardName", "portal");
        settings->setValue("activeState", false);
        settings->setValue("color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("Датчик оси Y");
        settings->setValue("portNumber", 1);
        settings->setValue("inputNumber", 1);
        settings->setValue("boardName", "portal");
        settings->setValue("activeState", false);
        settings->setValue("color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("Датчик оси Z");
        settings->setValue("portNumber", 1);
        settings->setValue("inputNumber", 2);
        settings->setValue("boardName", "portal");
        settings->setValue("activeState", false);
        settings->setValue("color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("Датчик оси A");
        settings->setValue("portNumber", 1);
        settings->setValue("inputNumber", 7);
        settings->setValue("boardName", "portal");
        settings->setValue("activeState", false);
        settings->setValue("color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("Датчик оси B");
        settings->setValue("portNumber", 1);
        settings->setValue("inputNumber", 4);
        settings->setValue("boardName", "portal");
        settings->setValue("activeState", true);
        settings->setValue("color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("Датчик оси C");
        settings->setValue("portNumber", 1);
        settings->setValue("inputNumber", 5);
        settings->setValue("boardName", "portal");
        settings->setValue("activeState", false);
        settings->setValue("color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("Датчик оси D");
        settings->setValue("portNumber", 1);
        settings->setValue("inputNumber", 6);
        settings->setValue("boardName", "portal");
        settings->setValue("activeState", false);
        settings->setValue("color", "#55bb55");
    settings->endGroup();

    settings->beginGroup("Датчик Ноля");
        settings->setValue("portNumber", 1);
        settings->setValue("inputNumber", 3);
        settings->setValue("boardName", "portal");
        settings->setValue("activeState", false);
        settings->setValue("color", "#b22222");
    settings->endGroup();

    settings->beginGroup("Devices");
        settings->setValue("count", 5);
        settings->setValue("0", "Фрезер");
        settings->setValue("1", "Фрезер 2");
        settings->setValue("2", "Шпиндель R");
        settings->setValue("3", "Муфта");
        settings->setValue("4", "САС");
    settings->endGroup();

    settings->beginGroup("Фрезер");
        settings->setValue("portNumber", 1);
        settings->setValue("outputNumber", 3);
        settings->setValue("boardName", "u1");
        settings->setValue("activeState", false);
        settings->setValue("needToDisplay", true);
        settings->setValue("mask", 0xfe);
    settings->endGroup();

    settings->beginGroup("Фрезер 2");
        settings->setValue("portNumber", 1);
        settings->setValue("outputNumber", 7);
        settings->setValue("boardName", "u1");
        settings->setValue("activeState", false);
        settings->setValue("needToDisplay", true);
        settings->setValue("mask", 0xfd);
    settings->endGroup();

    settings->beginGroup("Шпиндель R");
        settings->setValue("portNumber", 0);
        settings->setValue("outputNumber", 3);
        settings->setValue("invertOutputNumber", 2);
        settings->setValue("boardName", "u1");
        settings->setValue("activeState", false);
        settings->setValue("needToDisplay", true);
        settings->setValue("mask", 0xfb);
    settings->endGroup();

    settings->beginGroup("Муфта");
        settings->setValue("portNumber", 1);
        settings->setValue("outputNumber", 5);
        settings->setValue("boardName", "u1");
        settings->setValue("activeState", false);
        settings->setValue("needToDisplay", true);
        settings->setValue("mask", 0xef);
    settings->endGroup();

    settings->beginGroup("САС");
        settings->setValue("portNumber", 2);
        settings->setValue("outputNumber", 0);
        settings->setValue("boardName", "u1");
        settings->setValue("activeState", false);
        settings->setValue("needToDisplay", false);
        settings->setValue("mask", 0xf7);
    settings->endGroup();

    settings->beginGroup("Visualisation");
        settings->setValue("GridMaximalAccuracy", 0.01);
    settings->endGroup();

    settings->beginGroup("Options");
        settings->setValue("1", "Кабриоль");
        settings->setValue("2", "Датчик вылета инструмента");
        settings->setValue("3", "Станция автоматической смазки");
    settings->endGroup();

    // применяем изменения
    saveSettings();
}

QStringList SettingsManager::settingsKeys()
{
    return settings->allKeys();
}
