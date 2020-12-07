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
        AxisId id = Axis::idFromStr(axisObject["id"].toString());
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

    QtJson::JsonArray axes = motionController["axes"].toList();
    for(auto axis : axes)
    {
        QtJson::JsonObject axisObject = axis.toMap();
        AxisId id = Axis::idFromStr(axisObject["id"].toString());
        double value = axisObject["position"].toDouble();

        if(!m_repository.axisExists(id)) { qWarning() << "Unknown axis" << id; continue; }
        m_repository.axis(id)->setCurrentPosition(value);
    }
    this->setProcessingTask(motionController["workflowState"].toBool());
}
