#include "hardware_driver.h"

HardwareDriver::HardwareDriver(QObject *parent) :
    QObject(parent),
    m_connections(QList<QMetaObject::Connection>()),
    m_adapterServer(this),
    m_motionController(this),
    m_deviceController(this),
    m_adapterRegistrator(&m_motionController, &m_deviceController, this),
    m_adaptersLauncher(new AdaptersLauncher(this))
{
    this->setupConnections();

    SettingsManager s;
    quint16 port = quint16(s.get("ServerSettings", "ServerPort").toInt());
    m_adapterServer.open(port);
    this->launchAdapters();
}

HardwareDriver::~HardwareDriver()
{
    this->stopAdapters();
    this->resetConnections();
}

HardwareDriver &HardwareDriver::getInstance()
{
    static QScopedPointer<HardwareDriver> m_instance;
    if(m_instance.data() == nullptr)
    {
        m_instance.reset( new HardwareDriver() );
    }
    return *m_instance;
}

void HardwareDriver::setupConnections()
{
    this->resetConnections();

    m_connections.append(QObject::connect(&m_adapterServer, &AdapterGateway::newConnection, this, [=](QWebSocket* client) {
        m_adapterRegistrator.addClient(client);
    }));
}

void HardwareDriver::resetConnections()
{
    for(auto& connection : m_connections)
    {
        QObject::disconnect(connection);
    }
}

void HardwareDriver::stopAdapters()
{
    try
    {
        m_adaptersLauncher.stopAdapters();
    }
    catch(...)
    {
        qDebug() << QStringLiteral("MachineTool::stopAdapters: unknown error");
    }
}

void HardwareDriver::launchAdapters()
{
    SettingsManager s;
    QString deviceAdapterPath = s.get("ExternalTools", "DeviceAdapter").toString();
    QString motionAdapterPath = s.get("ExternalTools", "MotionAdapter").toString();

    m_adaptersLauncher.startAdapters(deviceAdapterPath, motionAdapterPath);
}