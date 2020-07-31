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

Sensor* DeviceController::getSensor(QString uid)
{
    for(auto sensor : m_sensors) {
        if(sensor->uid() == uid)
            return sensor;
    }

    throw std::invalid_argument("Sensor with uid " + uid.toStdString() + " does not exists");
}

Spindel *DeviceController::getSpindel(QString uid)
{
    for(auto s : m_spindels) {
        if(s->getUid() == uid)
            return s;
    }

    throw std::invalid_argument("Spindel with uid " + uid.toStdString() + " does not exists");
}

SupportDevice *DeviceController::getSupportDevice(QString uid)
{
    for(auto d : m_supportDevices) {
        if(d->getUid() == uid)
            return d;
    }

    throw std::invalid_argument("Device with uid " + uid.toStdString() + " does not exists");
}

void DeviceController::parseBinaryMessage(QByteArray message)
{
    qDebug() << "DeviceController::binary message received" << QString::fromUtf8(message);

    bool parsed = false;
    QtJson::JsonObject result = QtJson::parse(QString::fromUtf8(message), parsed).toMap();
    if(!parsed)
    {
        qDebug() << "DeviceController::binaryMessageReceived: an error is occurred during parsing json" << QString::fromUtf8(message) << "." << "Message Ignored";
        return;
    }

    QtJson::JsonObject deviceController = result["deviceControllerState"].toMap();
    if(deviceController.isEmpty())
    {
        qDebug() << "DeviceController::binaryMessageReceived: empty message";
        return ;
    }

    this->parseSensors(deviceController["sensors"].toList());
    this->parseSpindels(deviceController["spindels"].toList());
    this->setProcessingTask(deviceController["workflowState"].toBool());
}

void DeviceController::parseSensors(const QtJson::JsonArray &sensors)
{
    for(auto s : sensors)
    {
        QtJson::JsonObject sensorJson = s.toMap();
        QString id = sensorJson["id"].toString();
        bool input = sensorJson["input"].toBool();
        try
        {
            this->getSensor(id)->setInputState(input);
        }
        catch(std::invalid_argument e)
        {
            // create new sensor;
        }
    }
}

void DeviceController::parseSpindels(const QtJson::JsonArray &spindels)
{
    for(auto s : spindels)
    {
        QtJson::JsonObject spindelJson = s.toMap();
        QString id = spindelJson["id"].toString();
        size_t currentRotations  = spindelJson["rotations"].toULongLong();
        bool isEnable = spindelJson["enable"].toBool();
        try
        {
           this->getSpindel(id)->update(isEnable, currentRotations);
        }
        catch(std::invalid_argument e)
        {
            // create new spindel
        }
    }
}

void DeviceController::parseTextMessage(QString message)
{
    qDebug() << "DeviceController::text message received" << message;
}
