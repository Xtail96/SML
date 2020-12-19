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

    void processTask(Task) override;
private:
    QList<QMetaObject::Connection> m_connections;

    void setup(QtJson::JsonObject) override;

    void newMessageHandler(QtJson::JsonObject msg) override;

    void clearClients();

signals:
    void MotionAdapterConnected(QWebSocket* s, QtJson::JsonObject initialState);
    void DeviceAdapterConnected(QWebSocket* s, QtJson::JsonObject initialState);

};

#endif // REGISTRATOR_H
