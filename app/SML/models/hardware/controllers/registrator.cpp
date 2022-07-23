#include "registrator.h"

Registrator::Registrator(MotionController *m, DeviceController *d, QObject *parent) :
    WebSocketAdapter(parent),
    m_connections()
{
    m_connections.append(QObject::connect(this, &Registrator::motionControllerConnected, this, [=](QWebSocket* s, QtJson::JsonObject initialState) {
        qInfo() << "Try to register" << s << "as a motion controller";
        m->createClient(s, initialState);
        this->removeRegisteredClients();
        s->sendTextMessage("Registered");
    }));

    m_connections.append(QObject::connect(this, &Registrator::deviceControllerConnected, this, [=](QWebSocket* s, QtJson::JsonObject initialState) {
        qInfo() << "Try to register" << s << "as a device controller";
        d->createClient(s, initialState);
        this->removeRegisteredClients();
        s->sendTextMessage("Registered");
    }));
}

Registrator::~Registrator()
{
    for(auto connection : m_connections)
        QObject::disconnect(connection);
}

void Registrator::removeRegisteredClients()
{
    qInfo() << "Remove registered clients from clients list";
    for(auto client : m_clients)
        client->clearSlotsInfo();
    m_clients.clear();
}

void Registrator::onClientConnected(QtJson::JsonObject)
{

}

void Registrator::onMessageReceived(QtJson::JsonObject msg)
{
    qInfo().noquote() << "Received" << QtJson::serializeStr(msg);
    QWebSocket* pSender = qobject_cast<QWebSocket *>(sender());
    if (!pSender) return;

    QtJson::JsonObject deviceController = msg["deviceControllerState"].toMap();
    QtJson::JsonObject motionController = msg["motionControllerState"].toMap();

    if(!deviceController.isEmpty())
        emit this->deviceControllerConnected(pSender, msg);

    if(!motionController.isEmpty())
        emit this->motionControllerConnected(pSender, msg);

    if(deviceController.isEmpty() && motionController.isEmpty())
    {
        qWarning() << "Connection refused";
        pSender->sendTextMessage("Connection refused");
        pSender->close();
        this->clearClients();
    }
}
