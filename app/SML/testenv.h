#ifndef TESTENV_H
#define TESTENV_H

#include <QObject>

#include "models/machine_tool_elements/adapter_refactor/adapter_gateway.h"
#include "models/machine_tool_elements/adapter_refactor/motion_controller.h"

class TestEnv : public QObject
{
    Q_OBJECT
public:
    explicit TestEnv(QObject *parent = nullptr);

private:
    AdapterGateway s;
    MotionController m;

signals:

};

#endif // TESTENV_H
