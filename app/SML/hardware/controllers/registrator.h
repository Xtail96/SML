#ifndef REGISTRATOR_H
#define REGISTRATOR_H

#include <QObject>

#include "./motion_controller/motion_controller.h"
#include "./device_controller/device_controller.h"
#include "../../common/websockets/websocket_client.h"


class Registrator : public WebSocketClient
{
    Q_OBJECT
public:
    explicit Registrator(MotionController* m, DeviceController* d, QObject *parent = nullptr);
    ~Registrator() override;

private:
    QList<QMetaObject::Connection> m_slotsInfo;
    void removeRegisteredClients();
    void onClientConnected(QtJson::JsonObject) override;
    void onMessageReceived(QtJson::JsonObject msg) override;
signals:
    void motionControllerConnected(QWebSocket* s, QtJson::JsonObject initialState);
    void deviceControllerConnected(QWebSocket* s, QtJson::JsonObject initialState);

};

#endif // REGISTRATOR_H
