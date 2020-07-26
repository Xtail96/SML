#include "motion_controller.h"

MotionController::MotionController(QObject *parent):
    BaseController(parent),
    m_axes()
{
}

MotionController::~MotionController()
{
    qDeleteAll(m_axes.begin(), m_axes.end());
}

Point MotionController::currentPos()
{
    Point p;
    for(auto axis : m_axes)
    {
        p.insertAxis(axis->decoratedId(), axis->currentPosition());
    }
    return p;
}

void MotionController::parseBinaryMessage(QByteArray message)
{
    qDebug() << "MotionController::binary message received" << QString::fromUtf8(message);

    bool parsed = false;
    QtJson::JsonObject result = QtJson::parse(QString::fromUtf8(message), parsed).toMap();
    if(!parsed)
    {
        qDebug() << "MotionController::binaryMessageReceived: an error is occurred during parsing json" << QString::fromUtf8(message) << "." << "Message Ignored";
        return;
    }

    QtJson::JsonObject motionController = result["u2State"].toMap();
    if(motionController.isEmpty())
    {
        qDebug() << "MotionController::binaryMessageReceived: empty message";
        return ;
    }

    QtJson::JsonArray axes = motionController["axes"].toList();
    for(auto axis : axes)
    {
        QtJson::JsonObject axisObject = axis.toMap();
        QString id = axisObject["id"].toString();
        double value = axisObject["position"].toDouble();

        //if(!m_axes.contains(id))
        //    m_axes.insert(id, new Axis(id, value, this));
        //else
        //    m_axes[id].setCurrentPosition(value);
    }

    this->setProcessingTask(motionController["workflowState"].toBool());
}

void MotionController::parseTextMessage(QString message)
{
    qDebug() << "MotionController::text message received" << message;
}
