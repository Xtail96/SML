#ifndef TESTENV_H
#define TESTENV_H

#include <QObject>

#include "models/machine_tool_elements/adapter/adapter_server.h"
#include "models/machine_tool_elements/adapter/motor_adapter.h"

class TestEnv : public QObject
{
    Q_OBJECT
public:
    explicit TestEnv(QObject *parent = nullptr);

private:
    AdapterServer s;
    MotorAdapter m;

signals:

};

#endif // TESTENV_H
