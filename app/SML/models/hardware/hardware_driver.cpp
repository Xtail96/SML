#include "hardware_driver.h"

HardwareDriver::HardwareDriver(QObject *parent) :
    QObject(parent),
    m_slotsInfo(QList<QMetaObject::Connection>()),
    m_adapterServer(this),
    m_motionController(this),
    m_deviceController(this),
    m_adapterRegistrator(&m_motionController, &m_deviceController, this)
{
    this->setupSlots();

    SettingsManager s;
    quint16 port = quint16(s.get("ServerSettings", "ServerPort").toInt());
    m_adapterServer.open(port);
}

HardwareDriver::~HardwareDriver()
{
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
        m_adapterRegistrator.addClient(client, QtJson::JsonObject());
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

void HardwareDriver::registerHandler(HARDWARE_EVENT event, const std::function<void()> &handler)
{
    switch (event) {
    case HARDWARE_EVENT::DeviceControllerConnected:
        m_slotsInfo.append(QObject::connect(&m_deviceController, &BaseController::connected, this, [=]() {
            handler();
        }));
        break;
    case HARDWARE_EVENT::DeviceControllerDisconnected:
        m_slotsInfo.append(QObject::connect(&m_deviceController, &BaseController::disconnected, this, [=]() {
            handler();
        }));
        break;
    case HARDWARE_EVENT::MotionControllerConnected:
        m_slotsInfo.append(QObject::connect(&m_motionController, &BaseController::connected, this, [=]() {
            handler();
        }));
        break;
    case HARDWARE_EVENT::MotionControllerDisconnected:
        m_slotsInfo.append(QObject::connect(&m_motionController, &BaseController::disconnected, this, [=]() {
            handler();
        }));
        break;
    default:
        break;
    }
}

void HardwareDriver::resetHandlers()
{
    this->resetSlots();
    this->setupSlots();
}
