#include "repository.h"

Repository::Repository(QObject *parent) :
    QObject(parent),
    m_settingsManager(new SettingsManager()),
    m_pointsManager(new PointsManager(this)),
    m_gcodesFilesManager(new GCodesFileManager(this)),
    m_u1Adapter(new Adapter(this)),
    m_u2Adapter(new Adapter(this)),
    m_sensorsBuffer(new SensorsBuffer(16, this))
{
    loadSettigs();
}

void Repository::loadSettigs()
{
    loadServerSettings();
    loadSensorsSettings();
    loadDevicesSettings();
    loadAxisesSettings();
}

void Repository::loadServerSettings()
{
    try
    {
        m_port = m_settingsManager->get("ServerSettings", "ServerPort").toUInt();
    }
    catch(InvalidConfigurationException e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации", QString("Ошибка инициализации порта сервера") + QString(e.message())).exec();
        qDebug() << QStringLiteral("Repository::loadServerSettings:") << e.message();
        qApp->exit(0);
    }
}

void Repository::loadSensorsSettings()
{
    try
    {
        unsigned int sensorsCount = QVariant(m_settingsManager->get("Main", "SensorsCount")).toUInt();

        QList<QString> sensorsSettingCodes;
        for(unsigned int i = 0; i < sensorsCount; i++)
        {
            QString sensorSettingCode = QString("Sensor") + QString::number(i);
            sensorsSettingCodes.push_back(sensorSettingCode);
        }

        for(auto settingCode : sensorsSettingCodes)
        {
            QString uid  = QVariant(m_settingsManager->get(settingCode, "Uid")).toString();
            QString label = QVariant(m_settingsManager->get(settingCode, "Label")).toString();
            size_t portNumber = QVariant(m_settingsManager->get(settingCode, "PortNumber")).toUInt();
            size_t inputNumber = QVariant(m_settingsManager->get(settingCode, "InputNumber")).toUInt();
            QString boardName = QVariant(m_settingsManager->get(settingCode, "BoardName")).toString();
            bool activeState = QVariant(m_settingsManager->get(settingCode, "ActiveState")).toBool();
            QColor color = QColor(QVariant(m_settingsManager->get(settingCode, "Color")).toString());

            Sensor* sensor = new Sensor(uid,
                                        label,
                                        portNumber,
                                        inputNumber,
                                        boardName,
                                        activeState,
                                        color,
                                        this);
            m_sensors.push_back(QSharedPointer<Sensor>(sensor));
        }

        m_sensorsBufferSize = QVariant(m_settingsManager->get("Main", "SensorsBufferSize")).toUInt();
        m_sensorsBuffer->resetBuffer(m_sensorsBufferSize);
    }
    catch(InvalidConfigurationException e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настроек датчиков", e.message()).exec();
        qDebug() << QStringLiteral("Repository::loadSensorsSettings:") << e.message();
        qApp->exit(0);
    }
}

void Repository::loadDevicesSettings()
{
    try
    {
        unsigned int spindelsCount = QVariant(m_settingsManager->get("Main", "SpindelsCount")).toUInt();
        unsigned int supportDevicesCount = QVariant(m_settingsManager->get("Main", "SupportDevicesCount")).toUInt();

        for(unsigned int i = 0; i < spindelsCount; i++)
        {
            QString settingName = QString("Spindel") + QString::number(i);
            QString uid = QVariant(m_settingsManager->get(settingName, "Uid")).toString();
            QString label = QVariant(m_settingsManager->get(settingName, "Label")).toString();
            bool activeState = QVariant(m_settingsManager->get(settingName, "ActiveState")).toBool();
            size_t upperBound = QVariant(m_settingsManager->get(settingName, "UpperBound")).toULongLong();
            size_t lowerBound = QVariant(m_settingsManager->get(settingName, "LowerBound")).toULongLong();


            Spindel* spindel = new Spindel(settingName,
                                           uid,
                                           label,
                                           activeState,
                                           lowerBound,
                                           upperBound,
                                           this);
            m_spindels.push_back(QSharedPointer<Spindel> (spindel));
        }

        for(unsigned int i = 0; i < supportDevicesCount; i++)
        {
            QString settingName = QString("SupportDevice") + QString::number(i);
            QString uid = QVariant(m_settingsManager->get(settingName, "Uid")).toString();
            QString label = QVariant(m_settingsManager->get(settingName, "Label")).toString();
            bool activeState = QVariant(m_settingsManager->get(settingName, "ActiveState")).toBool();

            SupportDevice* device = new SupportDevice(settingName,
                                                      uid,
                                                      label,
                                                      activeState,
                                                      this);
            m_supportDevices.push_back(QSharedPointer<SupportDevice> (device));
        }
    }
    catch(InvalidConfigurationException e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настроек устройств", e.message()).exec();
        qDebug() << QStringLiteral("Repository::loadDevicesSettings:") << e.message();
        qApp->exit(0);
    }
}

void Repository::loadAxisesSettings()
{
    try
    {
         size_t axisesCount = m_settingsManager->get("Main", "AxisesCount").toUInt();
         for(size_t i = 0; i < axisesCount; i++)
         {
             QString name = SML_AXISES_NAMES.getNameByKey(i);

             QString fullAxisName = QString("Axis") + name;

             double length = m_settingsManager->get("TableSize", QString("Size" + name)).toDouble();
             double step = m_settingsManager->get(fullAxisName, "Step").toDouble();
             bool invertDirection = m_settingsManager->get(fullAxisName, "Invert").toBool();
             double bazaSearchSpeed = m_settingsManager->get(fullAxisName, "BazaSearchSpeed").toDouble();

             QSharedPointer<Axis> axis = QSharedPointer<Axis>(new Axis(name, length, step, invertDirection, bazaSearchSpeed));
             m_axises.push_back(axis);
         }
         m_zeroCoordinates = Point(m_axises.size());
         m_parkCoordinates = Point(m_axises.size());
    }
    catch(InvalidConfigurationException e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настроек осей", QString(e.message())).exec();
        qDebug() << QStringLiteral("Repository::loadAxisesSettings:") << e.message();
        qApp->exit(0);
    }
}

void Repository::setU1ConnectState(bool connected)
{
    m_u1Adapter->setConnected(connected);
}

void Repository::setU1WorkflowState(int state)
{
    m_u1Adapter->setWorkflowState(state);
}

void Repository::setU1Sensors(QList<QVariant> sensors)
{
    try
    {
        byte_array currentSensorsState;
        for(auto port : sensors)
        {
            currentSensorsState.push_back(static_cast<byte>(port.toUInt()));
        }

        m_sensorsBuffer->updateBuffer(currentSensorsState);
        for(auto sensor : m_sensors)
        {
            bool isVoltage = m_sensorsBuffer->getInputState(sensor->getBoardName(),
                                                            sensor->getPortNumber(),
                                                            sensor->getInputNumber());
            sensor->updateInputState(isVoltage);
        }
    }
    catch(SynchronizeStateException e)
    {
        qDebug() << QStringLiteral("Repository::setU1Sensors:") << e.message();
        throw;
    }
}

void Repository::setU1Devices(QList<QVariant> devices)
{
    try
    {
        byte_array currentDevicesState;
        for(auto device : devices)
        {
            currentDevicesState.push_back(static_cast<byte>(device.toUInt()));
        }

        for(int i = 0; i < currentDevicesState.size(); i++)
        {
            Device& device = getDevice(static_cast<size_t>(i));
            if(currentDevicesState[i] == 0x01)
            {
                device.setCurrentState(device.getActiveState(), QMap<QString, QString>());
            }
            else
            {
                if(currentDevicesState[i] == 0x00)
                {
                    device.setCurrentState(!device.getActiveState(), QMap<QString, QString>());
                }
            }
        }
    }
    catch (SynchronizeStateException e)
    {
        qDebug() << QStringLiteral("Repository::setU1Devices:") << e.message();
        throw;
    }
}

Device &Repository::getDevice(size_t index)
{
    for(auto device : m_spindels)
    {
        if(device->getUid().toUInt() == index)
        {
            return *device;
        }
    }

    for(auto device : m_supportDevices)
    {
        if(device->getUid().toUInt() == index)
        {
            return *device;
        }
    }

    QString message =
            QStringLiteral("device not found ") +
            QString::number(index);

    throw InvalidArgumentException(message);
}

QStringList Repository::getAllDevicesLabels()
{
    QStringList names;
    for(auto device : m_spindels)
    {
        names.push_back(device->getLabel());
    }
    for(auto device : m_supportDevices)
    {
        names.push_back(device->getLabel());
    }
    return names;
}

QStringList Repository::getAllDevicesSettings()
{
    QStringList devicesSettings;
    for(auto device : m_spindels)
    {
        devicesSettings.push_back(device->getSettings());
    }

    for(auto device : m_supportDevices)
    {
        devicesSettings.push_back(device->getSettings());
    }
    return devicesSettings;
}

QStringList Repository::getAllOnScreenDevicesLabels()
{
    QStringList names;
    for(auto device : m_spindels)
    {
        names.push_back(device->getLabel());
    }
    for(auto device : m_supportDevices)
    {
        names.push_back(device->getLabel());
    }
    return names;
}

QMap<QString, bool> Repository::getAllOnScreenDevicesStates()
{
    QMap<QString, bool> onScreenDevices;
    for(auto device : m_spindels)
    {
        onScreenDevices.insert(device->getUid(), device->isEnable());
    }
    for(auto device : m_supportDevices)
    {
        onScreenDevices.insert(device->getUid(), device->isEnable());
    }
    return onScreenDevices;
}

Sensor &Repository::getSensor(QString uid)
{
    for(auto sensor : m_sensors)
    {
        if(sensor->getUid() == uid)
        {
            return *(sensor.data());
        }
    }

    QString message =
            QStringLiteral("sensor with uid = ") +
            uid +
            QStringLiteral(" is not exists");
    throw InvalidArgumentException(message);
}

QStringList Repository::getAllSensorsUids()
{
    QStringList uids;
    for(auto sensor : m_sensors)
    {
        uids.push_back(sensor->getUid());
    }
    return uids;
}

QMap<QString, QString> Repository::getSensorSettings(QString uid)
{
    QMap<QString, QString> sensorsSettingsMap;
    try
    {
        QString settingsString = getSensor(uid).getSettings();
        QStringList settingsList = settingsString.split(";");

        for(auto setting : settingsList)
        {
            QStringList item = setting.split(":");
            if(item.size() == 2)
            {
                sensorsSettingsMap.insert(item.at(0), item.at(1));
            }
        }
    }
    catch(InvalidArgumentException e)
    {
        QMessageBox(QMessageBox::Warning, "Get Sensor Settings Error", e.message()).exec();
    }
    return sensorsSettingsMap;
}


QStringList Repository::getAllSensorsSettings()
{
    QStringList settings;
    for(auto sensor : m_sensors)
    {
        settings.push_back(sensor->getSettings());
    }
    return settings;
}

void Repository::setGCodes(const QString &data)
{
    m_gcodesFilesManager->setFileContent(data);
}

QStringList Repository::getGCodesProgram()
{
    return m_gcodesFilesManager->getContent();
}

QList<Point> Repository::getMachineToolCoordinates()
{
    QList<Point> machineToolCoordinates;
    machineToolCoordinates.push_back(getCurrentCoordinatesFromZero());
    machineToolCoordinates.push_back(getCurrentCoordinatesFromBase());
    machineToolCoordinates.push_back(m_parkCoordinates);
    return machineToolCoordinates;
}

Point Repository::getCurrentCoordinatesFromBase()
{
    QList<double> axisesCoordinates;
    for(auto axis : m_axises)
    {
        axisesCoordinates.push_back(axis->currentPosition());
    }
    return Point(axisesCoordinates.toVector().toStdVector());
}

Point Repository::getCurrentCoordinatesFromZero()
{
    Point currentFromZero(m_axises.size());
    Point p = getCurrentCoordinatesFromBase();

    if(p.size() == m_zeroCoordinates.size())
    {
        currentFromZero = p.operator -=(m_zeroCoordinates);
    }

    return currentFromZero;
}

QStringList Repository::getAxisesNames()
{
    QStringList names;
    for(auto axis : m_axises)
    {
        names.push_back(axis->name());
    }
    return names;
}

QStringList Repository::getAxisesSettings()
{
    QStringList axisesSettings;

    for(auto axis : m_axises)
    {
        axisesSettings.push_back(axis->axisSettings());
    }
    return axisesSettings;
}

QStringList Repository::getOptionsLabels()
{
    /// todo: переписать метод через модель
    QStringList optionsNames =
    {
        "Кабриоль",
        "Датчик вылета инструмента",
        "Станция автоматической смазки"
    };
    return optionsNames;
}

void Repository::addPoint(QStringList coordinates)
{
    Point* p = PointsManager::makePoint(coordinates);
    m_pointsManager->addPoint(p);
}

QList<QStringList> Repository::getPoints()
{
    return m_pointsManager->points();
}

QStringList Repository::getPoint(unsigned int index)
{
    return m_pointsManager->point(index);
}

void Repository::deletePoint(unsigned int index)
{
    try
    {
        QSharedPointer<Point> p = m_pointsManager->operator [](index);
        m_pointsManager->deletePoint(p);
    }
    catch(OutOfRangeException e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.message()).exec();
    }
}

void Repository::updatePoint(QStringList coordinates, unsigned int index)
{
    m_pointsManager->updatePoint(coordinates, index);
}

QString Repository::getFilePath(QString type)
{
    QString path = "";
    if(type == "gcodes")
    {
        path = m_gcodesFilesManager->getFilePath();
    }
    else
    {
        if(type == "sml")
        {
            path = "sml file path";
        }
    }
    return path;
}

void Repository::setSoftLimitsMode(bool enable)
{
    for(auto axis : m_axises)
    {
        axis->setSoftLimitsEnable(enable);
    }
}

QString Repository::getServerPort()
{
    return QString::number(m_port);
}

QString Repository::getSensorsBufferSize()
{
    return QString::number(m_sensorsBufferSize);
}

QString Repository::getDevicesBufferSize()
{
    return QString::number(m_spindels.size() + m_supportDevices.size());
}

QList<Spindel *> Repository::getSpindels()
{
    QList<Spindel *> spindels;
    for(auto spindel : m_spindels)
    {
        spindels.push_back(spindel.data());
    }
    return spindels;
}

Spindel &Repository::getSpindel(QString uid)
{
    for(auto spindel : m_spindels)
    {
        if(spindel->getUid() == uid)
        {
            return *(spindel.data());
        }
    }

    QString message =
            QStringLiteral("spindel with index ") +
            uid +
            QStringLiteral(" is not exists");
    throw InvalidArgumentException(message);
}

void Repository::setSpindelState(QString uid, bool enable, size_t rotations)
{
    try
    {
        Spindel& spindel = getSpindel(uid);
        spindel.setCurrentState(enable, rotations);
    }
    catch(InvalidArgumentException e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.message()).exec();
    }
}

void Repository::exportSettings()
{
    QString path = QFileDialog::getSaveFileName(nullptr, "Выберите путь до файла", "", "*.ini");
    m_settingsManager->exportSettings(path);
}

void Repository::importSettings()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Выберите файл с настройками", "", "*.ini");
    m_settingsManager->importSettings(path);
}

void Repository::openGCodesFile()
{
    m_gcodesFilesManager->openGCodesFile();
}

void Repository::saveGCodesFile(const QString data)
{
    m_gcodesFilesManager->setFileContent(data);
    m_gcodesFilesManager->saveGCodesFile();
}

void Repository::saveGCodesFileAs(const QString data)
{
    m_gcodesFilesManager->setFileContent(data);
    m_gcodesFilesManager->saveGCodesFileAs();
}

void Repository::newGCodesFile()
{
    m_gcodesFilesManager->newGCodesFile();
}

void Repository::addGCodesFile(const QString data)
{
    saveGCodesFile(data);
    m_gcodesFilesManager->addGCodesFile();
}

double Repository::getVelocity() const
{
    return m_velocity;
}

void Repository::setVelocity(double velocity)
{
    m_velocity = velocity;
}
