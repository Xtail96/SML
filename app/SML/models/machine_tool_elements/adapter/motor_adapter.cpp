#include "motor_adapter.h"

MotorAdapter::MotorAdapter(QObject *parent):
    BaseAdapter(parent),
    m_axes()
{
}

MotorAdapter::~MotorAdapter()
{
    qDeleteAll(m_axes.begin(), m_axes.end());
}

Point MotorAdapter::currentPos()
{
    Point p;
    for(auto axis : m_axes)
    {
        p.insertAxis(axis->decoratedId(), axis->currentPosition());
    }
    return p;
}

void MotorAdapter::parseBinaryMessage(QByteArray message)
{
    bool parsed = false;
    QtJson::JsonObject result = QtJson::parse(QString::fromUtf8(message), parsed).toMap();
    if(!parsed)
    {
        qDebug() << "MotorAdapter::binaryMessageReceived: an error is occurred during parsing json" << QString::fromUtf8(message) << "." << "Message Ignored";
        return;
    }

    QtJson::JsonObject u2State = result["u2State"].toMap();
    if(u2State.isEmpty())
    {
        qDebug() << "MotorAdapter::binaryMessageReceived: empty message";
        return ;
    }

    QtJson::JsonArray axes = u2State["axes"].toList();
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

    this->setProcessingTask(u2State["workflowState"].toBool());
}

void MotorAdapter::parseTextMessage(QString message)
{
    qDebug() << "text message received" << message;
}
