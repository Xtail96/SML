#include "adapter.h"

Adapter::Adapter(Type type, QObject *parent) :
    QObject(parent),
    m_type(type),
    m_connected(false),
    m_workflowState(0),
    m_path("")
{

}

bool Adapter::connectionState() const
{
    return m_connected;
}

void Adapter::setConnectionState(bool connected)
{
    if(m_connected != connected)
    {
        m_connected = connected;
        emit connectionStateChanged();
    }
}

unsigned int Adapter::workflowState() const
{
    return m_workflowState;
}

void Adapter::setWorkflowState(unsigned int workflowState)
{
    if(m_workflowState != workflowState)
    {
        m_workflowState = workflowState;
        emit workflowStateChanged();
    }
}

Adapter::Type Adapter::type() const
{
    return m_type;
}

QString Adapter::path() const
{
    return m_path;
}

void Adapter::setPath(const QString &path)
{
    m_path = path;
}
