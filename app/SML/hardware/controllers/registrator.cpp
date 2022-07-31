#include "registrator.h"

Registrator::Registrator(MotionController *m, DeviceController *d, QObject *parent) :
    WebSocketClient(parent),
    m_slotsInfo()
{
    m_slotsInfo.append(QObject::connect(this, &Registrator::motionControllerConnected, this, [=](QWebSocket* s, QtJson::JsonObject initialState) {
        qInfo() << "Try to register" << s << "as a motion controller";
        m->createConnection(s, initialState);
        this->removeRegisteredClients();
        s->sendTextMessage("Registered");
    }));

    m_slotsInfo.append(QObject::connect(this, &Registrator::deviceControllerConnected, this, [=](QWebSocket* s, QtJson::JsonObject initialState) {
        qInfo() << "Try to register" << s << "as a device controller";
        d->createConnection(s, initialState);
        this->removeRegisteredClients();
        s->sendTextMessage("Registered");
    }));
}

Registrator::~Registrator()
{
    for(auto slotInfo : m_slotsInfo)
        QObject::disconnect(slotInfo);
}

void Registrator::removeRegisteredClients()
{
    qInfo() << "Remove registered clients from clients list";
    for(auto connection : m_connections)
        connection->clearSlotsInfo();
    m_connections.clear();
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
        this->clearConnections();
    }
}
