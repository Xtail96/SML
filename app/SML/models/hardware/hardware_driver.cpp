#include "hardware_driver.h"

HardwareDriver::HardwareDriver(QObject *parent) :
    QObject(parent),
    m_systemSlotsInfo(QList<QMetaObject::Connection>()),
    m_userSlotsInfo(QList<QMetaObject::Connection>()),
    m_adapterServer(this),
    m_motionController(this),
    m_deviceController(this),
    m_adapterRegistrator(&m_motionController, &m_deviceController, this)
{
    this->setupSystemSlots();

    SettingsManager s;
    quint16 port = quint16(s.get("AdapterServer", "Port").toInt());
    m_adapterServer.open(port);
}

HardwareDriver::~HardwareDriver()
{
    this->resetSystemSlots();
    this->resetHandlers();
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

void HardwareDriver::setupSystemSlots()
{
    this->resetSystemSlots();

    m_systemSlotsInfo.append(QObject::connect(&m_adapterServer, &AdapterGateway::newConnection, this, [=](QWebSocket* client) {
        m_adapterRegistrator.addClient(client, QtJson::JsonObject());
    }));
}

void HardwareDriver::resetSystemSlots()
{
    for(auto& slotInfo : m_systemSlotsInfo)
    {
        QObject::disconnect(slotInfo);
    }
    m_systemSlotsInfo.clear();
}

void HardwareDriver::registerHandler(HARDWARE_EVENT event, const std::function<void()> &handler)
{
    switch (event) {
    case HARDWARE_EVENT::DeviceControllerConnected:
        m_userSlotsInfo.append(QObject::connect(&m_deviceController, &BaseController::connected, this, [=]() {
            handler();
        }));
        break;
    case HARDWARE_EVENT::DeviceControllerDisconnected:
        m_userSlotsInfo.append(QObject::connect(&m_deviceController, &BaseController::disconnected, this, [=]() {
            handler();
        }));
        break;
    case HARDWARE_EVENT::MotionControllerConnected:
        m_userSlotsInfo.append(QObject::connect(&m_motionController, &BaseController::connected, this, [=]() {
            handler();
        }));
        break;
    case HARDWARE_EVENT::MotionControllerDisconnected:
        m_userSlotsInfo.append(QObject::connect(&m_motionController, &BaseController::disconnected, this, [=]() {
            handler();
        }));
        break;
    case HARDWARE_EVENT::CurrentPositionChanged:
        m_userSlotsInfo.append(QObject::connect(&m_motionController, &MotionController::positionChanged, this, [=]() {
            handler();
        }));
    default:
        break;
    }
}

void HardwareDriver::resetHandlers()
{
    for(auto& slotInfo : m_userSlotsInfo)
    {
        QObject::disconnect(slotInfo);
    }
    m_systemSlotsInfo.clear();
}

MotionControllerRepository &HardwareDriver::getMotionController()
{
    return m_motionController.m_repository;
}

void HardwareDriver::moveTo(QMap<AxisId, double> absPos)
{
    QStringList gcode = {};

    gcode.append("G0");
    for(auto key : absPos.keys())
    {
        gcode.append(Axis::decorateId(key) + QString::number(absPos.value(key)));
    }

    Task t(gcode.join(" "));
    m_motionController.processTask(t);
}

void HardwareDriver::moveOffset(QMap<AxisId, double> relPos)
{
    QMap<AxisId, double> absPos = {};
    for(auto key : relPos.keys())
    {
        if(!m_motionController.m_repository.axisExists(key)) continue;

        absPos.insert(key, m_motionController.m_repository.axis(key)->currentPositionFromBase() +
                      relPos.value(key));
    }

    if(absPos.isEmpty()) return;
    this->moveTo(absPos);
}
