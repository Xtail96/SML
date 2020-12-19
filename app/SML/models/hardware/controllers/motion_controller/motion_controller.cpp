#include "motion_controller.h"

MotionController::MotionController(QObject *parent):
    BaseController("MotionController", parent),
    m_slotsInfo(),
    m_repository()
{
    m_slotsInfo.append(QObject::connect(this, &BaseController::disconnected, this, [=]() {
        m_repository.clearAxes();
    }));
}

MotionController::~MotionController()
{
    for(auto& slotInfo : m_slotsInfo)
        QObject::disconnect(slotInfo);
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
        std::pair<QString, QVariant>("target", "motionController"),
        std::pair<QString, QVariant>("action", "gcodeExecution"),
        std::pair<QString, QVariant>("raw", t.serialize()),
        std::pair<QString, QVariant>("blocks", blocks),
    };
    this->sendMessage(QtJson::serialize(message));
}

void MotionController::setup(QtJson::JsonObject initialState)
{
    QtJson::JsonObject motionController = initialState["motionControllerState"].toMap();
    if(motionController.isEmpty())
    {
        qWarning() << "Empty message received";
        return ;
    }

    QtJson::JsonArray axes = motionController["axes"].toList();
    for(auto axis : axes)
    {
        QtJson::JsonObject axisObject = axis.toMap();
        AxisId id = AxisState::idFromStr(axisObject["id"].toString());
        double value = axisObject["position"].toDouble();

        if(m_repository.axisExists(id)) continue;
        m_repository.addAxis(id, value);
    }
    this->setProcessingTask(motionController["workflowState"].toBool());
}

void MotionController::newMessageHandler(QtJson::JsonObject msg)
{
    QtJson::JsonObject motionController = msg["motionControllerState"].toMap();
    if(motionController.isEmpty())
    {
        qWarning() << "Empty message received";
        return ;
    }

    bool positionChanged = false;
    QtJson::JsonArray axes = motionController["axes"].toList();
    for(auto axis : axes)
    {
        QtJson::JsonObject axisObject = axis.toMap();
        AxisId id = AxisState::idFromStr(axisObject["id"].toString());
        double value = axisObject["position"].toDouble();

        if(!m_repository.axisExists(id)) { qWarning() << "Unknown axis" << id; continue; }
        if(AxisState::isEqual(m_repository.axis(id).currentPositionFromBase(), value)) continue;

        m_repository.axis(id).setCurrentPosition(value);
        positionChanged = true;
    }
    this->setProcessingTask(motionController["workflowState"].toBool());

    if(positionChanged) emit this->positionChanged();
}
