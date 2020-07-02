#include "base_controller.h"

BaseController::BaseController(QObject *parent) :
    QObject(parent),
    m_clients(),
    m_processingTask(false)
{
}

BaseController::~BaseController()
{
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void BaseController::addClient(QWebSocket *s)
{
    if(m_clients.length() > 0)
    {
        qDebug () << "Already have client. Remove it first";
        if(s->isValid())
            s->sendTextMessage("Connection aborted");

        s->close();
        s->deleteLater();
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
    }));

    m_clients.append(newClient);

    emit this->connectionStateChanged();
}

void BaseController::clearClients()
{
    qDeleteAll(m_clients.begin(), m_clients.end());
    m_clients.clear();
    emit this->connectionStateChanged();
}

bool BaseController::processingTask() const
{
    return m_processingTask;
}

bool BaseController::isConnected() const
{
    if(m_clients.first() == nullptr) return false;
    if(m_clients.first()->socket() == nullptr) return false;

    return m_clients.first()->socket()->isValid();
}

qint64 BaseController::sendMessage(QByteArray message)
{
    auto client = m_clients.first();
    if(!client->socket())
        throw std::invalid_argument("Socket is null");

    if(!client->socket()->isValid())
        throw std::invalid_argument("Invalid socket:" + client->socket()->peerAddress().toString().toStdString());

    return client->socket()->sendBinaryMessage(message);
}

void BaseController::setProcessingTask(bool processingTask)
{
    if(m_processingTask == processingTask) return;

    m_processingTask = processingTask;
    emit this->taskProcessingStateChanged();
}
