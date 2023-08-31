#include "base_controller.h"

BaseController::BaseController(QObject *parent) :
    WebSocketClient(parent),
    m_slotsInfo(),
    m_taskProcessing(false)
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
    return !m_taskProcessing;
}

void BaseController::stopProcessing(QString targetControllerId)
{
    if(!m_taskProcessing)
        return;

    QtJson::JsonObject message = {
        std::pair<QString, QVariant>("target", targetControllerId),
        std::pair<QString, QVariant>("action", "stop")
    };
    this->sendMessage(QtJson::serialize(message));
    QTest::qWait(100);
}

void BaseController::setTaskProcessing(bool processing)
{
    if(m_taskProcessing == processing)
        return;

    m_taskProcessing = processing;
    emit this->taskProcessingStateChanged();
}
