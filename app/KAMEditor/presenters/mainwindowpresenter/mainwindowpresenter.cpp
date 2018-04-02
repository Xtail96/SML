#include "mainwindowpresenter.h"

MainWindowPresenter::MainWindowPresenter(QObject *parent) :
    QObject(parent),
    m_settingsManager(new SettingsManager()),
    m_serverManager(new ServerConnectionManager(m_settingsManager, false, this)),
    m_sensorsManager(new SensorsManager(m_settingsManager)),
    m_devicesManager(new DevicesManager(m_settingsManager)),
    m_axisesManager(new AxisesManager(m_settingsManager)),
    m_gcodesFilesManager(new GCodesFilesManager(this)),
    m_gcodesManager(new GCodesManager()),
    m_pointsManager(new PointsManager())
{
    connect(m_serverManager, SIGNAL(u1StateIsChanged()), this, SLOT(updateU1State()));
    connect(m_serverManager, SIGNAL(textMessageReceived(QString)), this, SLOT(onMessageReceived(QString)));
    connect(m_serverManager, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onMessageReceived(QByteArray)));

    connect(m_serverManager, SIGNAL(serverIsConnected()), this, SLOT(onConnected()));
    connect(m_serverManager, SIGNAL(serverIsDisconnected(QString)), this, SLOT(onDisconnected(QString)));
}

MainWindowPresenter::~MainWindowPresenter()
{
    delete m_pointsManager;
    delete m_gcodesManager;
    delete m_gcodesFilesManager;
    delete m_axisesManager;
    delete m_devicesManager;
    delete m_sensorsManager;
    delete m_serverManager;
    delete m_settingsManager;
}

void MainWindowPresenter::onConnected()
{
    updateU1State();
}

void MainWindowPresenter::onDisconnected(QString message)
{
    emit machineToolIsDisconnected(message);
}

void MainWindowPresenter::updateU1State()
{
    byte_array sensors = m_serverManager->getSensorsState();
    byte_array devices = m_serverManager->getDevicesState();
    m_sensorsManager->updateSensors(sensors);
    m_devicesManager->updateDevices(devices);
    emit u1StateIsChanged();
}

void MainWindowPresenter::sendTextMessgeToServer(QString message)
{
    if(!m_serverManager->sendTextMessage(message))
    {
        QMessageBox(QMessageBox::Warning,
                    "Ошибка подключения",
                    QString("Не могу отправить на серевер сообщение") + message).exec();
    }
}

void MainWindowPresenter::sendBinaryMessageToServer(QByteArray message)
{
    if(!m_serverManager->sendBinaryMessage(message))
    {
        QMessageBox(QMessageBox::Warning,
                    "Ошибка подключения",
                    QString("Не могу отправить на серевер сообщение") + QString::fromUtf8(message)).exec();
    }
}

void MainWindowPresenter::onMessageReceived(QString message)
{
    emit receivedMessage(message);
}

void MainWindowPresenter::onMessageReceived(QByteArray message)
{
    emit receivedMessage(QString::fromUtf8(message));
}

void MainWindowPresenter::openWebSocketConnection()
{
    m_serverManager->openWebSocket();
}

void MainWindowPresenter::closeWebSocketConnection()
{
    m_serverManager->closeWebSocket();
}

void MainWindowPresenter::onGCodesLoadingStart()
{
    emit gcodesLoadingStart();
}

void MainWindowPresenter::onGCodesLoading(int currentValue)
{
    emit gcodesIsLoading(currentValue);
}

void MainWindowPresenter::onGCodesLoaded()
{
    emit gcodesLoaded();
}

void MainWindowPresenter::exportSettings()
{
    QString path = QFileDialog::getSaveFileName(0, "Выберите путь до файла", "", "*.ini");
    m_settingsManager->exportSettings(path);
}

void MainWindowPresenter::importSettings()
{
    QString path = QFileDialog::getOpenFileName(0, "Выберите файл с настройками", "", "*.ini");
    m_settingsManager->importSettings(path);
}

void MainWindowPresenter::parseGCodes(QString data)
{
    m_gcodesManager->updateGCodesProgram(data);
}

void MainWindowPresenter::setSoftLimitsMode(bool enable)
{
    m_axisesManager->setSoftLimitsMode(enable);
}

void MainWindowPresenter::switchDevice(QString deviceName)
{
    try
    {
        Device &device = m_devicesManager->findDevice(deviceName);
        qDebug() << "current state = " << device.getCurrentState();
        byte_array data = m_devicesManager->switchDeviceData(device, !device.getCurrentState());

        QtJson::JsonObject generalMessage;
        QtJson::JsonObject u1Message;
        QtJson::JsonArray u1Data;

        for(auto byte_unit : data)
        {
            u1Data.push_back(byte_unit);
        }
        u1Message["SwitchDevice"] = u1Data;
        generalMessage["MessageToU1"] = u1Message;


        bool ok = false;
        QByteArray message = QtJson::serialize(generalMessage, ok);
        qDebug() << "Try to switch device =" << message;
        if(ok)
        {
            m_serverManager->sendBinaryMessage(message);
        }
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

void MainWindowPresenter::updateVelocity(int value)
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

void MainWindowPresenter::updateSpindelRotations(int value)
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

void MainWindowPresenter::addPoint(QStringList coordinates)
{
    Point* p = PointsManager::makePoint(coordinates);
    m_pointsManager->addPoint(p);
    emit pointsUpdated();
}

void MainWindowPresenter::updatePoint(QStringList coordinates, unsigned int number)
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

void MainWindowPresenter::deletePoint(unsigned int number)
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


void MainWindowPresenter::openGCodesFile()
{
    connect(m_gcodesFilesManager, SIGNAL(startLoading()), this, SLOT(onGCodesLoadingStart()));
    connect(m_gcodesFilesManager, SIGNAL(loading(int)), this, SLOT(onGCodesLoading(int)));
    connect(m_gcodesFilesManager, SIGNAL(loaded()), this, SLOT(onGCodesLoaded()));

    m_gcodesFilesManager->openGCodesFile();

    emit gcodesUpdated();
    emit filePathUpdated();
}

QString MainWindowPresenter::getGCodesFileContent()
{
    return m_gcodesFilesManager->getContent();
}

void MainWindowPresenter::saveGCodesFile(const QString data)
{

    m_gcodesFilesManager->setFileContent(data);
    m_gcodesFilesManager->saveGCodesFile();
    emit filePathUpdated();
}

void MainWindowPresenter::saveGCodesFileAs(const QString data)
{
    m_gcodesFilesManager->setFileContent(data);
    m_gcodesFilesManager->saveGCodesFileAs();
    emit filePathUpdated();
}

void MainWindowPresenter::newGCodesFile()
{
    m_gcodesFilesManager->newGCodesFile();
    emit gcodesUpdated();
    emit filePathUpdated();
}

void MainWindowPresenter::addGCodesFile(const QString data)
{
    saveGCodesFile(data);
    m_gcodesFilesManager->addGCodesFile();
    emit gcodesUpdated();
    emit filePathUpdated();
}

void MainWindowPresenter::updateGCodes(const QString &data)
{
    m_gcodesManager->setGcodes(data);
}

QString MainWindowPresenter::getGCodesProgram()
{
    return m_gcodesManager->gcodes();
}

QList<Point> MainWindowPresenter::getMachineToolCoordinates()
{
    QList<Point> machineToolCoordinates;
    machineToolCoordinates.push_back(m_axisesManager->getCurrentCoordinatesFromZero());
    machineToolCoordinates.push_back(m_axisesManager->getCurrentCoordinatesFromBase());
    machineToolCoordinates.push_back(m_axisesManager->getParkCoordinates());
    return machineToolCoordinates;
}

QStringList MainWindowPresenter::getSensorsLabels()
{
    return m_sensorsManager->sensorsLabels();
}

QStringList MainWindowPresenter::getSensorParametrLabels()
{
    return m_sensorsManager->sensorParametrLabels();
}

QList<QStringList> MainWindowPresenter::getSensorsSettings()
{
    return m_sensorsManager->sensorsSettings();
}

QList<QColor> MainWindowPresenter::getSensorsLeds()
{
    return m_sensorsManager->sensorsLeds();
}

QStringList MainWindowPresenter::getDevicesNames()
{
    return m_devicesManager->devicesNames();
}

QStringList MainWindowPresenter::getDevicesParametrsNames()
{
    return m_devicesManager->devicesParametrsNames();
}

QList<QStringList> MainWindowPresenter::getDevicesSettings()
{
    return m_devicesManager->devicesSettings();
}

QStringList MainWindowPresenter::getOnScreenDevicesNames()
{
    return m_devicesManager->onScreenDevicesNames();
}

QList<bool> MainWindowPresenter::getOnScreenDevicesStates()
{
    return m_devicesManager->onScreenDevicesStates();
}

QStringList MainWindowPresenter::getAxisesNames()
{
    return m_axisesManager->getAxisesNames();
}

QStringList MainWindowPresenter::getAxisesSettings()
{
    return m_axisesManager->getAxisesSettings();
}

QStringList MainWindowPresenter::getOptionsNames()
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

unsigned int MainWindowPresenter::getVelocity()
{
    //return m_machineTool->getVelocity();
    return feedrate;
}

unsigned int MainWindowPresenter::getSpindelRotations()
{
    //return m_machineTool->getSpindelRotations();
    return rotations;
}

QList<QStringList> MainWindowPresenter::getPoints()
{
    return m_pointsManager->points();
}

QStringList MainWindowPresenter::getPoint(unsigned int number)
{
    return m_pointsManager->point(number);
}

QString MainWindowPresenter::getFilePath(QString type)
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
