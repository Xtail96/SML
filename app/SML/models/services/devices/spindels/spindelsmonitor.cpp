#include "spindelsmonitor.h"

SpindelsMonitor::SpindelsMonitor(QList<QSharedPointer<Spindel> > spindels, QObject *parent) : QObject(parent)
{
    for(auto spindel : spindels)
    {
        QObject::connect(spindel.data(), SIGNAL(stateChanged(QString,bool,size_t)), this, SLOT(onSpindel_StateChanged(QString,bool,size_t)));
    }
}

void SpindelsMonitor::onSpindel_StateChanged(QString index, bool enable, size_t rotations)
{
    emit stateChanged(index, enable, rotations);
}