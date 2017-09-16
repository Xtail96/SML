#include "mainbridge.h"

MainBridge::MainBridge()
{

}

MainBridge::~MainBridge()
{

}

QStringList MainBridge::sensorsNames(std::vector<std::shared_ptr<Sensor> > sensors)
{
    QStringList names;
    for(auto sensor : sensors)
    {
        names.push_back(QString::fromStdString(sensor->getName()));
    }
    return names;
}

QStringList MainBridge::sensorsParametrsNames()
{
    QStringList parametrsNames =
    {
        "Имя платы",
        "Номер порта",
        "Номер входа",
        "Активное состояние",
    };
    return parametrsNames;
}

QList<QStringList> MainBridge::sensorsSettings(std::vector<std::shared_ptr<Sensor> > sensors)
{
    QList<QStringList> sensorsSettings;
    for(auto sensor : sensors)
    {
        QStringList sensorSettings =
        {
            QString::fromStdString(sensor->getBoardName()),
            QString::number(sensor->getPortNumber()),
            QString::number(sensor->getInputNumber()),
            QString::number(sensor->getActiveState())
        };
        sensorsSettings.push_back(sensorSettings);
    }
    return sensorsSettings;
}

QStringList MainBridge::devicesNames(std::vector<std::shared_ptr<Device> > devices)
{
    QStringList names;
    for(auto device : devices)
    {
        names.push_back(QString::fromStdString(device->getName()));
    }
    return names;
}

QStringList MainBridge::devicesParametrsNames()
{
    QStringList parametrsNames =
    {
        "Имя платы",
        "Номер порта",
        "Номер выхода",
        "Активное состояние",
        "Маска",
    };
    return parametrsNames;
}

QList<QStringList> MainBridge::devicesSettings(std::vector<std::shared_ptr<Device> > devices)
{
    QList<QStringList> devicesSettings;
    for(auto device : devices)
    {
        QStringList deviceSettings =
        {
            QString::fromStdString(device->getBoardName()),
            QString::number(device->getPortNumber()),
            QString::number(device->getOutputNumber()),
            QString::number(device->getActiveState()),
            QString::number(device->getMask(), 2)
        };
        devicesSettings.push_back(deviceSettings);
    }
    return devicesSettings;
}

QStringList MainBridge::axisesNames(std::vector<std::shared_ptr<Axis> > axises)
{
    QStringList names;
    for(auto axis : axises)
    {
        names.push_back(QString::fromStdString(axis->getName()));
    }
    return names;
}

QStringList MainBridge::axisesParametrsNames()
{
    QStringList parametrsNames =
    {
        "Длина",
        "Шаг",
        "Направление",
        "Рывок",
        "Ускорение",
        "Скорость",
        "Скорость Базирования",
        "Канал"
    };
    return parametrsNames;
}

QList<QStringList> MainBridge::axisesSettings(std::vector<std::shared_ptr<Axis> > axises)
{
    QList<QStringList> axisesSettings;
    for(auto axis : axises)
    {
        QStringList axisSettings =
        {
            QString::number(axis->getLength()),
            QString::number(axis->getStep()),
            QString::number(axis->getInvertDirection()),
            QString::number(axis->getJerk()),
            QString::number(axis->getAcceleration()),
            QString::number(axis->getVelocity()),
            QString::number(axis->getBasingVelocity()),
            QString::number(axis->getChannel())
        };
        axisesSettings.push_back(axisSettings);
    }
    return axisesSettings;
}
