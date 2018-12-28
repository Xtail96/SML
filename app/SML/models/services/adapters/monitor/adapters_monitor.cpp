#include "adapters_monitor.h"

AdaptersMonitor::AdaptersMonitor(Adapter* u1, Adapter* u2, QObject *parent) :
    QObject(parent),
    m_u1Adapter(u1),
    m_u2Adapter(u2)
{
    QObject::connect(m_u1Adapter, SIGNAL(connectionStateChanged(Adapter::Type, bool)), this, SLOT(onAdapter_ConnectionStateChanged(Adapter::Type, bool)));
    QObject::connect(m_u1Adapter, SIGNAL(workflowStateChanged(Adapter::Type, int)), this, SLOT(onAdapter_WorkflowStateChanged(Adapter::Type, int)));

    QObject::connect(m_u2Adapter, SIGNAL(connectionStateChanged(Adapter::Type, bool)), this, SLOT(onAdapter_ConnectionStateChanged(Adapter::Type, bool)));
    QObject::connect(m_u2Adapter, SIGNAL(workflowStateChanged(Adapter::Type, int)), this, SLOT(onAdapter_WorkflowStateChanged(Adapter::Type, int)));
}

void AdaptersMonitor::onAdapter_ConnectionStateChanged(Adapter::Type type, bool state)
{
    emit AdaptersConnectionStateChanged(m_u1Adapter->connectionState(), true);
}

void AdaptersMonitor::onAdapter_WorkflowStateChanged(Adapter::Type type, int state)
{
    emit AdaptersWorkflowStateChanged(m_u1Adapter->workflowState(), 0);
}
