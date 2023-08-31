#include "hardware_driver.h"

HardwareDriver::HardwareDriver(QObject *parent) :
    QObject(parent),
    m_systemSlotsInfo(QList<QMetaObject::Connection>()),
    m_userSlotsInfo(QList<QMetaObject::Connection>()),
    m_adapterServer(this),
    m_motionController(this),
    m_deviceController(this),
    m_controllerRegistrator(&m_motionController, &m_deviceController, this)
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

    m_systemSlotsInfo.append(QObject::connect(&m_adapterServer, &WebSocketGateway::newConnection, this, [=](QWebSocket* client) {
        m_controllerRegistrator.createConnection(client, QtJson::JsonObject());
    }));
}

void HardwareDriver::resetSystemSlots()
{
    for(auto& slotInfo : m_systemSlotsInfo)
        QObject::disconnect(slotInfo);
    m_systemSlotsInfo.clear();
}

void HardwareDriver::registerHandler(HARDWARE_EVENT event, const std::function<void(HARDWARE_EVENT_DATA)> &handler)
{
    switch (event) {
    case HARDWARE_EVENT::DeviceControllerConnected:
        m_userSlotsInfo.append(QObject::connect(&m_deviceController, &BaseController::connected, this, [=]() {
            handler(HARDWARE_EVENT_DATA());
        }));
        break;
    case HARDWARE_EVENT::DeviceControllerDisconnected:
        m_userSlotsInfo.append(QObject::connect(&m_deviceController, &BaseController::disconnected, this, [=]() {
            handler(HARDWARE_EVENT_DATA());
        }));
        break;
    case HARDWARE_EVENT::MotionControllerConnected:
        m_userSlotsInfo.append(QObject::connect(&m_motionController, &BaseController::connected, this, [=]() {
            handler(HARDWARE_EVENT_DATA());
        }));
        break;
    case HARDWARE_EVENT::MotionControllerDisconnected:
        m_userSlotsInfo.append(QObject::connect(&m_motionController, &BaseController::disconnected, this, [=]() {
            handler(HARDWARE_EVENT_DATA());
        }));
        break;
    case HARDWARE_EVENT::CurrentPositionChanged:
        m_userSlotsInfo.append(QObject::connect(&m_motionController, &MotionController::positionChanged, this, [=]() {
            handler(HARDWARE_EVENT_DATA());
        }));
        break;
    case HARDWARE_EVENT::SensorStateChanged:
        m_userSlotsInfo.append(QObject::connect(&m_deviceController, &DeviceController::sensorStateChanged, this, [=](Sensor s) {
            QList<QVariant> signalParams = { s.id(), s.enabled() };
            handler(HARDWARE_EVENT_DATA(signalParams));
        }));
        break;
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

AxesRepository &HardwareDriver::getMotionController()
{
    return m_motionController.m_repository;
}

SensorsRepository &HardwareDriver::getSensors()
{
    return m_deviceController.m_sensors;
}

void HardwareDriver::moveTo(QMap<Axis::Id, double> absPos)
{
    QStringList gcode = {};

    gcode.append("G0");
    for(auto key : absPos.keys())
    {
        gcode.append(Axis::decorateId(key) + QString::number(absPos.value(key)));
    }

    Task t(gcode.join(" "));
    if(!m_motionController.isReady())
        m_motionController.stopProcessing();
    m_motionController.startProcessing(t);
}

void HardwareDriver::moveOffset(QMap<Axis::Id, double> relPos)
{
    QMap<Axis::Id, double> absPos = {};
    for(auto key : relPos.keys())
    {
        if(!m_motionController.m_repository.exists(key))
            continue;

        absPos.insert(key, m_motionController.m_repository.get(key).currentPositionFromBase() +
                      relPos.value(key));
    }

    if(absPos.isEmpty())
        return;
    this->moveTo(absPos);
}

void HardwareDriver::stopMoving()
{
    m_motionController.stopProcessing();
}

bool HardwareDriver::isMoving()
{
    return !m_motionController.isReady();
}
