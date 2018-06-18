#include "machinetool.h"

MachineTool::MachineTool(QObject *parent) :
    QObject(parent),
    m_repository(new Repository(this)),
    m_server(new SMLServer(m_repository->m_port, this)),
    m_connectionMonitor(new ConnectionsMonitor(m_repository->m_u1Connection.data(),
                                               m_repository->m_u2Connection.data(),
                                               this))
{
    setupConnections();
    startServer();
}

MachineTool::~MachineTool()
{
    resetConnections();
}

void MachineTool::setupConnections()
{
    QObject::connect(m_server.data(), SIGNAL(u1Connected()), this, SLOT(onServer_U1Connected()));
    QObject::connect(m_server.data(), SIGNAL(u1Disconnected()), this, SLOT(onServer_U1Disconnected()));
    QObject::connect(m_server.data(), SIGNAL(u1StateChanged(QList<QVariant>,QList<QVariant>,int)),
                     this, SLOT(onServer_U1StateChanged(QList<QVariant>,QList<QVariant>,int)));

    QObject::connect(m_connectionMonitor.data(), SIGNAL(u1Connected()), this, SLOT(onConnectionMonitor_U1Connected()));
    QObject::connect(m_connectionMonitor.data(), SIGNAL(u1Disconnected()), this, SLOT(onConnectionMonitor_U1Disconnected()));
    QObject::connect(m_connectionMonitor.data(), SIGNAL(u1LastErrorChanged(int)), this, SLOT(onConnectionMonitor_U1Error(int)));


    /*QObject::connect(m_serverManager.data(), SIGNAL(u1Connected()), this, SLOT(onU1Connected()));
    QObject::connect(m_serverManager.data(), SIGNAL(u1Disconnected()), this, SLOT(onU1Disconnected()));
    QObject::connect(m_serverManager.data(), SIGNAL(u1StateIsChanged()), this, SLOT(updateU1State()));
    QObject::connect(m_serverManager.data(), SIGNAL(u1ErrorIsOccured(int)), this, SLOT(onU1Error(int)));

    QStringList sensorsNames = m_sensorsManager->sensorsNames();
    for(auto name : sensorsNames)
    {
        Sensor* sensor = m_sensorsManager->findSensor(name);
        QObject::connect(sensor, SIGNAL(stateChanged(QString,bool)), this, SLOT(onSensorStateChanged(QString,bool)));
    }*/
}

void MachineTool::resetConnections()
{
    QObject::disconnect(m_server.data(), SIGNAL(u1Connected()), this, SLOT(onServer_U1Connected()));
    QObject::disconnect(m_server.data(), SIGNAL(u1Disconnected()), this, SLOT(onServer_U1Disconnected()));
    QObject::disconnect(m_server.data(), SIGNAL(u1StateChanged(QList<QVariant>,QList<QVariant>,int)),
                     this, SLOT(onServer_U1StateChanged(QList<QVariant>,QList<QVariant>,int)));

    QObject::disconnect(m_connectionMonitor.data(), SIGNAL(u1Connected()), this, SLOT(onConnectionMonitor_U1Connected()));
    QObject::disconnect(m_connectionMonitor.data(), SIGNAL(u1Disconnected()), this, SLOT(onConnectionMonitor_U1Disconnected()));
    QObject::disconnect(m_connectionMonitor.data(), SIGNAL(u1LastErrorChanged(int)), this, SLOT(onConnectionMonitor_U1Error(int)));

    /*QObject::disconnect(m_serverManager.data(), SIGNAL(u1Connected()), this, SLOT(onU1Connected()));
    QObject::disconnect(m_serverManager.data(), SIGNAL(u1Disconnected()), this, SLOT(onU1Disconnected()));
    QObject::disconnect(m_serverManager.data(), SIGNAL(u1StateIsChanged()), this, SLOT(updateU1State()));
    QObject::disconnect(m_serverManager.data(), SIGNAL(u1ErrorIsOccured(int)), this, SLOT(onU1Error(int)));

    QStringList sensorsNames = m_sensorsManager->sensorsNames();
    for(auto name : sensorsNames)
    {
        Sensor* sensor = m_sensorsManager->findSensor(name);
        QObject::disconnect(sensor, SIGNAL(stateChanged(QString,bool)), this, SLOT(onSensorStateChanged(QString,bool)));
    }*/
}

void MachineTool::onConnectionMonitor_U1Connected()
{
    emit u1Connected();
}

void MachineTool::onConnectionMonitor_U1Disconnected()
{
    emit u1Disconnected();
}

void MachineTool::onConnectionMonitor_U1Error(int code)
{
    qDebug() << "u1 eror" << code;
    //emit u1Disconnected();
}

void MachineTool::onSensorStateChanged(QString sensorName, bool state)
{
    /*if(sensorName == "name")
    {
        do somtething
    }*/
    /*QColor led = QColor(SmlColors::white());
    if(state)
    {
        led =  m_sensorsManager->findSensor(sensorName)->getColor();
    }
    emit sensorStateChanged(sensorName, led);*/
}

void MachineTool::onServer_U1Error(int errorCode)
{
    m_repository->setU1Error(errorCode);
}

void MachineTool::onServer_U1Connected()
{
    m_repository->setU1Connected(true);
}

void MachineTool::onServer_U1Disconnected()
{
    m_repository->setU1Connected(false);
}

void MachineTool::updateU1State()
{
    /*byte_array sensors = m_serverManager->getSensorsState();
    byte_array devices = m_serverManager->getDevicesState();
    m_sensorsManager->updateSensors(sensors);
    m_devicesManager->updateDevices(devices);
    emit u1StateIsChanged();*/
}

void MachineTool::onGCodesLoaded()
{
    //emit gcodesUpdated();
    //emit filePathUpdated();
}

void MachineTool::exportSettings()
{
    //QString path = QFileDialog::getSaveFileName(0, "Выберите путь до файла", "", "*.ini");
    //m_settingsManager->exportSettings(path);
}

void MachineTool::importSettings()
{
    //QString path = QFileDialog::getOpenFileName(0, "Выберите файл с настройками", "", "*.ini");
    //m_settingsManager->importSettings(path);
}

QStringList MachineTool::getSensorNames()
{
    //return m_sensorsManager->sensorsNames();
}

QMap<QString, QString> MachineTool::getSensorSettings(QString name)
{
    /*QMap<QString, QString> sensorsSettingsMap;
    QString settingsString = m_sensorsManager->sensorSettings(name);
    QStringList settingsList = settingsString.split(";");

    for(auto setting : settingsList)
    {
        QStringList item = setting.split(":");
        if(item.size() == 2)
        {
            sensorsSettingsMap.insert(item.at(0), item.at(1));
        }
    }
    return sensorsSettingsMap;*/
}

void MachineTool::parseGCodes()
{
    //m_gcodesManager->updateGCodesProgram();
}

void MachineTool::setSoftLimitsMode(bool enable)
{
    //m_axisesManager->setSoftLimitsMode(enable);
}

QStringList MachineTool::getCurrentConnections()
{
    //return m_serverManager->getCurrentConnections();
}

QString MachineTool::getServerPort()
{
    //return QString::number(m_serverManager->getServerPort());
}

QString MachineTool::getSensorsBufferSize()
{
    //return QString::number(m_serverManager->getSensorsBufferSize());
}

QString MachineTool::getDevicesBufferSize()
{
    //return QString::number(m_serverManager->getDevicesBufferSize());
}

QList<Spindel*> MachineTool::getSpindels()
{
    //return m_devicesManager->getSpindels();
}

void MachineTool::onServer_U1StateChanged(QList<QVariant> sensors, QList<QVariant> devices, int error)
{
    m_repository->setU1Sensors(sensors);
    m_repository->setU1Devices(devices);
    m_repository->setU1Error(error);
}

void MachineTool::handleMachineToolErrors(int errorCode)
{
    // обрабатываем ошибки и испускаем сигнал об их наступлении
    //emit machineToolErrorIsOccured(errorCode);
}

void MachineTool::startServer()
{
    m_server->start();
}

void MachineTool::stopServer()
{
    m_server->stop();
}

void MachineTool::switchSpindelOn(QString spindelName, size_t rotations)
{
    /*try
    {
        Spindel &spindel = m_devicesManager->findSpindel(spindelName);
        m_devicesManager->setSpindelRotations(spindel.getName(), rotations);
        QStringList params = m_devicesManager->getSwitchSpindelParams(spindel.getName());
        m_serverManager->switchDeviceOn(ServerManager::Spindel, spindel.getIndex(), params);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }*/
}

void MachineTool::switchSpindelOff(QString spindelName)
{
    /*try
    {
        Spindel &spindel = m_devicesManager->findSpindel(spindelName);
        m_serverManager->switchDeviceOff(ServerManager::Spindel, spindel.getIndex());
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }*/
}

void MachineTool::addPoint(QStringList coordinates)
{
    /*Point* p = PointsManager::makePoint(coordinates);
    m_pointsManager->addPoint(p);
    emit pointsUpdated();*/
}

void MachineTool::updatePoint(QStringList coordinates, unsigned int number)
{
    /*Point* p = PointsManager::makePoint(coordinates);
    try
    {
        std::shared_ptr<Point> originPoint = m_pointsManager->operator [](number);
        unsigned int originPointDimension = originPoint->size();
        unsigned int newPointDimension = p->size();
        unsigned int rangeForUpdate = std::min(originPointDimension, newPointDimension);
        for(unsigned int i = 0; i < rangeForUpdate; i++)
        {
            originPoint->get(i) = p->get(i);
        }
        emit pointsUpdated();
    }
    catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }*/
}

void MachineTool::deletePoint(unsigned int number)
{
    /*try
    {
        std::shared_ptr<Point> p = m_pointsManager->operator [](number);
        m_pointsManager->deletePoint(p);
        emit pointsUpdated();
    }
    catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }*/
}


void MachineTool::openGCodesFile()
{
    /*connect(m_gcodesFilesManager.data(), SIGNAL(loadedFile()), this, SLOT(onGCodesLoaded()));

    m_gcodesFilesManager->openGCodesFile();

    disconnect(m_gcodesFilesManager.data(), SIGNAL(loadedFile()), this, SLOT(onGCodesLoaded()));*/
}

QString MachineTool::getGCodesFileContent()
{
    //return m_gcodesFilesManager->getContent();
}

void MachineTool::saveGCodesFile(const QString data)
{

    /*m_gcodesFilesManager->setFileContent(data);
    m_gcodesFilesManager->saveGCodesFile();
    emit filePathUpdated();*/
}

void MachineTool::saveGCodesFileAs(const QString data)
{
    /*m_gcodesFilesManager->setFileContent(data);
    m_gcodesFilesManager->saveGCodesFileAs();
    emit filePathUpdated();*/
}

void MachineTool::newGCodesFile()
{
    /*m_gcodesFilesManager->newGCodesFile();
    emit gcodesUpdated();
    emit filePathUpdated();*/
}

void MachineTool::addGCodesFile(const QString data)
{
    /*saveGCodesFile(data);
    m_gcodesFilesManager->addGCodesFile();
    emit gcodesUpdated();
    emit filePathUpdated();*/
}

void MachineTool::setGCodes(const QString &data)
{
    //m_gcodesManager->setGcodes(data);
}

QString MachineTool::getGCodesProgram()
{
    //return m_gcodesManager->gcodes();
}

QList<Point> MachineTool::getMachineToolCoordinates()
{
    /*QList<Point> machineToolCoordinates;
    machineToolCoordinates.push_back(m_axisesManager->getCurrentCoordinatesFromZero());
    machineToolCoordinates.push_back(m_axisesManager->getCurrentCoordinatesFromBase());
    machineToolCoordinates.push_back(m_axisesManager->getParkCoordinates());
    return machineToolCoordinates;*/
}

QStringList MachineTool::getSensorsSettings()
{
    //return m_sensorsManager->sensorsSettings();
}

QStringList MachineTool::getDevicesNames()
{
    //return m_devicesManager->getAllDevicesNames();
}

QStringList MachineTool::getDevicesParametrsNames()
{
    //return m_devicesManager->getDevicesParametrsNames();
}

QList<QStringList> MachineTool::getDevicesSettings()
{
    //return m_devicesManager->getDevicesSettings();
}

QStringList MachineTool::getOnScreenDevicesNames()
{
    //return m_devicesManager->onScreenDevicesNames();
}

QList<bool> MachineTool::getOnScreenDevicesStates()
{
    //return m_devicesManager->onScreenDevicesStates();
}

QStringList MachineTool::getAxisesNames()
{
    //return m_axisesManager->getAxisesNames();
}

QStringList MachineTool::getAxisesSettings()
{
    //return m_axisesManager->getAxisesSettings();
}

QStringList MachineTool::getOptionsNames()
{
    //todo: переписсать метод через модель
    /*QStringList optionsNames =
    {
        "Кабриоль",
        "Датчик вылета инструмента",
        "Станция автоматической смазки"
    };
    return optionsNames;*/
}

size_t MachineTool::getFeedrate() const
{
    //return m_machineTool->getVelocity();
    //return feedrate;
}

size_t MachineTool::getSpindelRotations() const
{
    //return m_machineTool->getSpindelRotations();
    //return rotations;
}

QList<QStringList> MachineTool::getPoints()
{
    //return m_pointsManager->points();
}

QStringList MachineTool::getPoint(unsigned int number)
{
    //return m_pointsManager->point(number);
}

QString MachineTool::getFilePath(QString type)
{
    /*QString path = "";
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
    return path;*/
}
