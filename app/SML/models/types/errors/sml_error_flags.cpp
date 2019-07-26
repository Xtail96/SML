#include "sml_error_flags.h"

SmlErrorFlags::SmlErrorFlags(QObject *parent) :
    QObject(parent),
    m_errors(QSet<ERROR_CODE>())
{

}

bool SmlErrorFlags::isSystemHasErrors()
{
    return (m_errors.size() != 0);
}

void SmlErrorFlags::insertErrorFlag(ERROR_CODE code)
{
    if(code != ERROR_CODE::OK)
    {
        m_errors.insert(code);
        emit this->stateChanged();
    }
}

void SmlErrorFlags::dropErrorFlag(ERROR_CODE code)
{
    if(m_errors.contains(code))
    {
        m_errors.remove(code);
        emit this->stateChanged();
    }
}

QList<ERROR_CODE> SmlErrorFlags::getCurrentErrorFlags()
{
    return m_errors.toList();
}
