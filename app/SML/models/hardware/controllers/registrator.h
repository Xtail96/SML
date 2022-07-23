#ifndef REGISTRATOR_H
#define REGISTRATOR_H

#include <QObject>

#include "./motion_controller/motion_controller.h"
#include "./device_controller/device_controller.h"
#include "./adapters/adapter_message_handler.h"


class Registrator : public AdapterMessageHandler
{
    Q_OBJECT
public:
    explicit Registrator(MotionController* m, DeviceController* d, QObject *parent = nullptr);
    ~Registrator() override;

private:
    QList<QMetaObject::Connection> m_connections;
    void clearAwaitedClients();
    void onClientConnected(QtJson::JsonObject) override;
    void newMessageHandler(QtJson::JsonObject msg) override;
signals:
    void motionAdapterConnected(QWebSocket* s, QtJson::JsonObject initialState);
    void deviceAdapterConnected(QWebSocket* s, QtJson::JsonObject initialState);

};

#endif // REGISTRATOR_H
