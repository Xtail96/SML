#include "connectionsmonitor.h"

ConnectionsMonitor::ConnectionsMonitor(Connection* u1, Connection* u2, QObject *parent) : QObject(parent)
{
    QObject::connect(u1, SIGNAL(connectionStateChanged(bool)), this, SLOT(onU1_ConnectionStateChanged(bool)));
    QObject::connect(u1, SIGNAL(lastErrorChanged(int)), this, SLOT(onU1_LastErrorChanged(int)));

    QObject::connect(u2, SIGNAL(connectionStateChanged(bool)), this, SLOT(onU2_ConnectionStateChanged(bool)));
    QObject::connect(u2, SIGNAL(lastErrorChanged(int)), this, SLOT(onU2_LastErrorChanged(int)));
}

void ConnectionsMonitor::onU1_ConnectionStateChanged(bool state)
{
    if(state)
    {
        emit u1Connected();
    }
    else
    {
        emit u1Disconnected();
    }
}

void ConnectionsMonitor::onU1_LastErrorChanged(int code)
{
    emit u1LastErrorChanged(code);
}

void ConnectionsMonitor::onU2_ConnectionStateChanged(bool state)
{
    if(state)
    {
        emit u2Connected();
    }
    else
    {
        emit u2Disconnected();
    }
}

void ConnectionsMonitor::onU2_LastErrorChanged(int code)
{
    emit u2LastErrorChanged(code);
}
