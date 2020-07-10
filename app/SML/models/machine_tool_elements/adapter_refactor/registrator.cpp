#include "registrator.h"

Registrator::Registrator(MotionController *m, DeviceController *d, QObject *parent) :
    BaseController(parent),
    m_connections()
{
    m_connections.append(QObject::connect(this, &Registrator::MotionAdapterConnected, this, [=](QWebSocket* s) {
        m->addClient(s);
    }));

    m_connections.append(QObject::connect(this, &Registrator::DeviceAdapterConnected, this, [=](QWebSocket* s) {
        d->addClient(s);
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
    qDebug() << "Registrator::binary message received" << message;
}

void Registrator::parseTextMessage(QString message)
{
    qDebug() << "Registrator::text message received" << message;
}
