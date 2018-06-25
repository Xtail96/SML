#ifndef SPINDELSMONITOR_H
#define SPINDELSMONITOR_H

#include <QObject>
#include "models/types/device/spindel.h"

class SpindelsMonitor : public QObject
{
    Q_OBJECT
public:
    explicit SpindelsMonitor(QList< QSharedPointer<Spindel> > spindels, QObject *parent = nullptr);

signals:
    void stateChanged(QString index, bool enable, size_t rotations);

public slots:
    void onSpindel_StateChanged(QString index, bool enable, size_t rotations);
};

#endif // SPINDELSMONITOR_H
