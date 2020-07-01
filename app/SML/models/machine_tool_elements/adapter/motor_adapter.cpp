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
        QString json = QString::fromUtf8(message);
        QtJson::JsonObject result = QtJson::parse(json, parsed).toMap();
        if(!parsed)
            throw std::invalid_argument("MotorAdapter::binaryMessageReceived: an error is occurred during parsing json" + QString::fromUtf8(message).toStdString());

        QtJson::JsonObject u2State = result["u2State"].toMap();
        if(u2State.isEmpty())
            throw std::invalid_argument("MotorAdapter::binaryMessageReceived: empty message");

        this->m_workflowState = u2State["workflowState"].toBool();

        QtJson::JsonArray axes = u2State["axes"].toList();
        for(auto axis : axes)
        {
            QtJson::JsonObject axisObject = axis.toMap();
            QString id = axisObject["id"].toString();
            double value = axisObject["position"].toDouble();

            if(!m_axes.contains(id))
                m_axes.insert(id, Axis(id, 100, 100, 50, this));

            m_axes[id].setCurrentPosition(value);
        }
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

qint64 MotorAdapter::sendMessage(QByteArray message)
{
    if(!m_socket.data())
        throw std::invalid_argument("Socket is null");

    if(!m_socket->isValid())
        throw std::invalid_argument("Invalid socket:" + m_socket->localAddress().toString().toStdString());

    return m_socket->sendBinaryMessage(message);
}
