#include "motor_adapter.h"

MotorAdapter::MotorAdapter(QWebSocket *socket, QObject *parent):
    QObject(parent),
    m_socket(socket),
    m_axes(QMap<QString, Axis>()),
    m_workflowState(false),
    m_connections(QList<QMetaObject::Connection>())
{
    this->setupConnections();
}

MotorAdapter::~MotorAdapter()
{
    this->resetConnections();
}

Point MotorAdapter::currentPos()
{
    Point p;
    auto keys = m_axes.keys();
    for(auto key : keys)
    {
        p.insertAxis(key, (&m_axes[key])->currentPosition());
    }
    return p;
}

void MotorAdapter::setCurrentPos(Point absPos)
{
}

void MotorAdapter::moveTo(Point absPos)
{

}

void MotorAdapter::moveOffset(Point relPos)
{

}

void MotorAdapter::executeChunk(QString gcode)
{

}

void MotorAdapter::stopMoving()
{

}

void MotorAdapter::setupConnections()
{
    m_connections.append(QObject::connect(m_socket.data(), &QWebSocket::textMessageReceived, this, [=](QString message){

    }));

    m_connections.append(QObject::connect(m_socket.data(), &QWebSocket::binaryMessageReceived, this, [=](QByteArray message) {

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

            if(!m_axes.contains(id))
                m_axes.insert(id, Axis(id, value, this));
            else
                m_axes[id].setCurrentPosition(value);
        }

        this->setWorkflowState(u2State["workflowState"].toBool());
    }));

    m_connections.append(QObject::connect(m_socket.data(), &QWebSocket::disconnected, this, [=]() {
        this->deleteLater();
    }));
}

void MotorAdapter::resetConnections()
{
    for(auto& connection : m_connections)
        QObject::disconnect(connection);
}

void MotorAdapter::setWorkflowState(bool value)
{
    if(m_workflowState == value) return;

    m_workflowState = value;
    emit this->workflowStateChanged();
}

qint64 MotorAdapter::sendMessage(QByteArray message)
{
    if(!m_socket.data())
        throw std::invalid_argument("Socket is null");

    if(!m_socket->isValid())
        throw std::invalid_argument("Invalid socket:" + m_socket->localAddress().toString().toStdString());

    return m_socket->sendBinaryMessage(message);
}
