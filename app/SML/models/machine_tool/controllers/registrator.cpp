#include "registrator.h"

Registrator::Registrator(MotionController *m, DeviceController *d, QObject *parent) :
    BaseController(parent),
    m_connections()
{
    m_connections.append(QObject::connect(this, &Registrator::MotionAdapterConnected, this, [=](QWebSocket* s) {
        m->addClient(s);
        for(auto client : m_clients)
        {
            client->clearSlotsInfo();
        }
        m_clients.clear();
        s->sendTextMessage("Registered!");
    }));

    m_connections.append(QObject::connect(this, &Registrator::DeviceAdapterConnected, this, [=](QWebSocket* s) {
        d->addClient(s);
        for(auto client : m_clients)
        {
            client->clearSlotsInfo();
        }
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
    qDebug() << "Registrator::binary message received" << message;
}

void Registrator::parseTextMessage(QString message)
{
    qDebug() << "Registrator::text message received" << message;

    QWebSocket* pSender = qobject_cast<QWebSocket *>(sender());
    if (!pSender) return;

    if(message == "@SML-DeviceAdapter@")
    {
        try
        {
            emit this->DeviceAdapterConnected(pSender);
        }
        catch(SynchronizeStateException e)
        {
            qDebug() << e.message();
            delete pSender;
        }
    }
    else
    {
        if(message == "@SML-MotionAdapter@")
        {
            try
            {
                emit this->MotionAdapterConnected(pSender);
            }
            catch(SynchronizeStateException e)
            {
                qDebug() << e.message();
                delete pSender;
            }
        }
        else
        {
            pSender->sendTextMessage("Connection aborted");
            pSender->close();
        }
    }

}
