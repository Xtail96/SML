#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>

#include "models/machine_tool_elements/controllers/base_controller.h"
#include "models/machine_tool_elements/sensor/sensor.h"
#include "models/machine_tool_elements/device/spindel.h"
#include "models/machine_tool_elements/device/support_device.h"

class DeviceController : public BaseController
{
    Q_OBJECT
public:
    explicit DeviceController(QObject *parent = nullptr);
    ~DeviceController() override;

    Sensor *getSensor(QString uid);
    Spindel *getSpindel(QString uid);
    SupportDevice *getSupportDevice(QString uid);

private:
    QSet<Sensor*> m_sensors;
    QSet<Spindel*> m_spindels;
    QSet<SupportDevice*> m_supportDevices;

    /**
     * @brief Обработчик сообщения от адаптера в виде массива байт.
     * @param message - принятое сообщение от адаптера
     */
    void parseBinaryMessage(QByteArray message) override;

    // нужно сделать нормальную проверку на существование датчиков
    void parseSensors(const QtJson::JsonArray &sensors);

    // нужно сделать нормальную проверку на существование устройств
    void parseSpindels(const QtJson::JsonArray &spindels);

    /**
     * @brief Обработчик сообщения от адаптера в виде текста.
     * @param message - принятое сообщение от адаптера
     */
    void parseTextMessage(QString message) override;

signals:

};

#endif // DEVICECONTROLLER_H
