#include "adapters_monitor.h"

AdaptersMonitor::AdaptersMonitor(Adapter* u1, Adapter* u2, QObject *parent) :
    QObject(parent)
{
    QObject::connect(u1, SIGNAL(connectionStateChanged()), this, SLOT(onAdapter_ConnectionStateChanged()));
    QObject::connect(u1, SIGNAL(workflowStateChanged()), this, SLOT(onAdapter_WorkflowStateChanged()));

    QObject::connect(u2, SIGNAL(connectionStateChanged()), this, SLOT(onAdapter_ConnectionStateChanged()));
    QObject::connect(u2, SIGNAL(workflowStateChanged()), this, SLOT(onAdapter_WorkflowStateChanged()));
}

void AdaptersMonitor::onAdapter_ConnectionStateChanged()
{
    emit this->adapterConnectionStateChanged();
}

void AdaptersMonitor::onAdapter_WorkflowStateChanged()
{
    emit this->adapterWorkflowStateChanged();
}
