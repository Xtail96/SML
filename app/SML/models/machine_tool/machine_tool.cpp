#include "machine_tool.h"

MachineTool::MachineTool(QObject *parent) :
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

MachineTool::~MachineTool()
{
    this->stopAdapters();
    this->resetConnections();
}

MachineTool &MachineTool::getInstance()
{
    static QScopedPointer<MachineTool> m_instance;
    if(m_instance.data() == nullptr)
    {
        m_instance.reset( new MachineTool() );
    }
    return *m_instance;
}

void MachineTool::setupConnections()
{
    this->resetConnections();

    m_connections.append(QObject::connect(&m_adapterServer, &AdapterGateway::newConnection, this, [=](QWebSocket* client) {
        m_adapterRegistrator.addClient(client);
    }));
}

void MachineTool::resetConnections()
{
    for(auto& connection : m_connections)
    {
        QObject::disconnect(connection);
    }
}

void MachineTool::stopAdapters()
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

void MachineTool::launchAdapters()
{
    SettingsManager s;
    QString deviceAdapterPath = s.get("ExternalTools", "DeviceAdapter").toString();
    QString motionAdapterPath = s.get("ExternalTools", "MotionAdapter").toString();

    m_adaptersLauncher.startAdapters(deviceAdapterPath, motionAdapterPath);
}
