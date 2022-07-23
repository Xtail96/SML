#ifndef REGISTRATOR_H
#define REGISTRATOR_H

#include <QObject>

#include "../controllers/motion_controller/motion_controller.h"
#include "../controllers/device_controller/device_controller.h"
#include "./websocket_adapter.h"


class Registrator : public WebSocketAdapter
{
    Q_OBJECT
public:
    explicit Registrator(MotionController* m, DeviceController* d, QObject *parent = nullptr);
    ~Registrator() override;

private:
    QList<QMetaObject::Connection> m_connections;
    void removeRegisteredClients();
    void onClientConnected(QtJson::JsonObject) override;
    void newMessageHandler(QtJson::JsonObject msg) override;
signals:
    void motionAdapterConnected(QWebSocket* s, QtJson::JsonObject initialState);
    void deviceAdapterConnected(QWebSocket* s, QtJson::JsonObject initialState);

};

#endif // REGISTRATOR_H
