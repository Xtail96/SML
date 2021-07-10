#include "registrator.h"

Registrator::Registrator(MotionController *m, DeviceController *d, QObject *parent) :
    BaseController("Registrator", parent),
    m_connections()
{
    m_connections.append(QObject::connect(this, &Registrator::MotionAdapterConnected, this, [=](QWebSocket* s, QtJson::JsonObject initialState) {
        qInfo() << "Try to connect" << s << "as a client to motion controller";
        m->addClient(s, initialState);
        this->clearClients();
        s->sendTextMessage("Registered!");
    }));

    m_connections.append(QObject::connect(this, &Registrator::DeviceAdapterConnected, this, [=](QWebSocket* s, QtJson::JsonObject initialState) {
        qInfo() << "Try to connect" << s << "as a client to device controller";
        d->addClient(s, initialState);
        this->clearClients();
        m_clients.clear();
        s->sendTextMessage("Registered!");
    }));
}

Registrator::~Registrator()
{
    for(auto connection : m_connections)
    {
        QObject::disconnect(connection);
    }
}

void Registrator::processTask(Task) {}

void Registrator::stopProcessing() {}

void Registrator::setup(QtJson::JsonObject) {}

void Registrator::newMessageHandler(QtJson::JsonObject msg)
{
    qInfo().noquote() << "Received" << QtJson::serializeStr(msg);
    QWebSocket* pSender = qobject_cast<QWebSocket *>(sender());
    if (!pSender) return;

    QtJson::JsonObject deviceController = msg["deviceControllerState"].toMap();
    QtJson::JsonObject motionController = msg["motionControllerState"].toMap();

    if(!deviceController.isEmpty())
    {
        emit this->DeviceAdapterConnected(pSender, msg);
    }

    if(!motionController.isEmpty())
    {
        emit this->MotionAdapterConnected(pSender, msg);
    }

    if(deviceController.isEmpty() && motionController.isEmpty())
    {
        qWarning() << "Connection refused";
        pSender->sendTextMessage("Connection refused");
        pSender->close();
        this->clearClients();
    }
}

void Registrator::clearClients()
{
    qInfo() << "Clear slots info";
    for(auto client : m_clients)
    {
        client->clearSlotsInfo();
    }
    qInfo() << "Clear clients";
    m_clients.clear();
}
