#ifndef REGISTRATOR_H
#define REGISTRATOR_H

#include <QObject>

#include "models/machine_tool_elements/controllers/motion_controller.h"
#include "models/machine_tool_elements/controllers/device_controller.h"


class Registrator : public BaseController
{
    Q_OBJECT
public:
    explicit Registrator(MotionController* m, DeviceController* d, QObject *parent = nullptr);
    ~Registrator() override;
private:
    QList<QMetaObject::Connection> m_connections;

    /**
     * @brief Обработчик сообщения в виде массива байт.
     * @param message - принятое сообщение от адаптера
     */
    void parseBinaryMessage(QByteArray message) override;

    /**
     * @brief Обработчик сообщения в виде текста.
     * @param message - принятое сообщение от адаптера
     */
    void parseTextMessage(QString message) override;

signals:
    void MotionAdapterConnected(QWebSocket* s);
    void DeviceAdapterConnected(QWebSocket* s);

};

#endif // REGISTRATOR_H
