#ifndef ERROR_FLAGS_MONITOR_H
#define ERROR_FLAGS_MONITOR_H

#include <QObject>

#include "models/errors/sml_error_flags.h"

class ErrorFlagsMonitor : public QObject
{
    Q_OBJECT
public:
    explicit ErrorFlagsMonitor(SmlErrorFlags& flags, QObject *parent = nullptr);

signals:
    void errorFlagsStateChanged();

public slots:
    void onSmlErrorFlags_StateChaged();
};

#endif // ERROR_FLAGS_MONITOR_H
