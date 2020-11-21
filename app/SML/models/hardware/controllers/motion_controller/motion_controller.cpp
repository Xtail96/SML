#include "motion_controller.h"

MotionController::MotionController(QObject *parent):
    BaseController("MotionController", parent),
    m_axes(),
    m_slotsInfo()
{
    m_slotsInfo.append(QObject::connect(this, &BaseController::disconnected, this, [=]() {
        this->clearAxes();
    }));
}

MotionController::~MotionController()
{
    for(auto& slotInfo : m_slotsInfo)
        QObject::disconnect(slotInfo);

    qDeleteAll(m_axes.begin(), m_axes.end());
}

bool MotionController::axisExists(AxisId id)
{
    for(auto axis : m_axes)
    {
       if(axis->id() == id)
           return true;
    }

    return false;
}

void MotionController::addAxis(AxisId id, double initialPosition)
{
    m_axes.insert(new Axis(id, initialPosition, this));
}

void MotionController::removeAxis(AxisId id)
{
    m_axes.remove(this->findById(id));
}

void MotionController::clearAxes()
{
    m_axes.clear();
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

        if(this->axisExists(id)) continue;
        this->addAxis(id, value);
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

        if(!this->axisExists(id)) { qWarning() << "Unknown axis" << id; continue; }
        this->findById(id)->setCurrentPosition(value);
    }
    this->setProcessingTask(motionController["workflowState"].toBool());
}

Axis *MotionController::findById(AxisId id)
{
    for(auto axis : m_axes)
    {
       if(axis->id() == id)
           return axis;
    }

    throw std::invalid_argument("invalid axis id" + Axis::decorateId(id).toStdString());
}
