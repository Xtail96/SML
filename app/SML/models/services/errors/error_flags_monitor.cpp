#include "error_flags_monitor.h"

ErrorFlagsMonitor::ErrorFlagsMonitor(SmlErrorFlags &flags, QObject *parent) : QObject(parent)
{
    QObject::connect(&flags, SIGNAL(stateChanged()), this, SLOT(onSmlErrorFlags_StateChaged()));
}

void ErrorFlagsMonitor::onSmlErrorFlags_StateChaged()
{
    emit this->errorFlagsStateChanged();
}
