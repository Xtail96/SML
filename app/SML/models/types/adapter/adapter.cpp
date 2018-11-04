#include "adapter.h"

Adapter::Adapter(QObject *parent) : QObject(parent)
{
    m_connected = false;
    m_workflowState = 0;
}

void Adapter::setConnected(bool connected)
{
    if(m_connected != connected)
    {
        m_connected = connected;
        emit connectionStateChanged(m_connected);
    }
}

int Adapter::workflowState() const
{
    return m_workflowState;
}

void Adapter::setWorkflowState(int workflowState)
{
    if(m_workflowState != workflowState)
    {
        m_workflowState = workflowState;
        emit workflowStateChanged(m_workflowState);
    }
}
