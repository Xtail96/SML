#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>

#include "../../controllers/base_controller.h"
#include "../../controllers/device_controller/sensor/sensor.h"
#include "../../controllers/device_controller/device/spindel.h"
#include "../../controllers/device_controller/device/support_device.h"

class DeviceController : public BaseController
{
    Q_OBJECT
public:
    explicit DeviceController(QObject *parent = nullptr);
    ~DeviceController() override;

    Sensor *getSensor(QString uid);
    Spindel *getSpindel(QString uid);
    SupportDevice *getSupportDevice(QString uid);

    void processTask(Task t) override;
    void stopProcessing() override;
private:
    const QString m_controllerName = "deviceController";
    QSet<Sensor*> m_sensors;
    QSet<Spindel*> m_spindels;
    QSet<SupportDevice*> m_supportDevices;

    void onClientConnected(QtJson::JsonObject initialState) override;

    void onMessageReceived(QtJson::JsonObject msg) override;

    // нужно сделать нормальную проверку на существование датчиков
    void parseSensors(const QtJson::JsonArray &sensors);

    // нужно сделать нормальную проверку на существование устройств
    void parseSpindels(const QtJson::JsonArray &spindels);

    bool sensorExists(QString id);
    bool spindelExists(QString id);
};

#endif // DEVICECONTROLLER_H
