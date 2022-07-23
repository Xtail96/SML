#include "adapter_message_handler.h"

AdapterMessageHandler::AdapterMessageHandler(QObject *parent):
    QObject(parent),
    m_clients()
{

}

AdapterMessageHandler::~AdapterMessageHandler()
{
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void AdapterMessageHandler::addClient(QWebSocket *s, QtJson::JsonObject intialState)
{
    qInfo().noquote() << "Connection from" << s << "is requested.";
    if(m_clients.length() > 0)
    {
        if(s->isValid())
            s->sendTextMessage("Connection refused");

        s->close();
        s->deleteLater();

        qWarning().noquote() << "Already have a client." << s << "disconnected";
        return;
    }

    AdapterConnection* newClient = new AdapterConnection(s);
    newClient->addSlotInfo(QObject::connect(s, &QWebSocket::textMessageReceived, this, [=](QString message){
        this->parseTextMessage(message);
    }));

    newClient->addSlotInfo(QObject::connect(s, &QWebSocket::binaryMessageReceived, this, [=](QByteArray message) {
        this->parseBinaryMessage(message);
    }));

    newClient->addSlotInfo(QObject::connect(s, &QWebSocket::disconnected, this, [=]() {
        m_clients.removeAll(newClient);
        delete newClient;
        emit this->disconnected();
    }));

    m_clients.append(newClient);
    qInfo().noquote() << s << "is connected as a client";

    this->onClientConnected(intialState);
    emit this->connected();
}

void AdapterMessageHandler::clearClients()
{
    qDeleteAll(m_clients.begin(), m_clients.end());
    m_clients.clear();
    emit this->disconnected();
}

bool AdapterMessageHandler::isConnected() const
{
    if(m_clients.length() <= 0)
        return false;

    if(m_clients.first()->socket() == nullptr)
        return false;

    return m_clients.first()->socket()->isValid();
}

qint64 AdapterMessageHandler::sendMessage(QByteArray message)
{
    auto client = m_clients.first();
    if(!client->socket())
        throw std::invalid_argument("Socket is null");

    if(!client->socket()->isValid())
        throw std::invalid_argument("Invalid socket:" + client->socket()->peerAddress().toString().toStdString());

    return client->socket()->sendBinaryMessage(message);
}

void AdapterMessageHandler::parseTextMessage(QString message)
{
    bool parsed = false;
    QtJson::JsonObject messageData = QtJson::parse(message, parsed).toMap();
    if(!parsed)
    {
        qWarning().noquote() << "An error has occurred during parsing" << message << "." << "Message Ignored";
        return;
    }

    this->newMessageHandler(messageData);
}

void AdapterMessageHandler::parseBinaryMessage(QByteArray message)
{
    this->parseTextMessage(QString::fromUtf8(message));
}
