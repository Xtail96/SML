#include "websocket_client.h"

WebSocketClient::WebSocketClient(QObject *parent):
    QObject(parent),
    m_connections()
{

}

WebSocketClient::~WebSocketClient()
{
    qDeleteAll(m_connections.begin(), m_connections.end());
}

void WebSocketClient::createConnection(QWebSocket *s, QtJson::JsonObject intialState)
{
    qInfo().noquote() << "Try to connect" << s;
    if(m_connections.length() > 0)
    {
        if(s->isValid())
            s->sendTextMessage("Connection refused");

        s->close();
        s->deleteLater();

        qWarning().noquote() << "Already have a connection. Each client could have only one connection. Socket" << s << "will be disconnected";
        return;
    }

    WebSocketConnection* connection = new WebSocketConnection(s);
    connection->addSlotInfo(QObject::connect(s, &QWebSocket::textMessageReceived, this, [=](QString message){
        this->parseTextMessage(message);
    }));

    connection->addSlotInfo(QObject::connect(s, &QWebSocket::binaryMessageReceived, this, [=](QByteArray message) {
        this->parseBinaryMessage(message);
    }));

    connection->addSlotInfo(QObject::connect(s, &QWebSocket::disconnected, this, [=]() {
        m_connections.removeAll(connection);
        delete connection;
        emit this->disconnected();
    }));

    m_connections.append(connection);
    qInfo().noquote() << s << "is connected";

    this->onClientConnected(intialState);
    emit this->connected();
}

void WebSocketClient::clearConnections()
{
    qDeleteAll(m_connections.begin(), m_connections.end());
    m_connections.clear();
    emit this->disconnected();
}

bool WebSocketClient::isConnected() const
{
    if(m_connections.length() <= 0)
        return false;

    if(m_connections.first()->socket() == nullptr)
        return false;

    return m_connections.first()->socket()->isValid();
}

qint64 WebSocketClient::sendMessage(QByteArray message)
{
    auto client = m_connections.first();
    if(!client->socket())
        throw std::invalid_argument("Socket is null");

    if(!client->socket()->isValid())
        throw std::invalid_argument("Invalid socket:" + client->socket()->peerAddress().toString().toStdString());

    return client->socket()->sendBinaryMessage(message);
}

void WebSocketClient::parseTextMessage(QString message)
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

void WebSocketClient::parseBinaryMessage(QByteArray message)
{
    this->parseTextMessage(QString::fromUtf8(message));
}
