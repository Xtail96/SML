#ifndef TESTENV_H
#define TESTENV_H

#include <QObject>

#include "models/machine_tool/controllers/adapters/adapter_gateway.h"
#include "models/machine_tool/controllers/motion_controller/motion_controller.h"
#include "models/machine_tool/controllers/device_controller/device_controller.h"
#include "models/machine_tool/controllers/registrator.h"

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
