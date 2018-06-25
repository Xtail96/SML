#include "machinetool.h"

MachineTool::MachineTool(QObject *parent) :
    QObject(parent),
    m_repository(new Repository(this)),
    m_server(new SMLServer(m_repository->m_port, this)),
    m_connectionMonitor(new ConnectionsMonitor(m_repository->m_u1Connection.data(),
                                               m_repository->m_u2Connection.data(),
                                               this)),
    m_pointsMonitor(new PointsMonitor(m_repository->m_pointsManager.data(), this)),
    m_sensorsMonitor(new SensorsMonitor(m_repository->m_sensors, this)),
    m_spindelsMonitor(new SpindelsMonitor(m_repository->m_spindels, this))
{
    setupConnections();
    startServer();
}

MachineTool::~MachineTool()
{
    resetConnections();
}

Repository *MachineTool::repository()
{
    return m_repository.data();
}

void MachineTool::setupConnections()
{
    QObject::connect(m_server.data(), SIGNAL(u1Connected()), this, SLOT(onServer_U1Connected()));
    QObject::connect(m_server.data(), SIGNAL(u1Disconnected()), this, SLOT(onServer_U1Disconnected()));
    QObject::connect(m_server.data(), SIGNAL(u1StateChanged(QList<QVariant>,QList<QVariant>,int)),
                     this, SLOT(onServer_U1StateChanged(QList<QVariant>,QList<QVariant>,int)));

    QObject::connect(m_connectionMonitor.data(), SIGNAL(u1Connected()), this, SLOT(onConnectionMonitor_U1Connected()));
    QObject::connect(m_connectionMonitor.data(), SIGNAL(u1Disconnected()), this, SLOT(onConnectionMonitor_U1Disconnected()));
    QObject::connect(m_connectionMonitor.data(), SIGNAL(u1LastErrorChanged(int)), this, SLOT(onConnectionMonitor_U1LastErrorChanged(int)));

    QObject::connect(m_pointsMonitor.data(), SIGNAL(pointsUpdated()), this, SLOT(onPointsMonitor_PointsUpdated()));
    QObject::connect(m_sensorsMonitor.data(), SIGNAL(stateChanged(QString,bool)), this, SLOT(onSensorMonitor_StateChanged(QString,bool)));
    QObject::connect(m_spindelsMonitor.data(), SIGNAL(stateChanged(QString,bool,size_t)), this, SLOT(onSpindelsMonitor_StateChanged(QString,bool,size_t)));


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
    QObject::disconnect(m_connectionMonitor.data(), SIGNAL(u1LastErrorChanged(int)), this, SLOT(onConnectionMonitor_U1LastErrorChanged(int)));

    QObject::disconnect(m_pointsMonitor.data(), SIGNAL(pointsUpdated()), this, SLOT(onPointsMonitor_PointsUpdated()));
    QObject::disconnect(m_sensorsMonitor.data(), SIGNAL(stateChanged(QString,bool)), this, SLOT(onSensorMonitor_StateChanged(QString,bool)));
    QObject::disconnect(m_spindelsMonitor.data(), SIGNAL(stateChanged(QString,bool,size_t)), this, SLOT(onSpindelsMonitor_StateChanged(QString,bool,size_t)));

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

void MachineTool::onConnectionMonitor_U1LastErrorChanged(int code)
{
    qDebug() << "u1 eror" << code;
    emit u1Error(code);
}

void MachineTool::onPointsMonitor_PointsUpdated()
{
    emit pointsUpdated();
}

void MachineTool::onSensorMonitor_StateChanged(QString sensorName, bool state)
{
    /*if(sensorName == "name")
    {
        do somtething
    }*/
    QColor led = QColor(SmlColors::white());
    if(state)
    {
        led = m_repository->findSensor(sensorName)->getColor();
    }
    emit sensorStateChanged(sensorName, led);
}

void MachineTool::onSpindelsMonitor_StateChanged(QString index, bool state, size_t rotations)
{
    emit spindelStateChanged(index, state, rotations);
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


void MachineTool::parseGCodes()
{
    //m_gcodesManager->updateGCodesProgram();
}

void MachineTool::onServer_U1StateChanged(QList<QVariant> sensors, QList<QVariant> devices, int error)
{
    m_repository->setU1Sensors(sensors);
    m_repository->setU1Devices(devices);
    m_repository->setU1Error(error);
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

void MachineTool::openGCodesFile()
{
    /*connect(m_gcodesFilesManager.data(), SIGNAL(loadedFile()), this, SLOT(onGCodesLoaded()));

    m_gcodesFilesManager->openGCodesFile();

    disconnect(m_gcodesFilesManager.data(), SIGNAL(loadedFile()), this, SLOT(onGCodesLoaded()));*/
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
