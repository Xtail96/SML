#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>

#include "../../controllers/base_controller.h"
#include "./sensors_repository.h"

class DeviceController : public BaseController
{
    Q_OBJECT
public:
    explicit DeviceController(QObject *parent = nullptr);
    ~DeviceController() override;
    void processTask(Task t) override;
    void stopProcessing() override;
    void onClientConnected(QtJson::JsonObject initialState) override;
    void onMessageReceived(QtJson::JsonObject msg) override;
    void onDisconnected() override;
private:
    const QString m_controllerName = "deviceController";
    SensorsRepository m_sensors;
signals:
    void sensorStateChanged(Sensor s);
friend class HardwareDriver;
};

#endif // DEVICECONTROLLER_H
