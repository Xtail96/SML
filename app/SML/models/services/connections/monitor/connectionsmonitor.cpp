#include "connectionsmonitor.h"

ConnectionsMonitor::ConnectionsMonitor(Connection* u1, Connection* u2, QObject *parent) : QObject(parent)
{
    QObject::connect(u1, SIGNAL(connectionStateChanged(bool)), this, SLOT(onU1_ConnectionStateChanged(bool)));
    QObject::connect(u2, SIGNAL(connectionStateChanged(bool)), this, SLOT(onU2_ConnectionStateChanged(bool)));
}

void ConnectionsMonitor::onU1_ConnectionStateChanged(bool state)
{
    emit u1StateChanged(state);
}

void ConnectionsMonitor::onU2_ConnectionStateChanged(bool state)
{
    emit u2StateChanged(state);
}
