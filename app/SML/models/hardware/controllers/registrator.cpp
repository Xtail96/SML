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

void Registrator::parseBinaryMessage(QByteArray message)
{
    this->parseTextMessage(QString::fromUtf8(message));
}

void Registrator::parseTextMessage(QString message)
{
    qInfo().noquote() << "Received" << message;
    QWebSocket* pSender = qobject_cast<QWebSocket *>(sender());
    if (!pSender) return;

    QtJson::JsonObject messageData = QtJson::parse(message).toMap();
    QtJson::JsonObject deviceController = messageData["deviceControllerState"].toMap();
    QtJson::JsonObject motionController = messageData["motionControllerState"].toMap();

    if(!deviceController.isEmpty())
    {
        emit this->DeviceAdapterConnected(pSender, messageData);
    }

    if(!motionController.isEmpty())
    {
        emit this->MotionAdapterConnected(pSender, messageData);
    }

    if(deviceController.isEmpty() && motionController.isEmpty())
    {
        qWarning() << "Connection refused";
        pSender->sendTextMessage("Connection refused");
        pSender->close();
        this->clearClients();
    }
}

void Registrator::setup(QtJson::JsonObject) {}

void Registrator::newMessageHandler(QtJson::JsonObject) {}

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
