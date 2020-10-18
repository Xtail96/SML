#include "registrator.h"

Registrator::Registrator(MotionController *m, DeviceController *d, QObject *parent) :
    BaseController(parent),
    m_connections()
{
    m_connections.append(QObject::connect(this, &Registrator::MotionAdapterConnected, this, [=](QWebSocket* s) {
        qDebug() << "Registrator: try to connect" << s << "as a client to motion controller";
        m->addClient(s);
        qDebug() << "Registrator: clear" << s << "slots info";
        for(auto client : m_clients)
        {
            client->clearSlotsInfo();
        }
        qDebug() << "Registrator: clear clients";
        m_clients.clear();
        s->sendTextMessage("Registered!");
    }));

    m_connections.append(QObject::connect(this, &Registrator::DeviceAdapterConnected, this, [=](QWebSocket* s) {
        qDebug() << "Registrator: try to connect" << s << "as a client to device controller";
        d->addClient(s);
        qDebug() << "Registrator: clear" << s << "slots info";
        for(auto client : m_clients)
        {
            client->clearSlotsInfo();
        }
        qDebug() << "Registrator: clear clients";
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
    qDebug() << "Registrator: binary message received" << message;
}

void Registrator::parseTextMessage(QString message)
{
    qDebug() << "Registrator: text message received" << message;

    QWebSocket* pSender = qobject_cast<QWebSocket *>(sender());
    if (!pSender) return;

    if(message == "@SML-DeviceAdapter@")
    {
        try
        {
            emit this->DeviceAdapterConnected(pSender);
        }
        catch(std::runtime_error e)
        {
            qDebug() << e.what();
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
            catch(std::runtime_error e)
            {
                qDebug() << e.what();
                delete pSender;
            }
        }
        else
        {
            qDebug() << "Registrator: connection refused";
            pSender->sendTextMessage("Connection refused");
            pSender->close();
        }
    }

}
