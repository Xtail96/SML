#include "base_controller.h"

BaseController::BaseController(QObject *parent) :
    WebSocketClient(parent),
    m_slotsInfo(),
    m_processingTask(false)
{
    m_slotsInfo.append(QObject::connect(this, &BaseController::disconnected, this, [=]() {
        this->onDisconnected();
    }));
}

BaseController::~BaseController()
{
    for(auto& slotInfo : m_slotsInfo)
        QObject::disconnect(slotInfo);
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
