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
    m_spindelsMonitor(new SpindelsMonitor(m_repository->m_spindels, this)),
    m_gcodesMonitor(new GCodesMonitor(m_repository->m_gcodesFilesManager.data(), this))
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

    QObject::connect(m_gcodesMonitor.data(), SIGNAL(filePathUpdated(QString)), this, SLOT(onGCodesMonitor_FilePathUpdated(QString)));
    QObject::connect(m_gcodesMonitor.data(), SIGNAL(fileContentUpdated(QString)), this, SLOT(onGCodesMonitor_FileContentUpdated(QString)));


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

    QObject::disconnect(m_gcodesMonitor.data(), SIGNAL(filePathUpdated(QString)), this, SLOT(onGCodesMonitor_FilePathUpdated(QString)));
    QObject::disconnect(m_gcodesMonitor.data(), SIGNAL(fileContentUpdated(QString)), this, SLOT(onGCodesMonitor_FileContentUpdated(QString)));

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

void MachineTool::onGCodesMonitor_FilePathUpdated(QString path)
{
    emit gcodesFilePathUpdated(path);
}

void MachineTool::onGCodesMonitor_FileContentUpdated(QString content)
{
    emit gcodesFileContentUpdated(content);
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

void MachineTool::switchSpindelOn(QString index, size_t rotations)
{
    SwitchSpindel swithcer(index, true, rotations);
    swithcer.start(m_server.data());
}

void MachineTool::switchSpindelOff(QString index)
{
    SwitchSpindel switcher(index, false);
    switcher.start(m_server.data());
}
