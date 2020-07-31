#include "websockethandler.h"

WebSocketHandler::WebSocketHandler(const SettingsManager& sm, QObject *parent) :
    QObject(parent),
    m_webSocket(nullptr),
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
        m_debug = sm.get("ServerSettings", "DebugMode").toBool();
    }
    catch(std::invalid_argument e)
    {
        qDebug() << e.what();
        m_url = QUrl(QStringLiteral("ws://localhost:1234"));
        m_debug = false;
    }
}

void WebSocketHandler::openWebSocket()
{
    if(m_debug)
    {
        qDebug() << "try to open socket";
    }
    if(!m_url.isEmpty())
    {
        if(m_debug)
        {
            qDebug() << "WebSocket Server url is" << m_url.toString();
        }

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
        qDebug() << "Не могу установить связь с сервером!";
    }
}

void WebSocketHandler::closeWebSocket()
{
    if(m_webSocket != nullptr)
    {
        if(m_debug)
        {
            qDebug() << "Close current socket";
        }
        m_webSocket->close();
    }
}

void WebSocketHandler::onQWebSocket_Connected()
{
    if(m_debug)
    {
        qDebug() << "WebSocket connected";
    }
    connect(m_webSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onQWebSocket_TextMessageReceived(QString)));
    connect(m_webSocket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onQWebSocket_BinaryMessageReceived(QByteArray)));
    m_webSocket->sendTextMessage(QStringLiteral("@SML-MotionAdapter@"));
    emit connected();
}

void WebSocketHandler::onQWebSocket_Disconnected()
{
    if(m_debug)
    {
        qDebug() << "WebSocket Server with url = " << m_url.toString() << " is disconnected";
    }
    emit disconnected(QWebSocketProtocol::CloseCode::CloseCodeNormal);
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
        emit disconnected(QWebSocketProtocol::CloseCode::CloseCodeBadOperation,
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
        qDebug() << "Can not send binary message";
        emit disconnected(QWebSocketProtocol::CloseCode::CloseCodeBadOperation,
                          QString("Can not send byte message: ") + QString::fromUtf8(message));
    }
    return messageSent;
}

void WebSocketHandler::onQWebSocket_TextMessageReceived(QString message)
{
    if (m_debug)
    {
        //QMessageBox(QMessageBox::Information, "", "Message recieved: " + message).exec();
        qDebug() << "Message received:" << message;
        //emit textMessageReceived(message);
    }
}

void WebSocketHandler::onQWebSocket_BinaryMessageReceived(QByteArray message)
{
    if(m_debug)
    {
        qDebug() << "Received binary message" << message;
    }
    emit binaryMessageReceived(message);
}

void WebSocketHandler::setDebug(bool debug)
{
    m_debug = debug;
}
