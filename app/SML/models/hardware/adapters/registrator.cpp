#include "registrator.h"

Registrator::Registrator(MotionController *m, DeviceController *d, QObject *parent) :
    WebSocketAdapter(parent),
    m_connections()
{
    m_connections.append(QObject::connect(this, &Registrator::motionAdapterConnected, this, [=](QWebSocket* s, QtJson::JsonObject initialState) {
        qInfo() << "Try to connect" << s << "as a client to motion controller";
        m->addClient(s, initialState);
        this->removeRegisteredClients();
        s->sendTextMessage("Registered!");
    }));

    m_connections.append(QObject::connect(this, &Registrator::deviceAdapterConnected, this, [=](QWebSocket* s, QtJson::JsonObject initialState) {
        qInfo() << "Try to connect" << s << "as a client to device controller";
        d->addClient(s, initialState);
        this->removeRegisteredClients();
        s->sendTextMessage("Registered!");
    }));
}

Registrator::~Registrator()
{
    for(auto connection : m_connections)
        QObject::disconnect(connection);
}

void Registrator::removeRegisteredClients()
{
    qInfo() << "Clear adapters candidate list";
    for(auto client : m_clients)
        client->clearSlotsInfo();
    m_clients.clear();
}

void Registrator::onClientConnected(QtJson::JsonObject)
{

}

void Registrator::newMessageHandler(QtJson::JsonObject msg)
{
    qInfo().noquote() << "Received" << QtJson::serializeStr(msg);
    QWebSocket* pSender = qobject_cast<QWebSocket *>(sender());
    if (!pSender) return;

    QtJson::JsonObject deviceController = msg["deviceControllerState"].toMap();
    QtJson::JsonObject motionController = msg["motionControllerState"].toMap();

    if(!deviceController.isEmpty())
        emit this->deviceAdapterConnected(pSender, msg);

    if(!motionController.isEmpty())
        emit this->motionAdapterConnected(pSender, msg);

    if(deviceController.isEmpty() && motionController.isEmpty())
    {
        qWarning() << "Connection refused";
        pSender->sendTextMessage("Connection refused");
        pSender->close();
        this->clearClients();
    }
}
