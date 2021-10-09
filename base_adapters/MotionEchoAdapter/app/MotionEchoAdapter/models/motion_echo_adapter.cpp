#include "motion_echo_adapter.h"

MotionEchoAdapter::MotionEchoAdapter(QObject *parent) :
    QObject(parent),
    m_debugMode(true),
    m_settingsManager(SettingsManager()),
    m_socketHandler(new WebSocketHandler(m_settingsManager, m_debugMode, this)),
    m_currentState(MotionControllerState(0, 0)),
    m_processingTask(false)
{
    this->loadSettings();

    QObject::connect(m_socketHandler, SIGNAL(connected()), this, SLOT(onWebSocketHandler_Connected()));
    QObject::connect(m_socketHandler, SIGNAL(disconnected(QWebSocketProtocol::CloseCode,QString)), this, SLOT(onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode,QString)));
    QObject::connect(m_socketHandler, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onWebSocketHandler_BinaryMessageReceived(QByteArray)));
}

MotionEchoAdapter::~MotionEchoAdapter()
{
    QObject::disconnect(m_socketHandler, SIGNAL(connected()), this, SLOT(onWebSocketHandler_Connected()));
    QObject::disconnect(m_socketHandler, SIGNAL(disconnected(QWebSocketProtocol::CloseCode,QString)), this, SLOT(onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode,QString)));
    QObject::disconnect(m_socketHandler, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onWebSocketHandler_BinaryMessageReceived(QByteArray)));

    delete m_socketHandler;
}

void MotionEchoAdapter::loadSettings()
{
    try
    {
        m_currentState.addAxisPosition("X", 0.0);
        m_currentState.addAxisPosition("Y", 0.0);
        m_currentState.addAxisPosition("Z", 0.0);
        m_currentState.addAxisPosition("A", 0.0);
        m_currentState.addAxisPosition("B", 0.0);
        m_currentState.addAxisPosition("C", 0.0);
        m_currentState.addAxisPosition("U", 0.0);
        m_currentState.addAxisPosition("V", 0.0);
        m_currentState.addAxisPosition("W", 0.0);
    }
    catch(std::invalid_argument e)
    {
        qDebug() << e.what();
    }
}

void MotionEchoAdapter::startInThread(QtJson::JsonObject message, bool debugMode, bool printState)
{
    this->debugMessage("start processing");
    TaskWorker* worker = new TaskWorker(m_currentState, message, debugMode);
    QThread* thread = new QThread;
    worker->moveToThread(thread);
    QObject::connect(thread, SIGNAL(started()), worker, SLOT(process()));
    QObject::connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    QObject::connect(this, SIGNAL(stopExecution()), worker, SLOT(stop()));
    QObject::connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    QObject::connect(worker, &TaskWorker::finished, this, [=]() {
        this->debugMessage("task has finished");
        m_processingTask = false;
        m_currentState.setWorkflowState(0);
        this->sendCurrentStateToServer(m_currentState);
    });
    QObject::connect(worker, &TaskWorker::currentStateChanged, this, [=](MotionControllerState state) {
       m_currentState = state;
       if(debugMode && printState)
           this->printState(m_currentState);
       this->sendCurrentStateToServer(m_currentState);
    }, Qt::ConnectionType::BlockingQueuedConnection);
    thread->start();
    m_processingTask = true;
}

void MotionEchoAdapter::stopThreads()
{
    emit this->stopExecution();
}

void MotionEchoAdapter::onWebSocketHandler_BinaryMessageReceived(QByteArray message)
{
    QString messageString = QString::fromUtf8(message);
    bool ok = false;
    QtJson::JsonObject parsedMessage = QtJson::parse(messageString, ok).toMap();
    if(!ok)
    {
        this->debugMessage("invalid message " + messageString + ". Ignored");
    }

    QString target = parsedMessage["target"].toString();
    if(target.toLower() != "motioncontroller")
    {
        this->debugMessage("message is not for me. Ignored");
        return;
    }

    if(parsedMessage["action"] == "stop")
    {
        this->stopThreads();
        return;
    }

    if(m_processingTask) {
        this->stopThreads();
    }
    this->startInThread(parsedMessage, m_debugMode, false);

}

void MotionEchoAdapter::onWebSocketHandler_Connected()
{
    this->debugMessage("web socket is connected");
    this->sendCurrentStateToServer(m_currentState);
}

void MotionEchoAdapter::onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode code, QString message)
{
    this->debugMessage("web socket disconnected with message " + message + " (" + QString::number(code) + ")");
}

void MotionEchoAdapter::sendCurrentStateToServer(MotionControllerState state)
{
    QtJson::JsonObject message = {};
    QtJson::JsonObject motionControllerState = {};
    motionControllerState["lastError"] = state.getLastError();
    motionControllerState["workflowState"] = state.getWorkflowState();
    motionControllerState["axesCount"] = state.getAxesCount();
    QtJson::JsonArray axes = {};
    QStringList axisesKeys = state.getAxisesKeys();
    for(auto key : axisesKeys)
    {
        QtJson::JsonObject axis = {};
        axis["id"] = key;
        axis["position"] = state.getAxisPosition(key);
        axes.append(axis);
    }
    motionControllerState["axes"] = axes;
    message["motionControllerState"] = motionControllerState;

    QByteArray data = QtJson::serialize(message);
    m_socketHandler->sendBinaryMessage(data);
}

void MotionEchoAdapter::printState(MotionControllerState state)
{
    qDebug() << "State";
    qDebug() << "AxisesCount:" << state.getAxesCount();
    qDebug() << "Positions:";
    QStringList axisesKeys = state.getAxisesKeys();
    for(auto key : axisesKeys)
    {
        qDebug() << key << ":" << state.getAxisPosition(key);
    }
    qDebug() << "WorkflowState:" << state.getWorkflowState();
    qDebug() << "LastError: " << state.getLastError();
    qDebug() << "---------" ;
}

void MotionEchoAdapter::debugMessage(QString msg)
{
    if(m_debugMode)
        qDebug() << "MotionEchoAdapter::" + msg;
}

