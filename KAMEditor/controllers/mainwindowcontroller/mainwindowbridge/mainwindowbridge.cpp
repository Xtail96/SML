#include "mainwindowbridge.h"

MainWindowBridge::MainWindowBridge()
{

}

MainWindowBridge::~MainWindowBridge()
{

}

QStringList MainWindowBridge::sensorsNames(std::vector<std::shared_ptr<Sensor> > sensors)
{
    QStringList names;
    for(auto sensor : sensors)
    {
        names.push_back(QString::fromStdString(sensor->getName()));
    }
    return names;
}

QStringList MainWindowBridge::sensorsParametrsNames()
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

QList<QStringList> MainWindowBridge::sensorsSettings(std::vector<std::shared_ptr<Sensor> > sensors)
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

QList<QColor> MainWindowBridge::sensorsLeds(std::vector<std::shared_ptr<Sensor> > sensors)
{
    QList<QColor> sensorsLeds;
    for(auto sensor : sensors)
    {
        QColor sensorLed(SmlColors::white());
        if(sensor->isActive())
        {
            sensorLed = sensor->getColor();
        }
        sensorsLeds.push_back(sensorLed);
    }
    return sensorsLeds;
}

QStringList MainWindowBridge::devicesNames(std::vector<std::shared_ptr<Device> > devices)
{
    QStringList names;
    for(auto device : devices)
    {
        names.push_back(QString::fromStdString(device->getName()));
    }
    return names;
}

QStringList MainWindowBridge::devicesParametrsNames()
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

QList<QStringList> MainWindowBridge::devicesSettings(std::vector<std::shared_ptr<Device> > devices)
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

QStringList MainWindowBridge::onScreenDevicesNames(std::vector<std::shared_ptr<Device> > devices)
{
    QStringList names;
    for(auto device : devices)
    {
        if(device->getNeedToDisplay())
        {
            names.push_back(QString::fromStdString(device->getName()));
        }
    }
    return names;
}

QList<bool> MainWindowBridge::onScreenDevicesStates(std::vector<std::shared_ptr<Device> > devices)
{
    QList<bool> devicesStates;
    for(auto device : devices)
    {
        if(device->getNeedToDisplay())
        {
            devicesStates.push_back(device->isEnable());
        }
    }
    return devicesStates;
}

QStringList MainWindowBridge::axisesNames(std::vector<std::shared_ptr<Axis> > axises)
{
    QStringList names;
    for(auto axis : axises)
    {
        names.push_back(QString::fromStdString(axis->getName()));
    }
    return names;
}

QStringList MainWindowBridge::axisesParametrsNames()
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

QList<QStringList> MainWindowBridge::axisesSettings(std::vector<std::shared_ptr<Axis> > axises)
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

QList<QStringList> MainWindowBridge::points(PointsManager *pointsManager)
{
    QList<QStringList> points;
    unsigned int pointsCount = pointsManager->pointCount();

    for(unsigned int i = 0; i < pointsCount; i++)
    {
        std::shared_ptr<Point> point = pointsManager->operator [](i);

        QStringList coordinates;
        unsigned int coordinatesCount = point.get()->size();
        for(unsigned int j = 0; j < coordinatesCount; j++)
        {
            QString coordinate;
            try
            {
                coordinate = QString::number(point.get()->operator [](j));
            }
            catch(std::out_of_range e)
            {
                QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
                break;
            }
            coordinates.push_back(coordinate);
        }
        points.push_back(coordinates);
    }
    return points;
}

QStringList MainWindowBridge::point(PointsManager *pointsManager, unsigned int number)
{
    QStringList coordinates;
    try
    {
        std::shared_ptr<Point> p = pointsManager->operator [](number);
        unsigned int coordinatesCount = p.get()->size();
        for(unsigned int j = 0; j < coordinatesCount; j++)
        {
            QString coordinate;
            coordinate = QString::number(p.get()->operator [](j));
            coordinates.push_back(coordinate);
        }
    }
    catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
    return coordinates;
}

Point* MainWindowBridge::makePoint(QStringList arguments)
{
    std::vector<double> pointsCoordinates;
    for(auto argument : arguments)
    {
        pointsCoordinates.push_back(argument.toDouble());
    }
    Point* p = new Point(pointsCoordinates);
    return p;
}

QList<QTreeWidgetItem *> MainWindowBridge::commands(CommandsManager *commandsManager)
{
    QList<QTreeWidgetItem*> commands;

    size_t commandsCount = commandsManager->commandsCount();

    for(unsigned int i = 0; i < commandsCount; i++)
    {
        try
        {
            std::shared_ptr<SMLCommand> command = commandsManager->operator [](i);
            QTreeWidgetItem* item = new QTreeWidgetItem();
            item->setText(0, QString::number(i+1));
            item->setText(1, command->getName());
            item->setText(2, command->getArgumentsString());
            QColor commandColor = command->getColor();
            item->setTextColor(1, commandColor);
            item->setTextColor(2, commandColor);

            commands.push_back(item);
        }
        catch(std::out_of_range e)
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
        }
    }
    return commands;
}

std::vector<std::shared_ptr<SMLCommand> > MainWindowBridge::getAllCommandsInVector(CommandsManager *commandsManager)
{
    std::vector< std::shared_ptr<SMLCommand> > commandsVector;
    size_t commandsCount = commandsManager->commandsCount();
    try
    {
        for(size_t i = 0; i < commandsCount; i++)
        {
            commandsVector.push_back(commandsManager->operator [](i));
        }
    }
    catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
    return commandsVector;
}
