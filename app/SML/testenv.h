#ifndef TESTENV_H
#define TESTENV_H

#include <QObject>

#include "models/machine_tool_elements/controllers/adapters/adapter_gateway.h"
#include "models/machine_tool_elements/controllers/motion_controller.h"
#include "models/machine_tool_elements/controllers/device_controller.h"
#include "models/machine_tool_elements/controllers/registrator.h"

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
