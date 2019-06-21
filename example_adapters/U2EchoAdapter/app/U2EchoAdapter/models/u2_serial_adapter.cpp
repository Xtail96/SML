#include "u2_serial_adapter.h"

U2SerialAdapter::U2SerialAdapter(QString portName, QObject *parent) :
    QObject(parent),
    m_settingsManager(SettingsManager()),
    m_socketHandler(new WebSocketHandler(m_settingsManager, this))
{
    loadSettings();

    connect(m_socketHandler, SIGNAL(connected()), this, SLOT(onWebSocketHandler_Connected()));
    connect(m_socketHandler, SIGNAL(disconnected(QWebSocketProtocol::CloseCode,QString)), this, SLOT(onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode,QString)));
    connect(m_socketHandler, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onWebSocketHandler_BinaryMessageReceived(QByteArray)));
}

U2SerialAdapter::~U2SerialAdapter()
{
    disconnect(m_socketHandler, SIGNAL(connected()), this, SLOT(onWebSocketHandler_Connected()));
    disconnect(m_socketHandler, SIGNAL(disconnected(QWebSocketProtocol::CloseCode,QString)), this, SLOT(onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode,QString)));
    disconnect(m_socketHandler, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onWebSocketHandler_BinaryMessageReceived(QByteArray)));

    delete m_socketHandler;
}

void U2SerialAdapter::loadSettings()
{
    try
    {

    }
    catch(std::invalid_argument e)
    {
        qDebug() << e.what();
    }
}

void U2SerialAdapter::printState(U2State state)
{
    qDebug() << "State";
    qDebug() << "WorkflowState:" << state.getWorkflowState();
    qDebug() << "LastError: " << state.getLastError();
    qDebug() << "---------" ;
}

void U2SerialAdapter::sendCurrentStateToServer(U2State state)
{
    QtJson::JsonObject message;
    QtJson::JsonObject u2State;

    u2State["LastError"] = state.getLastError();
    u2State["WorkflowState"] = state.getWorkflowState();
    message["U2State"] = u2State;

    QByteArray data = QtJson::serialize(message);
    m_socketHandler->sendBinaryMessage(data);
}

void U2SerialAdapter::onWebSocketHandler_BinaryMessageReceived(QByteArray message)
{
    QString messageString = QString::fromUtf8(message);
    bool ok = false;
    QtJson::JsonObject result = QtJson::parse(messageString, ok).toMap();
    if(ok)
    {
        QString target = result["target"].toString();
        if(target.toLower() == "u2")
        {
            qDebug() << "start processing";
            for(int i = 0; i < 1000; i++)
            {
                qDebug() << i;
                QThread::msleep(10);
                qDebug() << "send state";
                this->sendCurrentStateToServer(U2State(0, 1));
            }
            qDebug() << "finissh processing";
            this->sendCurrentStateToServer(U2State(0, 0));
        }
        else
        {
            qDebug() << "Message ignored";
        }
    }
}

void U2SerialAdapter::sendTestPackageToServer()
{
    sendCurrentStateToServer(U2State(0, 0));
}

void U2SerialAdapter::onWebSocketHandler_Connected()
{
    qDebug() << "Web socket is connected";
    sendTestPackageToServer();
}

void U2SerialAdapter::onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode code, QString message)
{
    qDebug() << "Web socket disconnected with message" << message << "(code" << code << ")";
}
