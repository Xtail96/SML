#include "machinetool.h"

MachineTool::MachineTool(QObject *parent) :
    QObject(parent),
    m_repository(new Repository(this)),
    m_adapterServer(new SMLServer(m_repository->m_port, this)),
    m_connectionMonitor(new ConnectionsMonitor(m_repository->m_u1Connection.data(),
                                               m_repository->m_u2Connection.data(),
                                               this)),
    m_pointsMonitor(new PointsMonitor(m_repository->m_pointsManager.data(), this)),
    m_sensorsMonitor(new SensorsMonitor(m_repository->m_sensors, this)),
    m_spindelsMonitor(new SpindelsMonitor(m_repository->m_spindels, this)),
    m_gcodesMonitor(new GCodesMonitor(m_repository->m_gcodesFilesManager.data(), this)),
    m_lastError(0)
{
    setupConnections();
    startAdapterServer();
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
    QObject::connect(m_adapterServer.data(), SIGNAL(u1Connected()), this, SLOT(onServer_U1Connected()));
    QObject::connect(m_adapterServer.data(), SIGNAL(u1Disconnected()), this, SLOT(onServer_U1Disconnected()));
    QObject::connect(m_adapterServer.data(), SIGNAL(u1StateChanged(QList<QVariant>,QList<QVariant>)),
                     this, SLOT(onServer_U1StateChanged(QList<QVariant>,QList<QVariant>)));
    QObject::connect(m_adapterServer.data(), SIGNAL(errorOccured(int)), this, SLOT(onServer_ErrorOccured(int)));

    QObject::connect(m_connectionMonitor.data(), SIGNAL(u1Connected()), this, SLOT(onConnectionMonitor_U1Connected()));
    QObject::connect(m_connectionMonitor.data(), SIGNAL(u1Disconnected()), this, SLOT(onConnectionMonitor_U1Disconnected()));

    QObject::connect(m_pointsMonitor.data(), SIGNAL(pointsUpdated()), this, SLOT(onPointsMonitor_PointsUpdated()));
    QObject::connect(m_sensorsMonitor.data(), SIGNAL(stateChanged(QString,bool)), this, SLOT(onSensorMonitor_StateChanged(QString,bool)));
    QObject::connect(m_spindelsMonitor.data(), SIGNAL(stateChanged(QString,bool,size_t)), this, SLOT(onSpindelsMonitor_StateChanged(QString,bool,size_t)));

    QObject::connect(m_gcodesMonitor.data(), SIGNAL(filePathUpdated(QString)), this, SLOT(onGCodesMonitor_FilePathUpdated(QString)));
    QObject::connect(m_gcodesMonitor.data(), SIGNAL(fileContentUpdated(QString)), this, SLOT(onGCodesMonitor_FileContentUpdated(QString)));
}

void MachineTool::resetConnections()
{
    QObject::disconnect(m_adapterServer.data(), SIGNAL(u1Connected()), this, SLOT(onServer_U1Connected()));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(u1Disconnected()), this, SLOT(onServer_U1Disconnected()));
    QObject::disconnect(m_adapterServer.data(), SIGNAL(u1StateChanged(QList<QVariant>,QList<QVariant>)),
                     this, SLOT(onServer_U1StateChanged(QList<QVariant>,QList<QVariant>)));
    QObject::connect(m_adapterServer.data(), SIGNAL(errorOccured(int)), this, SLOT(onServer_ErrorOccured(int)));

    QObject::disconnect(m_connectionMonitor.data(), SIGNAL(u1Connected()), this, SLOT(onConnectionMonitor_U1Connected()));
    QObject::disconnect(m_connectionMonitor.data(), SIGNAL(u1Disconnected()), this, SLOT(onConnectionMonitor_U1Disconnected()));

    QObject::disconnect(m_pointsMonitor.data(), SIGNAL(pointsUpdated()), this, SLOT(onPointsMonitor_PointsUpdated()));
    QObject::disconnect(m_sensorsMonitor.data(), SIGNAL(stateChanged(QString,bool)), this, SLOT(onSensorMonitor_StateChanged(QString,bool)));
    QObject::disconnect(m_spindelsMonitor.data(), SIGNAL(stateChanged(QString,bool,size_t)), this, SLOT(onSpindelsMonitor_StateChanged(QString,bool,size_t)));

    QObject::disconnect(m_gcodesMonitor.data(), SIGNAL(filePathUpdated(QString)), this, SLOT(onGCodesMonitor_FilePathUpdated(QString)));
    QObject::disconnect(m_gcodesMonitor.data(), SIGNAL(fileContentUpdated(QString)), this, SLOT(onGCodesMonitor_FileContentUpdated(QString)));
}

void MachineTool::onConnectionMonitor_U1Connected()
{
    emit u1Connected();
}

void MachineTool::onConnectionMonitor_U1Disconnected()
{
    emit u1Disconnected();
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

void MachineTool::onServer_ErrorOccured(int errorCode)
{
    this->setLastError(errorCode);
}

void MachineTool::onServer_U1Connected()
{
    m_repository->setU1Connected(true);
}

void MachineTool::onServer_U1Disconnected()
{
    m_repository->setU1Connected(false);
}

void MachineTool::onServer_U1StateChanged(QList<QVariant> sensors, QList<QVariant> devices)
{
    try
    {
        this->m_repository->setU1Sensors(sensors);
        this->m_repository->setU1Devices(devices);
    }
    catch(SynchronizeStateException e)
    {
        qDebug() << "MachineTool::onServer_U1StateChanged:" << e.message();
        this->setLastError(-255);
    }
}

void MachineTool::startAdapterServer()
{
    m_adapterServer->start();
}

void MachineTool::stopAdapterServer()
{
    m_adapterServer->stop();
}

QStringList MachineTool::getConnectedAdapters()
{
    return m_adapterServer->currentAdapters();
}

QString MachineTool::getAdapterServerPort()
{
    return QString::number(m_adapterServer->port());
}

int MachineTool::getLastError()
{
    return m_lastError;
}

void MachineTool::setLastError(int value)
{
    m_lastError = value;
    if(m_lastError != 0)
    {
        // вызов интерактора-обработчика
        emit errorOccured(m_lastError);
    }
}

void MachineTool::switchSpindelOn(QString index, size_t rotations)
{
    if(m_lastError != 0)
    {
        return;
    }

    SwitchSpindel swithcer(m_adapterServer.data(), index, true, rotations);
    swithcer.execute();
}

void MachineTool::switchSpindelOff(QString index)
{
    if(m_lastError != 0)
    {
        return;
    }

    SwitchSpindel switcher(m_adapterServer.data(), index, false);
    switcher.execute();
}
