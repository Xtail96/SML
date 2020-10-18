#include "registrator.h"

Registrator::Registrator(MotionController *m, DeviceController *d, QObject *parent) :
    BaseController("Registrator", parent),
    m_connections()
{
    m_connections.append(QObject::connect(this, &Registrator::MotionAdapterConnected, this, [=](QWebSocket* s) {
        qDebug().noquote() << m_logName << "try to connect" << s << "as a client to motion controller";
        m->addClient(s);
        qDebug().noquote() << m_logName << "clear" << s << "slots info";
        for(auto client : m_clients)
        {
            client->clearSlotsInfo();
        }
        qDebug().noquote() << m_logName << "clear clients";
        m_clients.clear();
        s->sendTextMessage("Registered!");
    }));

    m_connections.append(QObject::connect(this, &Registrator::DeviceAdapterConnected, this, [=](QWebSocket* s) {
        qDebug().noquote() << m_logName << "try to connect" << s << "as a client to device controller";
        d->addClient(s);
        qDebug().noquote() << m_logName << "clear" << s << "slots info";
        for(auto client : m_clients)
        {
            client->clearSlotsInfo();
        }
        qDebug().noquote() << m_logName << "clear clients";
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
    qDebug().noquote() << m_logName << "binary message received" << message;
}

void Registrator::parseTextMessage(QString message)
{
    qDebug().noquote() << m_logName << "text message received" << message;

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
            qDebug().noquote() << m_logName << e.what();
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
                qDebug().noquote() << m_logName << e.what();
                delete pSender;
            }
        }
        else
        {
            qDebug().noquote() << m_logName << "connection refused";
            pSender->sendTextMessage("Connection refused");
            pSender->close();
        }
    }

}
