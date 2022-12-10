#include "device_controller.h"

DeviceController::DeviceController(QObject *parent) :
    BaseController(parent)
{
}

DeviceController::~DeviceController()
{
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
        bool enabled = sensorJson["enabled"].toBool();
        QColor ledColor = sensorJson["ledColor"].toString();

        if(m_sensors.exists(id))
            continue;
        m_sensors.add(Sensor(id, enabled, label, ledColor));
    }

    /*QtJson::JsonArray spindels = deviceController["spindels"].toList();
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
        m_spindels.insert(new Spindel(id, label, id, activeState, lowerBound, upperBound, this));
        this->getSpindel(id)->update(isEnable, currentRotations);
    }*/

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
        bool enabled = sensorJson["enabled"].toBool();

        if(!m_sensors.exists(id))
        {
            qWarning() << "Unknown sensor" << id;
            continue;
        }

        auto& sensor = m_sensors.get(id);
        if(sensor.enabled() == enabled)
            continue;
        sensor.setEnabled(enabled);
        emit this->sensorStateChanged(sensor);
    }

    /*QtJson::JsonArray spindels = deviceController["spindels"].toList();
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
        this->getSpindel(id)->update(isEnable, currentRotations);
    }*/

    this->setProcessingTask(deviceController["workflowState"].toBool());
}

void DeviceController::onDisconnected()
{
    m_sensors.clear();
}
