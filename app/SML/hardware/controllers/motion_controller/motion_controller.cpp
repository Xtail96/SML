#include "motion_controller.h"

MotionController::MotionController(QObject *parent):
    BaseController(parent),
    m_repository()
{

}

MotionController::~MotionController()
{

}

void MotionController::processTask(Task t)
{
    QtJson::JsonArray blocks = {};
    for(int i = 0; i < t.blocksCount(); i++)
    {
        QMap<QString, QVariant> axesArgs = t.blockAxesArgs(i);
        if(axesArgs.isEmpty()) continue;

        QtJson::JsonObject block = {
            std::pair<QString, QVariant>("block", t.block(i)),
            std::pair<QString, QVariant>("detailedInfo", QtJson::JsonObject {
                std::pair<QString, QVariant>("blockId", t.blockId(i)),
                std::pair<QString, QVariant>("axesCount", axesArgs.size()),
                std::pair<QString, QVariant>("axesArguments", QtJson::JsonObject(axesArgs)),
                std::pair<QString, QVariant>("feedrate", t.blockFeedrate(i)),
                std::pair<QString, QVariant>("mcodeId", t.blockMCode(i)),
            })
        };
        blocks.insert(i, block);
    }

    QtJson::JsonObject message = {
        std::pair<QString, QVariant>("target", m_controllerName),
        std::pair<QString, QVariant>("action", "gcodeExecution"),
        std::pair<QString, QVariant>("raw", t.serialize()),
        std::pair<QString, QVariant>("blocks", blocks),
    };
    this->sendMessage(QtJson::serialize(message));
}

void MotionController::stopProcessing()
{
    this->stopProcessingTask(m_controllerName);
}

void MotionController::onClientConnected(QtJson::JsonObject initialState)
{
    QtJson::JsonObject motionController = initialState["motionControllerState"].toMap();
    if(motionController.isEmpty())
    {
        qWarning() << "Empty message received";
        return;
    }

    QtJson::JsonArray axes = motionController["axes"].toList();
    for(auto axis : axes)
    {
        QtJson::JsonObject axisObject = axis.toMap();
        Axis::Id id = Axis::idFromStr(axisObject["id"].toString());
        double value = axisObject["position"].toDouble();

        if(m_repository.exists(id))
            continue;

        m_repository.add(AxesRepository::createAxis(id, value));
    }
    this->setProcessingTask(motionController["workflowState"].toBool());
}

void MotionController::onMessageReceived(QtJson::JsonObject msg)
{
    QtJson::JsonObject motionController = msg["motionControllerState"].toMap();
    if(motionController.isEmpty())
    {
        qWarning() << "Empty message received";
        return;
    }

    bool positionChanged = false;
    QtJson::JsonArray axes = motionController["axes"].toList();
    for(auto axis : axes)
    {
        QtJson::JsonObject axisObject = axis.toMap();
        Axis::Id id = Axis::idFromStr(axisObject["id"].toString());
        double value = axisObject["position"].toDouble();

        if(!m_repository.exists(id))
        {
            qWarning() << "Unknown axis" << id;
            continue;
        }

        if(Axis::State::isPosEqual(m_repository.get(id).currentPositionFromBase(), value))
            continue;

        m_repository.get(id).setCurrentPosition(value);
        positionChanged = true;
    }
    this->setProcessingTask(motionController["workflowState"].toBool());
    if(positionChanged)
        emit this->positionChanged();
}

void MotionController::onDisconnected()
{
    m_repository.clear();
}
