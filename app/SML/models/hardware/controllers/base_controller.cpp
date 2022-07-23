#include "base_controller.h"

BaseController::BaseController(QObject *parent) :
    WebSocketClient(parent),
    m_processingTask(false)
{
}

BaseController::~BaseController()
{
}

bool BaseController::isReady() const
{
    return !m_processingTask;
}

void BaseController::stopProcessingTask(QString targetControllerId)
{
    if(!m_processingTask) return;

    QtJson::JsonObject message = {
        std::pair<QString, QVariant>("target", targetControllerId),
        std::pair<QString, QVariant>("action", "stop")
    };
    this->sendMessage(QtJson::serialize(message));
    QTest::qWait(100);
}

void BaseController::setProcessingTask(bool processingTask)
{
    if(m_processingTask == processingTask) return;

    m_processingTask = processingTask;
    emit this->taskProcessingStateChanged();
}
