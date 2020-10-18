#include "motion_controller.h"

MotionController::MotionController(QObject *parent):
    BaseController("MotionController", parent),
    m_axes(),
    m_slotsInfo()
{
    m_slotsInfo.append(QObject::connect(this, &BaseController::connectionStateChanged, this, [=]() {
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
    emit this->axesListChanged();
}

void MotionController::removeAxis(AxisId id)
{
    m_axes.remove(this->findById(id));
    emit this->axesListChanged();
}

void MotionController::clearAxes()
{
    m_axes.clear();
    emit this->axesListChanged();
}

void MotionController::parseBinaryMessage(QByteArray message)
{
    qDebug().noquote() << m_logName << "binary message received" << QString::fromUtf8(message);

    bool parsed = false;
    QtJson::JsonObject result = QtJson::parse(QString::fromUtf8(message), parsed).toMap();
    if(!parsed)
    {
        qDebug().noquote() << m_logName << "binaryMessageReceived: an error is occurred during parsing json" << QString::fromUtf8(message) << "." << "Message Ignored";
        return;
    }

    QtJson::JsonObject motionController = result["motionControllerState"].toMap();
    if(motionController.isEmpty())
    {
        qDebug().noquote() << m_logName << "binaryMessageReceived: empty message";
        return ;
    }

    QtJson::JsonArray axes = motionController["axes"].toList();
    for(auto axis : axes)
    {
        QtJson::JsonObject axisObject = axis.toMap();
        AxisId id = Axis::idFromStr(axisObject["id"].toString());
        double value = axisObject["position"].toDouble();

        (!this->axisExists(id))
            ? this->addAxis(id, value)
            : this->findById(id)->setCurrentPosition(value);
    }

    this->setProcessingTask(motionController["workflowState"].toBool());
}

void MotionController::parseTextMessage(QString message)
{
    qDebug().noquote() << m_logName << "text message received" << message;
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
