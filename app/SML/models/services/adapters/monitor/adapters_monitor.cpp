#include "adapters_monitor.h"

AdaptersMonitor::AdaptersMonitor(Adapter* u1, Adapter* u2, QObject *parent) : QObject(parent)
{
    QObject::connect(u1, SIGNAL(connectionStateChanged(bool)), this, SLOT(onU1Adapter_ConnectionStateChanged(bool)));
    QObject::connect(u1, SIGNAL(workflowStateChanged(int)), this, SLOT(onU1Adapter_WorkflowStateChanged(int)));

    QObject::connect(u2, SIGNAL(connectionStateChanged(bool)), this, SLOT(onU2Adapter_ConnectionStateChanged(bool)));
}

void AdaptersMonitor::onU1Adapter_ConnectionStateChanged(bool state)
{
    emit u1AdapterConnectionStateChanged(state);
}

void AdaptersMonitor::onU2Adapter_ConnectionStateChanged(bool state)
{
    emit u2AdapterConnectionStateChanged(state);
}

void AdaptersMonitor::onU1Adapter_WorkflowStateChanged(int state)
{
    emit u1AdapterWorkflowStateChanged(state);
}
