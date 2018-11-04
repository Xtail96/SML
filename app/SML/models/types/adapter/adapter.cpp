#include "adapter.h"

Adapter::Adapter(QObject *parent) : QObject(parent)
{
    m_connected = false;
    m_workflowState = 0;
    m_errorCode = 0;
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
        if(workflowState == 0 || workflowState == 1 || workflowState == 2)
        {
            m_workflowState = workflowState;
            emit workflowStateChanged(m_workflowState);
        }
        else
        {
            setErrorCode(10);
        }
    }
}

int Adapter::errorCode() const
{
    return m_errorCode;
}

void Adapter::setErrorCode(int errorCode)
{
    m_errorCode = errorCode;
    if(m_errorCode != 0)
    {
        emit errorIsOccured(m_errorCode);
    }
}
