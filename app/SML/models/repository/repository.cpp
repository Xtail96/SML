#include "repository.h"

Repository::Repository(QObject *parent) :
    QObject(parent),
    m_settingsManager(new SettingsManager()),
    m_pointsManager(new PointsManager(this)),
    m_gcodesFilesManager(new GCodesFilesManager(this)),
    m_u1Connection(new Connection(this)),
    m_u2Connection(new Connection(this)),
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
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации", QString("Ошибка инициализации порта сервера") + QString(e.what())).exec();
    }
}

void Repository::loadSensorsSettings()
{
    try
    {
        unsigned int sensorsCount = QVariant(m_settingsManager->get("Main", "SensorsCount")).toUInt();

        std::vector<QString> sensorsCodes;
        for(unsigned int i = 0; i < sensorsCount; i++)
        {
            QString sensorString = QString("Sensor") + QString::number(i);
            sensorsCodes.push_back(sensorString);
        }

        for(auto code : sensorsCodes)
        {
            QString name  = QVariant(m_settingsManager->get(code, "Name")).toString();
            QString label = QVariant(m_settingsManager->get(code, "Label")).toString();
            size_t portNumber = QVariant(m_settingsManager->get(code, "PortNumber")).toUInt();
            size_t inputNumber = QVariant(m_settingsManager->get(code, "InputNumber")).toUInt();
            QString boardName = QVariant(m_settingsManager->get(code, "BoardName")).toString();
            bool activeState = QVariant(m_settingsManager->get(code, "ActiveState")).toBool();
            QColor color = QColor(QVariant(m_settingsManager->get(code, "Color")).toString());

            Sensor* sensor = new Sensor(name,
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
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки менеджера датчиков", e.what()).exec();
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
            QString name = QString("Spindel") + QString::number(i);
            QString label = QVariant(m_settingsManager->get(name, "Label")).toString();
            QString index = QVariant(m_settingsManager->get(name, "Index")).toString();
            bool activeState = QVariant(m_settingsManager->get(name, "ActiveState")).toBool();
            int mask = QVariant(m_settingsManager->get(name, "Mask")).toUInt();
            size_t upperBound = QVariant(m_settingsManager->get(name, "UpperBound")).toULongLong();
            size_t lowerBound = QVariant(m_settingsManager->get(name, "LowerBound")).toULongLong();


            Spindel* spindel = new Spindel(name,
                                           label,
                                           index,
                                           activeState,
                                           mask,
                                           lowerBound,
                                           upperBound,
                                           this);
            m_spindels.push_back(QSharedPointer<Spindel> (spindel));
        }

        for(unsigned int i = 0; i < supportDevicesCount; i++)
        {
            QString name = QString("SupportDevice") + QString::number(i);
            QString label = QVariant(m_settingsManager->get(name, "Label")).toString();
            QString index = QVariant(m_settingsManager->get(name, "Index")).toString();
            bool activeState = QVariant(m_settingsManager->get(name, "ActiveState")).toBool();
            int mask = QVariant(m_settingsManager->get(name, "Mask")).toUInt();


            SupportDevice* device = new SupportDevice(name,
                                                      label,
                                                      index,
                                                      activeState,
                                                      mask,
                                                      this);
            m_supportDevices.push_back(QSharedPointer<SupportDevice> (device));
        }
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки менеджера устройств", e.what()).exec();
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
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации", QString("Ошибка инициализации менеджера осей!") + QString(e.what())).exec();
    }
}

void Repository::setU1Connected(bool connected)
{
    m_u1Connection->setConnected(connected);
}

void Repository::setU1Sensors(QList<QVariant> sensors)
{
    try
    {
        byte_array currentSensorsState;
        for(auto port : sensors)
        {
            currentSensorsState.push_back(port.toUInt());
        }

        m_sensorsBuffer->updateBuffer(currentSensorsState);
        for(auto sensor : m_sensors)
        {
            bool isVoltage = m_sensorsBuffer->getInputState(sensor->getBoardName(),
                                                            sensor->getPortNumber(),
                                                            sensor->getInputNumber());
            sensor->update(isVoltage);
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
            currentDevicesState.push_back(device.toUInt());
        }

        for(size_t i = 0; i < currentDevicesState.size(); i++)
        {
            Device& device = findDevice(i);
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

Device &Repository::findDevice(size_t index)
{
    for(auto device : m_spindels)
    {
        if(device->getIndex().toUInt() == index)
        {
            return *device;
        }
    }

    for(auto device : m_supportDevices)
    {
        if(device->getIndex().toUInt() == index)
        {
            return *device;
        }
    }

    QString message =
            QStringLiteral("device not found ") +
            QString::number(index);

    throw SynchronizeStateException(message);
}

QStringList Repository::getAllDevicesNames()
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

QList<QStringList> Repository::getAllDevicesSettings()
{
    QList<QStringList> devicesSettings;
    for(auto device : m_spindels)
    {
        QStringList deviceSettings =
        {
            QString::number(device->getActiveState()),
            QString::number(device->getMask(), 2)
        };
        devicesSettings.push_back(deviceSettings);
    }

    for(auto device : m_supportDevices)
    {
        QStringList deviceSettings =
        {
            QString::number(device->getActiveState()),
            QString::number(device->getMask(), 2)
        };
        devicesSettings.push_back(deviceSettings);
    }
    return devicesSettings;
}

QStringList Repository::getOnScreenDevicesNames()
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

QList<bool> Repository::getOnScreenDevicesStates()
{
    QList<bool> devicesStates;
    for(auto device : m_spindels)
    {
        devicesStates.push_back(device->isEnable());
    }
    for(auto device : m_supportDevices)
    {
        devicesStates.push_back(device->isEnable());
    }
    return devicesStates;
}

Sensor* Repository::findSensor(QString name)
{
    for(auto sensor : m_sensors)
    {
        if(sensor->getName() == name)
        {
            return sensor.data();
            break;
        }
    }

    throw std::invalid_argument("sensor with name " + name.toStdString() + " is not exists");
}

QStringList Repository::getSensorNames()
{
    QStringList names;
    for(auto sensor : m_sensors)
    {
        names.push_back(sensor->getName());
    }
    return names;
}

QMap<QString, QString> Repository::getSensorSettings(QString name)
{
    QMap<QString, QString> sensorsSettingsMap;
    try
    {
        QString settingsString = findSensor(name)->getSettings();
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
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Get Sensor Settings Error", e.what()).exec();
    }
    return sensorsSettingsMap;
}


QStringList Repository::getSensorsSettings()
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

QString Repository::getGCodesProgram()
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

QStringList Repository::getOptionsNames()
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

QStringList Repository::getPoint(unsigned int number)
{
    return m_pointsManager->point(number);
}

void Repository::deletePoint(unsigned int number)
{
    try
    {
        std::shared_ptr<Point> p = m_pointsManager->operator [](number);
        m_pointsManager->deletePoint(p);
    }
    catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

void Repository::updatePoint(QStringList coordinates, unsigned int number)
{
    m_pointsManager->updatePoint(coordinates, number);
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

QStringList Repository::getCurrentConnections()
{
    return QStringList();
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

Spindel *Repository::findSpindel(QString index)
{
    for(auto spindel : m_spindels)
    {
        if(spindel->getIndex() == index)
        {
            return spindel.data();
        }
    }

    throw std::invalid_argument("spindel with index " + index.toStdString() + " is not exists");
}

void Repository::setSpindelState(QString index, bool enable, size_t rotations)
{
    try
    {
        Spindel* spindel = findSpindel(index);
        spindel->setCurrentState(enable, rotations);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

void Repository::exportSettings()
{
    QString path = QFileDialog::getSaveFileName(0, "Выберите путь до файла", "", "*.ini");
    m_settingsManager->exportSettings(path);
}

void Repository::importSettings()
{
    QString path = QFileDialog::getOpenFileName(0, "Выберите файл с настройками", "", "*.ini");
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
