#include "hardware_driver.h"

HardwareDriver::HardwareDriver(QObject *parent) :
    QObject(parent),
    m_slotsInfo(QList<QMetaObject::Connection>()),
    m_adapterServer(this),
    m_motionController(this),
    m_deviceController(this),
    m_adapterRegistrator(&m_motionController, &m_deviceController, this),
    m_adaptersLauncher(new AdaptersLauncher(this))
{
    this->setupSlots();

    SettingsManager s;
    quint16 port = quint16(s.get("ServerSettings", "ServerPort").toInt());
    m_adapterServer.open(port);
    this->launchAdapters();
}

HardwareDriver::~HardwareDriver()
{
    this->stopAdapters();
    this->resetSlots();
}

bool HardwareDriver::isConnected() const
{
    return m_deviceController.isConnected() && m_motionController.isConnected();
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

void HardwareDriver::setupSlots()
{
    this->resetSlots();

    m_slotsInfo.append(QObject::connect(&m_adapterServer, &AdapterGateway::newConnection, this, [=](QWebSocket* client) {
        m_adapterRegistrator.addClient(client);
    }));
}

void HardwareDriver::resetSlots()
{
    for(auto& slotInfo : m_slotsInfo)
    {
        QObject::disconnect(slotInfo);
    }
    m_slotsInfo.clear();
}

QMetaObject::Connection HardwareDriver::registerHandler(HARDWARE_EVENT event, const std::function<void()> &handler)
{
    QMetaObject::Connection slotInfo = QMetaObject::Connection();
    switch (event) {
    case HARDWARE_EVENT::DeviceControllerConnectionStateChanged:
        slotInfo = QObject::connect(&m_deviceController, &BaseController::connectionStateChanged, this, [=]() {
            handler();
        });
        break;
    case HARDWARE_EVENT::MotionControllerConnectionStateChanged:
        slotInfo = QObject::connect(&m_motionController, &BaseController::connectionStateChanged, this, [=]() {
            handler();
        });
        break;
    default:
        break;
    }

    m_slotsInfo.append(slotInfo);
    return slotInfo;
}

void HardwareDriver::unregisterHandler(QMetaObject::Connection slotInfo)
{
    m_slotsInfo.removeAll(slotInfo);
    QObject::disconnect(slotInfo);
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
