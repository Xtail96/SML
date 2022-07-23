#include "websocket_adapter.h"

WebSocketAdapter::WebSocketAdapter(QObject *parent):
    QObject(parent),
    m_clients()
{

}

WebSocketAdapter::~WebSocketAdapter()
{
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void WebSocketAdapter::createClient(QWebSocket *s, QtJson::JsonObject intialState)
{
    qInfo().noquote() << "Try to connect" << s;
    if(m_clients.length() > 0)
    {
        if(s->isValid())
            s->sendTextMessage("Connection refused");

        s->close();
        s->deleteLater();

        qWarning().noquote() << "Already have a client. Each adapter could have only one client. Websocket" << s << "is disconnected";
        return;
    }

    WebSocketClient* client = new WebSocketClient(s);
    client->addSlotInfo(QObject::connect(s, &QWebSocket::textMessageReceived, this, [=](QString message){
        this->parseTextMessage(message);
    }));

    client->addSlotInfo(QObject::connect(s, &QWebSocket::binaryMessageReceived, this, [=](QByteArray message) {
        this->parseBinaryMessage(message);
    }));

    client->addSlotInfo(QObject::connect(s, &QWebSocket::disconnected, this, [=]() {
        m_clients.removeAll(client);
        delete client;
        emit this->disconnected();
    }));

    m_clients.append(client);
    qInfo().noquote() << s << "is connected";

    this->onClientConnected(intialState);
    emit this->connected();
}

void WebSocketAdapter::clearClients()
{
    qDeleteAll(m_clients.begin(), m_clients.end());
    m_clients.clear();
    emit this->disconnected();
}

bool WebSocketAdapter::isConnected() const
{
    if(m_clients.length() <= 0)
        return false;

    if(m_clients.first()->socket() == nullptr)
        return false;

    return m_clients.first()->socket()->isValid();
}

qint64 WebSocketAdapter::sendMessage(QByteArray message)
{
    auto client = m_clients.first();
    if(!client->socket())
        throw std::invalid_argument("Socket is null");

    if(!client->socket()->isValid())
        throw std::invalid_argument("Invalid socket:" + client->socket()->peerAddress().toString().toStdString());

    return client->socket()->sendBinaryMessage(message);
}

void WebSocketAdapter::parseTextMessage(QString message)
{
    bool parsed = false;
    QtJson::JsonObject messageData = QtJson::parse(message, parsed).toMap();
    if(!parsed)
    {
        qWarning().noquote() << "An error has occurred during parsing" << message << "." << "Message Ignored";
        return;
    }

    this->onMessageReceived(messageData);
}

void WebSocketAdapter::parseBinaryMessage(QByteArray message)
{
    this->parseTextMessage(QString::fromUtf8(message));
}
