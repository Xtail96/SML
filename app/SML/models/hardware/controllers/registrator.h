#ifndef REGISTRATOR_H
#define REGISTRATOR_H

#include <QObject>

#include "./motion_controller/motion_controller.h"
#include "./device_controller/device_controller.h"


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

    void setup(QtJson::JsonObject) override;

    void newMessageHandler(QtJson::JsonObject) override;

    void clearClients();

signals:
    void MotionAdapterConnected(QWebSocket* s, QtJson::JsonObject initialState);
    void DeviceAdapterConnected(QWebSocket* s, QtJson::JsonObject initialState);

};

#endif // REGISTRATOR_H
