#include "repository.h"

Repository::Repository(QObject *parent) :
    QObject(parent),
    m_settingsManager(),
    m_gcodesFilesManager(this),
    m_port(1234),
    m_sensorsBufferSize(2),
    m_devicesBufferSize(1),
    m_u1Adapter(Adapter::U1, this),
    m_u2Adapter(Adapter::U2, this),
    m_sensors(QList< QSharedPointer<Sensor> >()),
    m_sensorsBuffer(16),
    m_spindels(QList< QSharedPointer<Spindel> >()),
    m_supportDevices(QList< QSharedPointer<SupportDevice> >()),
    m_axes(QList< QSharedPointer<Axis> >()),
    m_points(QList<Point>()),
    m_zeroCoordinates(Point()),
    m_parkCoordinates(Point()),
    m_velocity(0),
    m_movementStep(0)
{
    this->loadSettigs();
}

void Repository::setU1ConnectState(bool connected)
{
    try
    {
        m_u1Adapter.setConnectionState(connected);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::setU1ConnectState: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::setU1WorkflowState(unsigned int state)
{
    try
    {
        m_u1Adapter.setWorkflowState(state);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::setU1WorkflowState: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::setU2ConnectState(bool connected)
{
    try
    {
        m_u2Adapter.setConnectionState(connected);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::setU2ConnectState: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::setU2WorkflowState(unsigned int state)
{
    try
    {
        m_u2Adapter.setWorkflowState(state);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::setU2WorkflowState: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
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

        m_sensorsBuffer.updateBuffer(currentSensorsState);
        for(auto sensor : m_sensors)
        {
            bool isVoltage = m_sensorsBuffer.getInputState(sensor->boardName(),
                                                            sensor->portNumber(),
                                                            sensor->inputNumber());
            //sensor->setInputState(isVoltage);
        }
    }
    catch(SynchronizeStateException e)
    {
        qDebug() << QStringLiteral("Repository::setU1Sensors:") << e.message();
        emit this->errorOccurred(ERROR_CODE::SYNC_STATE_ERROR);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::setU1Sensors: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
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
            Device& device = this->getDevice(static_cast<size_t>(i));
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
        emit this->errorOccurred(ERROR_CODE::SYNC_STATE_ERROR);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::setU1Devices: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

QStringList Repository::getAllDevicesLabels()
{
    QStringList names = {};

    try
    {
        for(auto device : m_spindels)
        {
            names.push_back(device->getLabel());
        }
        for(auto device : m_supportDevices)
        {
            names.push_back(device->getLabel());
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getAllDevicesLabels: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return names;
}

QStringList Repository::getAllSpindelsSettings()
{
    QStringList spindelsSettings = {};

    try
    {
        for(auto spindel : m_spindels)
        {
            spindelsSettings.push_back(spindel->getSettings());
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getAllSpindelsSettings: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return spindelsSettings;
}

QStringList Repository::getAllSupportDeviceSettings()
{
    QStringList supportDevicesSettings = {};

    try
    {
        for(auto supportDevice : m_supportDevices)
        {
            supportDevicesSettings.push_back(supportDevice->getSettings());
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::supportDevicesSettings: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return supportDevicesSettings;
}

QStringList Repository::getAllOnScreenDevicesLabels()
{
    QStringList names = {};

    try
    {
        for(auto device : m_spindels)
        {
            names.push_back(device->getLabel());
        }
        for(auto device : m_supportDevices)
        {
            names.push_back(device->getLabel());
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getAllOnScreenDevicesLabels: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return names;
}

QMap<QString, bool> Repository::getAllOnScreenDevicesStates()
{
    QMap<QString, bool> onScreenDevices = {};

    try
    {
        for(auto device : m_spindels)
        {
            onScreenDevices.insert(device->getUid(), device->isEnable());
        }
        for(auto device : m_supportDevices)
        {
            onScreenDevices.insert(device->getUid(), device->isEnable());
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getAllOnScreenDevicesStates: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return onScreenDevices;
}

QStringList Repository::getAllSensorsUids()
{
    QStringList uids = {};

    try
    {
        for(auto sensor : m_sensors)
        {
            uids.push_back(sensor->uid());
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getAllSensorsUids: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return uids;
}

QMap<QString, QString> Repository::getSensorSettings(QString uid)
{
    QMap<QString, QString> sensorsSettingsMap = {};

    try
    {
        QString settingsString = this->getSensor(uid).settings();
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
        qDebug() << QStringLiteral("Repository::getSensorSettings:") << e.message();
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getSensorSettings: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return sensorsSettingsMap;
}

QStringList Repository::getAllSensorsSettings()
{
    QStringList settings = {};

    try
    {
        for(auto sensor : m_sensors)
        {
            settings.push_back(sensor->settings());
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getAllSensorsSettings: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return settings;
}

void Repository::setGCodes(const QString &data)
{
    try
    {
        m_gcodesFilesManager.setFileContent(data);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::setGCodes: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

QStringList Repository::getGCodesProgram()
{
    QStringList result = {};

    try
    {
        result = m_gcodesFilesManager.getContent();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getGCodesProgram: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return result;
}

QList<Point> Repository::getCurrentPositionDetaiedInfo()
{
    QList<Point> currentCoordinates = {};

    try
    {
        currentCoordinates.push_back(this->getCurrentPositionFromZero());
        currentCoordinates.push_back(this->getCurrentPositionFromBase());
        currentCoordinates.push_back(m_parkCoordinates);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getMachineToolCoordinates: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return currentCoordinates;
}

void Repository::setCurrentPosition(Point absCoordinates)
{
    try
    {
        for(auto axis : m_axes)
        {
            auto absValue = absCoordinates.get(axis->decoratedId());
            axis->setCurrentPosition(absValue);
        }
    }
    catch (...)
    {
        qDebug() << "Repository::setCurrentPosition: unknown error";
        QMessageBox(QMessageBox::Critical, "Error", "Can not set current position").exec();
    }
}

void Repository::setCurrentPosition(QMap<QString, double> absCoordinates)
{
    for(auto axis : m_axes)
    {
        QString currentAxisName = axis->decoratedId();
        if(absCoordinates.contains(currentAxisName))
        {
            double axisPosition = absCoordinates[currentAxisName];
            axis->setCurrentPosition(axisPosition);
        }
    }
}

QStringList Repository::getAxisesNames()
{
    QStringList names = {};

    try
    {
        for(auto axis : m_axes)
        {
            names.push_back(axis->decoratedId());
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getAxisesNames: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return names;
}

double Repository::getAxisPosition(const QString axisName)
{
    if(!this->getAxisesNames().contains(axisName))
    {
        QString message =
                QStringLiteral("axis with name = ") +
                axisName +
                QStringLiteral(" does not exists");
        qDebug() << QStringLiteral("Repository::getCurrentAxisPosition:") << message;
        throw InvalidArgumentException(message);
    }

    try
    {
        Point positionFromBase = this->getCurrentPositionFromBase();
        return positionFromBase.get(axisName);
    }
    catch (std::invalid_argument e) {
        qDebug() << QStringLiteral("Repository::getCurrentAxisPosition:") << e.what();
        throw InvalidArgumentException(e.what());
    }
}

QStringList Repository::getAxesSettings()
{
    QStringList axesSettings = {};

    try
    {
        for(auto axis : m_axes)
        {
            axesSettings.push_back(axis->toString());
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getAxisesSettings: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return axesSettings;
}

QStringList Repository::getOptionsLabels()
{
    /// todo: переписать метод
    QStringList optionsNames =
    {
        "Кабриоль",
        "ДВИ",
        "САС"
    };
    return optionsNames;
}

double Repository::getMovementStep() const
{
    return m_movementStep;
}

void Repository::setMovementStep(double movementStep)
{
    m_movementStep = movementStep;
}

Point Repository::getZeroCoordinates() const
{
    return m_zeroCoordinates;
}

void Repository::setZeroCoordinates(const Point &zeroCoordinates)
{
    m_zeroCoordinates = zeroCoordinates;
}

Point Repository::getParkCoordinates() const
{
    return m_parkCoordinates;
}

void Repository::setParkCoordinates(const Point &parkCoordinates)
{
    m_parkCoordinates = parkCoordinates;
}

void Repository::addPoint(QMap<QString, double> coords)
{
    try
    {
        Point p;
        for(auto axisUid : coords.keys())
        {
            p.insertAxis(axisUid, coords[axisUid]);
        }
        m_points.append(p);

        emit this->pointsUpdated();
    }
    catch(...)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Не удалось добавить точку").exec();
        qDebug() << QStringLiteral("Repository::addPoint: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

QList<Point> Repository::getPoints()
{
    return m_points;
}

Point Repository::getPoint(unsigned int index)
{
    if(m_points.size() <= int(index)) throw OutOfRangeException("Point with index " + QString::number(index) + " doest not exists");
    return m_points[int(index)];
}

void Repository::deletePoint(unsigned int index)
{
    if(m_points.size() <= int(index)) throw OutOfRangeException("Point with index " + QString::number(index) + " doest not exists");
    m_points.removeAt(int(index));

    emit this->pointsUpdated();
}

void Repository::updatePoint(QMap<QString, double> coordinates, unsigned int index)
{
    if(m_points.size() <= int(index)) throw OutOfRangeException("Point with index " + QString::number(index) + " doest not exists");
    m_points.replace(int(index), Point(coordinates));

    emit this->pointsUpdated();
}

Point Repository::createEmptyPoint()
{
    Point p;
    for(auto axis : m_axes)
    {
        p.insertAxis(axis->decoratedId(), 0.0);
    }
    return p;
}

QString Repository::getFilePath(QString type)
{
    QString path = "";

    try
    {
        if(type == "gcodes")
        {
            path = m_gcodesFilesManager.getFilePath();
        }
        else
        {
            if(type == "sml")
            {
                path = "sml file path";
            }
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getFilePath: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return path;
}

void Repository::setSoftLimitsMode(bool enable)
{
    try
    {
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::setSoftLimitsMode: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

QString Repository::getServerPort()
{
    QString result = QString();

    try
    {
        result = QString::number(m_port);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getServerPort: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return result;
}

QString Repository::getSensorsBufferSize()
{
    QString result = QString();

    try
    {
        result = QString::number(m_sensorsBufferSize);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getSensorsBufferSize: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return result;
}

QString Repository::getDevicesBufferSize()
{
    QString result = QString();

    try
    {
        result = QString::number(m_spindels.size() + m_supportDevices.size());
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getDevicesBufferSize: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return result;
}

QList<Spindel *> Repository::getSpindels()
{
    QList<Spindel *> spindels = {};

    try
    {
        for(auto spindel : m_spindels)
        {
            spindels.push_back(spindel.data());
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getSpindels: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return spindels;
}

void Repository::setSpindelState(QString uid, bool enable, size_t rotations)
{
    try
    {
        Spindel& spindel = this->getSpindel(uid);
        spindel.setCurrentState(enable, rotations);
    }
    catch(InvalidArgumentException e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.message()).exec();
        qDebug() << QStringLiteral("Repository::setSpindelState") << e.message();

        emit errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::exportSettings()
{
    try
    {
        QString path = QFileDialog::getSaveFileName(nullptr, "Выберите путь до файла", "", "*.ini");
        m_settingsManager.exportSettings(path);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::exportSettings: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::importSettings()
{
    try
    {
        QString path = QFileDialog::getOpenFileName(nullptr, "Выберите файл с настройками", "", "*.ini");
        m_settingsManager.importSettings(path);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::importSettings: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::openGCodesFile()
{
    try
    {
        m_gcodesFilesManager.openGCodesFile();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::openGCodesFile: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::saveGCodesFile(const QString data)
{
    try
    {
        m_gcodesFilesManager.setFileContent(data);
        m_gcodesFilesManager.saveGCodesFile();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::saveGCodesFile: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::saveGCodesFileAs(const QString data)
{
    try
    {
        m_gcodesFilesManager.setFileContent(data);
        m_gcodesFilesManager.saveGCodesFileAs();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::saveGCodesFileAs: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::newGCodesFile()
{
    try
    {
        m_gcodesFilesManager.newGCodesFile();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::newGCodesFile: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

void Repository::addGCodesFile(const QString data)
{
    try
    {
        this->saveGCodesFile(data);
        m_gcodesFilesManager.addGCodesFile();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::addGCodesFile: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

double Repository::getVelocity() const
{
    return m_velocity;
}

void Repository::setVelocity(double velocity)
{
    try
    {
        m_velocity = velocity;
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::setVelocity: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }
}

size_t Repository::getAxisesCount()
{
    return size_t(m_axes.size());
}

// private

void Repository::loadSettigs()
{
    this->loadServerSettings();
    this->loadAxisesSettings();
    this->loadSensorsSettings();
    this->loadDevicesSettings();

    m_u1Adapter.setPath(m_settingsManager.get("ExternalTools", "U1Adapter").toString());
    m_u2Adapter.setPath(m_settingsManager.get("ExternalTools", "U2Adapter").toString());
}

void Repository::loadServerSettings()
{
    try
    {
        m_port = qint16(m_settingsManager.get("ServerSettings", "ServerPort").toUInt());
    }
    catch(InvalidConfigurationException e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации", QString("Ошибка инициализации порта сервера") + QString(e.message())).exec();
        qDebug() << QStringLiteral("Repository::loadServerSettings:") << e.message();
        emit this->errorOccurred(ERROR_CODE::INVALID_SETTINGS);
        //qApp->exit(0);
    }
}

void Repository::loadSensorsSettings()
{
    try
    {
        QStringList availableSensors = m_settingsManager.get("Main", "AvailableSensors").toStringList();
        for(auto sensorUid : availableSensors)
        {
            QString sectionName = sensorUid;

            QString label = QVariant(m_settingsManager.get(sectionName, "Label")).toString();
            size_t portNumber = QVariant(m_settingsManager.get(sectionName, "PortNumber")).toUInt();
            size_t inputNumber = QVariant(m_settingsManager.get(sectionName, "InputNumber")).toUInt();
            QString boardName = QVariant(m_settingsManager.get(sectionName, "BoardName")).toString();
            bool activeState = QVariant(m_settingsManager.get(sectionName, "ActiveState")).toBool();
            QColor color = QColor(QVariant(m_settingsManager.get(sectionName, "Color")).toString());

            m_sensors.push_back(QSharedPointer<Sensor>(new Sensor(sensorUid,
                                                                  label,
                                                                  portNumber,
                                                                  inputNumber,
                                                                  boardName,
                                                                  activeState,
                                                                  color,
                                                                  this)));
        }

        m_sensorsBufferSize = QVariant(m_settingsManager.get("Main", "SensorsBufferSize")).toUInt();
        m_sensorsBuffer.resetBuffer(m_sensorsBufferSize);
    }
    catch(InvalidConfigurationException e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настроек датчиков", e.message()).exec();
        qDebug() << QStringLiteral("Repository::loadSensorsSettings:") << e.message();
        emit this->errorOccurred(ERROR_CODE::INVALID_SETTINGS);
        //qApp->exit(0);
    }
}

void Repository::loadDevicesSettings()
{
    try
    {
        unsigned int spindelsCount = QVariant(m_settingsManager.get("Main", "SpindelsCount")).toUInt();
        unsigned int supportDevicesCount = QVariant(m_settingsManager.get("Main", "SupportDevicesCount")).toUInt();

        for(unsigned int i = 0; i < spindelsCount; i++)
        {
            QString settingName = QString("Spindel") + QString::number(i);
            QString uid = QVariant(m_settingsManager.get(settingName, "Uid")).toString();
            QString label = QVariant(m_settingsManager.get(settingName, "Label")).toString();
            bool activeState = QVariant(m_settingsManager.get(settingName, "ActiveState")).toBool();
            size_t upperBound = QVariant(m_settingsManager.get(settingName, "UpperBound")).toULongLong();
            size_t lowerBound = QVariant(m_settingsManager.get(settingName, "LowerBound")).toULongLong();
            m_spindels.push_back(QSharedPointer<Spindel> (new Spindel(settingName,
                                                                      uid,
                                                                      label,
                                                                      activeState,
                                                                      lowerBound,
                                                                      upperBound,
                                                                      this)));
        }

        for(unsigned int i = 0; i < supportDevicesCount; i++)
        {
            QString settingName = QString("SupportDevice") + QString::number(i);
            QString uid = QVariant(m_settingsManager.get(settingName, "Uid")).toString();
            QString label = QVariant(m_settingsManager.get(settingName, "Label")).toString();
            bool activeState = QVariant(m_settingsManager.get(settingName, "ActiveState")).toBool();
            m_supportDevices.push_back(QSharedPointer<SupportDevice> (new SupportDevice(settingName,
                                                                                        uid,
                                                                                        label,
                                                                                        activeState,
                                                                                        this)));
        }
    }
    catch(InvalidConfigurationException e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настроек устройств", e.message()).exec();
        qDebug() << QStringLiteral("Repository::loadDevicesSettings:") << e.message();
        emit this->errorOccurred(ERROR_CODE::INVALID_SETTINGS);
        //qApp->exit(0);
    }
}

void Repository::loadAxisesSettings()
{
    try
    {
        QStringList availableAxises = m_settingsManager.get("Main", "AvailableAxises").toStringList();
        for(auto axisUid : availableAxises)
        {
            if(!SML_AXES_NAMES.contains(axisUid)) throw InvalidConfigurationException("Unknown axis uid " + axisUid);

            QString sectionName = QStringLiteral("Axis") + axisUid;

            //double bazaSearchSpeed = m_settingsManager.get(sectionName, "BazaSearchSpeed").toDouble();
            //double lowerBound = m_settingsManager.get(sectionName, "LowerBound").toDouble();
            //double uppderBound = m_settingsManager.get(sectionName, "UpperBound").toDouble();


            AxisId id = Axis::idFromStr(axisUid);
            m_axes.push_back(QSharedPointer<Axis>(new Axis(id, 0.0, this)));

            m_zeroCoordinates.insertAxis(axisUid, 0.0);
            m_parkCoordinates.insertAxis(axisUid, 0.0);
        }
    }
    catch(InvalidConfigurationException e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настроек осей", QString(e.message())).exec();
        qDebug() << QStringLiteral("Repository::loadAxisesSettings:") << e.message();
        emit this->errorOccurred(ERROR_CODE::INVALID_SETTINGS);
        //qApp->exit(0);
    }
}

bool Repository::sensorExists(QString uid)
{
    for(auto sensor : m_sensors)
    {
        if(sensor->uid() == uid)
        {
            return true;
        }
    }

    return false;
}

Point Repository::getCurrentPositionFromBase()
{
    Point result = Point();

    try
    {
        for(auto axis : m_axes)
        {
            result.insertAxis(axis->decoratedId(), axis->currentPosition());
        }
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getCurrentCoordinatesFromBase: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return result;
}

Point Repository::getCurrentPositionFromZero()
{
    Point result = {};

    try
    {
        Point p = this->getCurrentPositionFromBase();
        result = p.operator -=(m_zeroCoordinates);
    }
    catch(...)
    {
        qDebug() << QStringLiteral("Repository::getCurrentCoordinatesFromZero: unknown error");
        emit this->errorOccurred(ERROR_CODE::UNKNOWN_ERROR);
    }

    return result;
}

Sensor &Repository::getSensor(QString uid)
{
    for(auto sensor : m_sensors)
    {
        if(sensor->uid() == uid)
        {
            return *(sensor.data());
        }
    }

    QString message =
            QStringLiteral("sensor with uid = ") +
            uid +
            QStringLiteral(" is not exists");
    qDebug() << QStringLiteral("Repository::getSensor:") << message;
    throw InvalidArgumentException(message);
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
    qDebug() << QStringLiteral("Repository::getDevice:") << message;

    throw InvalidArgumentException(message);
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
    qDebug() << QStringLiteral("Repository::getSpindel") << message;

    throw InvalidArgumentException(message);
}

bool Repository::axisExists(QString uid)
{
    for(auto axis : m_axes)
    {
        if(axis->decoratedId() == uid)
        {
            return true;
        }
    }

    return false;
}

Axis &Repository::getAxis(QString uid)
{
    for(auto axis : m_axes)
    {
        if(axis->id() == uid)
        {
            return *(axis.data());
        }
    }

    QString message =
            QStringLiteral("axis with name ") +
            uid +
            QStringLiteral(" is not exists");
    qDebug() << QStringLiteral("Repository::getAxis") << message;

    throw InvalidArgumentException(message);
}

Point Repository::getMaxPosition()
{
    Point maxPosition = Point();
    for(auto axis : m_axes)
    {
        maxPosition.insertAxis(axis->decoratedId(), 10000);
    }
    return maxPosition;
}
