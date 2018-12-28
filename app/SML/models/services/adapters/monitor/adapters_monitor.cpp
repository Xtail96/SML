#include "adapters_monitor.h"

AdaptersMonitor::AdaptersMonitor(Adapter* u1, Adapter* u2, QObject *parent) :
    QObject(parent)
{
    QObject::connect(u1, SIGNAL(connectionStateChanged(Adapter::Type, bool)), this, SLOT(onAdapter_ConnectionStateChanged(Adapter::Type, bool)));
    QObject::connect(u1, SIGNAL(workflowStateChanged(Adapter::Type, int)), this, SLOT(onAdapter_WorkflowStateChanged(Adapter::Type, int)));

    QObject::connect(u2, SIGNAL(connectionStateChanged(Adapter::Type, bool)), this, SLOT(onAdapter_ConnectionStateChanged(Adapter::Type, bool)));
    QObject::connect(u2, SIGNAL(workflowStateChanged(Adapter::Type, int)), this, SLOT(onAdapter_WorkflowStateChanged(Adapter::Type, int)));
}

void AdaptersMonitor::onAdapter_ConnectionStateChanged(Adapter::Type type, bool state)
{
    emit AdapterConnectionStateChanged(type, state);
}

void AdaptersMonitor::onAdapter_WorkflowStateChanged(Adapter::Type type, int state)
{
    emit AdapterWorkflowStateChanged(type, state);
}
