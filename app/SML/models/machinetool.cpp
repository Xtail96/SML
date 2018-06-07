#include "machinetool.h"

MachineTool::MachineTool(QObject *parent) :
    QObject(parent),
    m_settingsManager(new SettingsManager()),
    m_serverManager(new ServerManager(*(m_settingsManager.data()), this)),
    m_sensorsManager(new SensorsManager(*(m_settingsManager.data()))),
    m_devicesManager(new DevicesManager(*(m_settingsManager.data()))),
    m_axisesManager(new AxisesManager(*(m_settingsManager.data()))),
    m_gcodesFilesManager(new GCodesFilesManager(this)),
    m_gcodesManager(new GCodesManager()),
    m_pointsManager(new PointsManager()),
    m_u1Connected(false),
    m_u2Connected(false)
{
    setup();
    startServer();
}

MachineTool::~MachineTool()
{
    reset();
}

void MachineTool::setup()
{
    connect(m_serverManager.data(), SIGNAL(u1Connected()), this, SLOT(onU1Connected()));
    connect(m_serverManager.data(), SIGNAL(u1Disconnected()), this, SLOT(onU1Disconnected()));
    connect(m_serverManager.data(), SIGNAL(u1StateIsChanged()), this, SLOT(updateU1State()));
    connect(m_serverManager.data(), SIGNAL(u1ErrorIsOccured(int)), this, SLOT(onU1Error(int)));
}

void MachineTool::reset()
{
    disconnect(m_serverManager.data(), SIGNAL(u1Connected()), this, SLOT(onU1Connected()));
    disconnect(m_serverManager.data(), SIGNAL(u1Disconnected()), this, SLOT(onU1Disconnected()));
    disconnect(m_serverManager.data(), SIGNAL(u1StateIsChanged()), this, SLOT(updateU1State()));
    disconnect(m_serverManager.data(), SIGNAL(u1ErrorIsOccured(int)), this, SLOT(onU1Error(int)));
}

void MachineTool::onU1Error(int errorCode)
{
    handleMachineToolErrors(errorCode);
}

void MachineTool::onU1Connected()
{
    updateU1State();
    emit u1Connected();
}

void MachineTool::onU1Disconnected()
{
    updateU1State();
    emit u1Disconnected();
}

void MachineTool::updateU1State()
{
    byte_array sensors = m_serverManager->getSensorsState();
    byte_array devices = m_serverManager->getDevicesState();
    m_sensorsManager->updateSensors(sensors);
    m_devicesManager->updateDevices(devices);
    emit u1StateIsChanged();
}

void MachineTool::onGCodesLoaded()
{
    emit gcodesUpdated();
    emit filePathUpdated();
}

void MachineTool::exportSettings()
{
    QString path = QFileDialog::getSaveFileName(0, "Выберите путь до файла", "", "*.ini");
    m_settingsManager->exportSettings(path);
}

void MachineTool::importSettings()
{
    QString path = QFileDialog::getOpenFileName(0, "Выберите файл с настройками", "", "*.ini");
    m_settingsManager->importSettings(path);
}

void MachineTool::parseGCodes()
{
    m_gcodesManager->updateGCodesProgram();
}

void MachineTool::setSoftLimitsMode(bool enable)
{
    m_axisesManager->setSoftLimitsMode(enable);
}

QStringList MachineTool::getCurrentConnections()
{
    return m_serverManager->getCurrentConnections();
}

QString MachineTool::getServerPort()
{
    return QString::number(m_serverManager->getServerPort());
}

QString MachineTool::getSensorsBufferSize()
{
    return QString::number(m_serverManager->getSensorsBufferSize());
}

QString MachineTool::getDevicesBufferSize()
{
    return QString::number(m_serverManager->getDevicesBufferSize());
}

void MachineTool::handleMachineToolErrors(int errorCode)
{
    // обрабатываем ошибки и испускаем сигнал об их наступлении
    emit machineToolErrorIsOccured(errorCode);
}

void MachineTool::startServer()
{
    m_serverManager->startServer();
}

void MachineTool::stopServer()
{
    m_serverManager->stopServer();
}

void MachineTool::switchDevice(QString deviceName)
{
    try
    {
        Device &device = m_devicesManager->findDevice(deviceName);
        qDebug() << "current state = " << device.getCurrentState();
        byte mask = m_devicesManager->getDeviceSwitchMask(device, !device.getCurrentState());

        QStringList params;
        params.push_back(QString("18000"));

        m_serverManager->switchDevice(mask, ServerManager::Spindel, params);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

void MachineTool::updateVelocity(int value)
{
    if(value >= 0)
    {
        feedrate = value;
    }
    else
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Скорость не может быть отрицательной").exec();
    }
}

void MachineTool::updateSpindelRotations(int value)
{
    if(value >= 0)
    {
        rotations = value;
    }
    else
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Обороты шпинделя не могут быть отрицательными").exec();
    }
}

void MachineTool::addPoint(QStringList coordinates)
{
    Point* p = PointsManager::makePoint(coordinates);
    m_pointsManager->addPoint(p);
    emit pointsUpdated();
}

void MachineTool::updatePoint(QStringList coordinates, unsigned int number)
{
    Point* p = PointsManager::makePoint(coordinates);
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
    }
}

void MachineTool::deletePoint(unsigned int number)
{
    try
    {
        std::shared_ptr<Point> p = m_pointsManager->operator [](number);
        m_pointsManager->deletePoint(p);
        emit pointsUpdated();
    }
    catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}


void MachineTool::openGCodesFile()
{
    connect(m_gcodesFilesManager.data(), SIGNAL(loadedFile()), this, SLOT(onGCodesLoaded()));

    m_gcodesFilesManager->openGCodesFile();

    disconnect(m_gcodesFilesManager.data(), SIGNAL(loadedFile()), this, SLOT(onGCodesLoaded()));
}

QString MachineTool::getGCodesFileContent()
{
    return m_gcodesFilesManager->getContent();
}

void MachineTool::saveGCodesFile(const QString data)
{

    m_gcodesFilesManager->setFileContent(data);
    m_gcodesFilesManager->saveGCodesFile();
    emit filePathUpdated();
}

void MachineTool::saveGCodesFileAs(const QString data)
{
    m_gcodesFilesManager->setFileContent(data);
    m_gcodesFilesManager->saveGCodesFileAs();
    emit filePathUpdated();
}

void MachineTool::newGCodesFile()
{
    m_gcodesFilesManager->newGCodesFile();
    emit gcodesUpdated();
    emit filePathUpdated();
}

void MachineTool::addGCodesFile(const QString data)
{
    saveGCodesFile(data);
    m_gcodesFilesManager->addGCodesFile();
    emit gcodesUpdated();
    emit filePathUpdated();
}

void MachineTool::setGCodes(const QString &data)
{
    m_gcodesManager->setGcodes(data);
}

QString MachineTool::getGCodesProgram()
{
    return m_gcodesManager->gcodes();
}

QList<Point> MachineTool::getMachineToolCoordinates()
{
    QList<Point> machineToolCoordinates;
    machineToolCoordinates.push_back(m_axisesManager->getCurrentCoordinatesFromZero());
    machineToolCoordinates.push_back(m_axisesManager->getCurrentCoordinatesFromBase());
    machineToolCoordinates.push_back(m_axisesManager->getParkCoordinates());
    return machineToolCoordinates;
}

QStringList MachineTool::getSensorsLabels()
{
    return m_sensorsManager->sensorsLabels();
}

QStringList MachineTool::getSensorParametrLabels()
{
    return m_sensorsManager->sensorParametrLabels();
}

QList<QStringList> MachineTool::getSensorsSettings()
{
    return m_sensorsManager->sensorsSettings();
}

QList<QColor> MachineTool::getSensorsLeds()
{
    return m_sensorsManager->sensorsLeds();
}

QStringList MachineTool::getDevicesNames()
{
    return m_devicesManager->getAllDevicesNames();
}

QStringList MachineTool::getDevicesParametrsNames()
{
    return m_devicesManager->getDevicesParametrsNames();
}

QList<QStringList> MachineTool::getDevicesSettings()
{
    return m_devicesManager->getDevicesSettings();
}

QStringList MachineTool::getOnScreenDevicesNames()
{
    return m_devicesManager->onScreenDevicesNames();
}

QList<bool> MachineTool::getOnScreenDevicesStates()
{
    return m_devicesManager->onScreenDevicesStates();
}

QStringList MachineTool::getAxisesNames()
{
    return m_axisesManager->getAxisesNames();
}

QStringList MachineTool::getAxisesSettings()
{
    return m_axisesManager->getAxisesSettings();
}

QStringList MachineTool::getOptionsNames()
{
    //todo: переписсать метод через модель
    QStringList optionsNames =
    {
        "Кабриоль",
        "Датчик вылета инструмента",
        "Станция автоматической смазки"
    };
    return optionsNames;
}

size_t MachineTool::getFeedrate() const
{
    //return m_machineTool->getVelocity();
    return feedrate;
}

size_t MachineTool::getSpindelRotations() const
{
    //return m_machineTool->getSpindelRotations();
    return rotations;
}

QList<QStringList> MachineTool::getPoints()
{
    return m_pointsManager->points();
}

QStringList MachineTool::getPoint(unsigned int number)
{
    return m_pointsManager->point(number);
}

QString MachineTool::getFilePath(QString type)
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
