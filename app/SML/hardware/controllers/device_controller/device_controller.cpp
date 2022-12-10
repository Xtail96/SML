#include "device_controller.h"

DeviceController::DeviceController(QObject *parent) :
    BaseController(parent),
    m_sensors(),
    m_spindels(),
    m_supportDevices()
{
}

DeviceController::~DeviceController()
{
    qDeleteAll(m_sensors.begin(), m_sensors.end());
    qDeleteAll(m_spindels.begin(), m_spindels.end());
    qDeleteAll(m_supportDevices.begin(), m_supportDevices.end());
}

Sensor* DeviceController::getSensor(QString id)
{
    for(auto sensor : m_sensors) {
        if(sensor->uid() == id)
            return sensor;
    }

    throw std::invalid_argument("Sensor with uid " + id.toStdString() + " does not exists");
}

Spindel *DeviceController::getSpindel(QString id)
{
    for(auto s : m_spindels) {
        if(s->getId() == id)
            return s;
    }

    throw std::invalid_argument("Spindel with uid " + id.toStdString() + " does not exists");
}

SupportDevice *DeviceController::getSupportDevice(QString id)
{
    for(auto d : m_supportDevices) {
        if(d->getId() == id)
            return d;
    }

    throw std::invalid_argument("Device with uid " + id.toStdString() + " does not exists");
}

void DeviceController::processTask(Task t)
{
    qDebug() << t.serialize();
}

void DeviceController::stopProcessing()
{
    this->stopProcessingTask(m_controllerName);
}

void DeviceController::onClientConnected(QtJson::JsonObject initialState)
{
    QtJson::JsonObject deviceController = initialState["deviceControllerState"].toMap();
    if(deviceController.isEmpty())
    {
        qWarning() << "Empty message received";
        return ;
    }

    QtJson::JsonArray sensors = deviceController["sensors"].toList();
    for(auto s : sensors)
    {
        QtJson::JsonObject sensorJson = s.toMap();
        QString id = sensorJson["id"].toString();
        QString label = sensorJson["label"].toString();
        bool activeState = sensorJson["activeState"].toBool();
        bool currentState = sensorJson["currentState"].toBool();
        QColor ledColor = sensorJson["ledColor"].toString();

        if(this->sensorExists(id)) continue;
        m_sensors.insert(new Sensor(id, label, activeState, ledColor, this));
        this->getSensor(id)->setCurrentState(currentState);
    }

    QtJson::JsonArray spindels = deviceController["spindels"].toList();
    for(auto s : spindels)
    {
        QtJson::JsonObject spindelJson = s.toMap();
        QString id = spindelJson["id"].toString();
        QString label = spindelJson["label"].toString();
        bool activeState = spindelJson["activeState"].toBool();
        int lowerBound = spindelJson["lowerBound"].toUInt();
        int upperBound = spindelJson["upperBound"].toUInt();
        size_t currentRotations  = spindelJson["currentRotations"].toULongLong();
        bool isEnable = spindelJson["enable"].toBool();

        if(this->spindelExists(id))
            continue;
        //m_spindels.insert(new Spindel(id, label, id, activeState, lowerBound, upperBound, this));
        //this->getSpindel(id)->update(isEnable, currentRotations);
    }

    this->setProcessingTask(deviceController["workflowState"].toBool());
}

void DeviceController::onMessageReceived(QtJson::JsonObject msg)
{
    QtJson::JsonObject deviceController = msg["deviceControllerState"].toMap();
    if(deviceController.isEmpty())
    {
        qWarning() << "Empty message received";
        return ;
    }

    QtJson::JsonArray sensors = deviceController["sensors"].toList();
    for(auto s : sensors)
    {
        QtJson::JsonObject sensorJson = s.toMap();
        QString id = sensorJson["id"].toString();
        bool currentState = sensorJson["currentState"].toBool();

        if(!this->sensorExists(id)) { qWarning() << "Unknown sensor" << id; continue; }
        this->getSensor(id)->setCurrentState(currentState);
    }

    QtJson::JsonArray spindels = deviceController["spindels"].toList();
    for(auto s : spindels)
    {
        QtJson::JsonObject spindelJson = s.toMap();
        QString id = spindelJson["id"].toString();
        size_t currentRotations  = spindelJson["currentRotations"].toULongLong();
        bool isEnable = spindelJson["enable"].toBool();

        if(!this->spindelExists(id))
        {
            qWarning() << "Unknow spindel" << id;
            continue;
        }
        //this->getSpindel(id)->update(isEnable, currentRotations);
    }

    this->setProcessingTask(deviceController["workflowState"].toBool());
}

bool DeviceController::sensorExists(QString id)
{
    for(auto sensor : m_sensors)
    {
       if(sensor->uid() == id)
           return true;
    }

    return false;
}

bool DeviceController::spindelExists(QString id)
{
    for(auto spindel : m_spindels)
    {
       if(spindel->getId() == id)
           return true;
    }

    return false;
}
