#ifndef TESTENV_H
#define TESTENV_H

#include <QObject>

#include "models/machine_tool_elements/adapter_refactor/adapter_gateway.h"
#include "models/machine_tool_elements/adapter_refactor/motion_controller.h"
#include "models/machine_tool_elements/adapter_refactor/device_controller.h"
#include "models/machine_tool_elements/adapter_refactor/registrator.h"

class TestEnv : public QObject
{
    Q_OBJECT
public:
    explicit TestEnv(QObject *parent = nullptr);

private:
    AdapterGateway s;
    MotionController m;
    DeviceController d;
    Registrator r;

signals:

};

#endif // TESTENV_H
