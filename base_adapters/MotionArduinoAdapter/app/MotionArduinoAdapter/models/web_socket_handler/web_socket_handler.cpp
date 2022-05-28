#include "web_socket_handler.h"

WebSocketHandler::WebSocketHandler(const SettingsManager& sm, bool debug, QObject *parent) :
    QObject(parent),
    m_webSocket(nullptr),
    m_debug(debug),
    m_timer(new QTimer(this))
{
    loadSettings(sm);

    m_timer->setInterval(10000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(openWebSocket()));
    connect(this, SIGNAL(disconnected(QWebSocketProtocol::CloseCode,QString)), m_timer, SLOT(start()));
    connect(this, SIGNAL(connected()), m_timer, SLOT(stop()));

    openWebSocket();
}

WebSocketHandler::~WebSocketHandler()
{
    // Отключаем сокет
    closeWebSocket();

    delete m_timer;
    delete m_webSocket;
}

void WebSocketHandler::loadSettings(const SettingsManager &sm)
{
    try
    {
        m_url = QUrl(sm.get("ServerSettings", "ServerAddress").toString());
    }
    catch(std::invalid_argument e)
    {
        qDebug() << e.what();
        m_url = QUrl(QStringLiteral("ws://localhost:1234"));
    }
}

void WebSocketHandler::debugMessage(QString msg)
{
    if(m_debug)
        qDebug() << "WebSocketHandler::" + msg;
}

void WebSocketHandler::openWebSocket()
{
    this->debugMessage("try to open socket");
    if(!m_url.isEmpty())
    {
        this->debugMessage("webSocket server url is " + m_url.toString());
        if(m_webSocket != nullptr)
        {
            disconnect(this, SIGNAL(disconnected(QWebSocketProtocol::CloseCode,QString)), m_webSocket, SLOT(close(QWebSocketProtocol::CloseCode,QString)));
            m_webSocket->close();
            m_webSocket = nullptr;
        }

        m_webSocket = new QWebSocket();
        connect(m_webSocket, SIGNAL(connected()), this, SLOT(onQWebSocket_Connected()));
        connect(m_webSocket, SIGNAL(disconnected()), this, SLOT(onQWebSocket_Disconnected()));
        connect(this, SIGNAL(disconnected(QWebSocketProtocol::CloseCode,QString)), m_webSocket, SLOT(close(QWebSocketProtocol::CloseCode,QString)));

        m_webSocket->open(QUrl(m_url));
    }
    else
    {
        qDebug() << "Can not connect to the server";
    }
}

void WebSocketHandler::closeWebSocket()
{
    if(m_webSocket != nullptr)
    {
        this->debugMessage("close current socket");
        m_webSocket->close();
    }
}

void WebSocketHandler::onQWebSocket_Connected()
{
    this->debugMessage("web socket connected");
    connect(m_webSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onQWebSocket_TextMessageReceived(QString)));
    connect(m_webSocket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onQWebSocket_BinaryMessageReceived(QByteArray)));
    emit this->connected();
}

void WebSocketHandler::onQWebSocket_Disconnected()
{
    this->debugMessage("web socket server with url = " + m_url.toString() + " is disconnected");
    emit this->disconnected(QWebSocketProtocol::CloseCode::CloseCodeNormal);
}

bool WebSocketHandler::sendTextMessage(QString message)
{
    bool messageSent = false;
    if(m_webSocket != nullptr)
    {
        m_webSocket->sendTextMessage(message);
        messageSent = true;
    }
    else
    {
        emit this->disconnected(QWebSocketProtocol::CloseCode::CloseCodeBadOperation,
                          QString("Can not send text message:") + message);
    }
    return messageSent;
}

bool WebSocketHandler::sendBinaryMessage(QByteArray message)
{
    bool messageSent = false;
    if(m_webSocket != nullptr)
    {
        m_webSocket->sendBinaryMessage(message);
        messageSent = true;
    }
    else
    {
        this->debugMessage("can not send binary message");
        emit this->disconnected(QWebSocketProtocol::CloseCode::CloseCodeBadOperation,
                          QString("Can not send byte message: ") + QString::fromUtf8(message));
    }
    return messageSent;
}

void WebSocketHandler::onQWebSocket_TextMessageReceived(QString message)
{
    this->debugMessage("message received: " + message);
}

void WebSocketHandler::onQWebSocket_BinaryMessageReceived(QByteArray message)
{
    this->debugMessage(" binarymessage received: " + QString::fromUtf8(message));
    emit this->binaryMessageReceived(message);
}
