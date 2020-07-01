#include "motor_adapter.h"

MotorAdapter::MotorAdapter(QWebSocket *socket, QObject *parent):
    QObject(parent),
    m_socket(socket)
{

}

MotorAdapter::~MotorAdapter()
{

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

qint64 MotorAdapter::sendMessage(QByteArray message)
{
    if(!m_socket.data())
        throw std::invalid_argument("Socket is null");

    if(!m_socket->isValid())
        throw std::invalid_argument("Invalid socket:" + m_socket->localAddress().toString().toStdString());

    return m_socket->sendBinaryMessage(message);
}
