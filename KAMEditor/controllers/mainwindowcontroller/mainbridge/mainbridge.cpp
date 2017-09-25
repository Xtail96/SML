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

QList<QColor> MainBridge::sensorsLeds(std::vector<std::shared_ptr<Sensor> > sensors)
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

QStringList MainBridge::onScreenDevicesNames(std::vector<std::shared_ptr<Device> > devices)
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

QList<bool> MainBridge::onScreenDevicesStates(std::vector<std::shared_ptr<Device> > devices)
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

QList<QStringList> MainBridge::points(PointsManager *pointsManager)
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

QStringList MainBridge::point(PointsManager *pointsManager, unsigned int number)
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

Point* MainBridge::makePoint(QStringList arguments)
{
    std::vector<double> pointsCoordinates;
    for(auto argument : arguments)
    {
        pointsCoordinates.push_back(argument.toDouble());
    }
    Point* p = new Point(pointsCoordinates);
    return p;
}

std::shared_ptr<Command> MainBridge::makeCommand(int id, QStringList arguments, MachineTool *machineTool)
{
    std::shared_ptr<Command> cmd;
    switch (id)
    {
    case CMD_SWITCH_ON:
    {
        cmd = makeSwitchOnCommand(arguments, machineTool->getDevicesManager());
        break;
    }
    case CMD_SWITCH_OFF:
    {
        cmd = makeSwitchOffCommand(arguments, machineTool->getDevicesManager());
        break;
    }
    case CMD_COMMENT:
    {
        cmd = makeCommentCommand(arguments);
        break;
    }
    case CMD_PAUSE:
    {
        cmd = makePauseCommand(arguments);
        break;
    }
    case CMD_LINE:
    {
        cmd = makeLineCommand(arguments);
        break;
    }
    case CMD_TTLINE:
    {
        cmd = makeTTLineCommand(arguments, machineTool->getPointsManager());
        break;
    }
    case CMD_ARC:
    {
        cmd = makeArcCommand(arguments);
        break;
    }
    default:
    {
        break;
    }
    }
    return cmd;
}

std::shared_ptr<Command> MainBridge::makeSwitchOnCommand(QStringList arguments, DevicesManager *deviceManager)
{
    std::shared_ptr<Command> cmd;

    std::string deviceName = "Device";
    std::string parametrs = "Parametrs";

    for(int i = 0; i < arguments.size(); i++)
    {
        switch (i)
        {
        case 0:
            deviceName = arguments[i].toStdString();
            break;
        case 1:
            parametrs = arguments[i].toStdString();
            break;
        default:
            break;
        }
    }

    cmd = std::shared_ptr<Command> (new SwitchOn(deviceManager, deviceName, parametrs));

    return cmd;
}

std::shared_ptr<Command> MainBridge::makeSwitchOffCommand(QStringList arguments, DevicesManager *deviceManager)
{
    std::shared_ptr<Command> cmd;

    std::string deviceName = "Device";

    for(int i = 0; i < arguments.size(); i++)
    {
        switch (i)
        {
        case 0:
            deviceName = arguments[i].toStdString();
            break;
        default:
            break;
        }
    }

    cmd = std::shared_ptr<Command> (new SwitchOff(deviceManager, deviceName));

    return  cmd;
}

std::shared_ptr<Command> MainBridge::makeCommentCommand(QStringList arguments)
{
    std::shared_ptr<Command> cmd;

    std::string text = "";

    for(int i = 0; i < arguments.size(); i++)
    {
        switch (i)
        {
        case 0:
            text = arguments[i].toStdString();
            break;
        default:
            break;
        }
    }

    cmd = std::shared_ptr<Command> (new Comment(text));

    return cmd;
}

std::shared_ptr<Command> MainBridge::makePauseCommand(QStringList arguments)
{
    std::shared_ptr<Command> cmd;

    size_t pauseLength = 0;

    for(int i = 0; i < arguments.size(); i++)
    {
        switch (i)
        {
        case 0:
            pauseLength = arguments[i].toUInt();
            break;
        default:
            break;
        }
    }

    cmd = std::shared_ptr<Command> (new Pause(pauseLength));

    return cmd;
}

std::shared_ptr<Command> MainBridge::makeLineCommand(QStringList arguments)
{
    std::shared_ptr<Command> cmd;

    double dx = 0;
    double dy = 0;
    double dz = 0;
    double v = 0;

    for(int i = 0; i < arguments.size(); i++)
    {
        switch (i)
        {
        case 0:
            dx = arguments[i].toDouble();
            break;
        case 1:
            dy = arguments[i].toDouble();
            break;
        case 2:
            dz = arguments[i].toDouble();
            break;
        case 3:
            v = arguments[i].toDouble();
            break;
        default:
            break;
        }
    }

    cmd = std::shared_ptr<Command> (new Line(dx, dy, dz, v));

    return cmd;
}

std::shared_ptr<Command> MainBridge::makeTTLineCommand(QStringList arguments, PointsManager* pointsManager)
{
    std::shared_ptr<Command> cmd;

    size_t destinationPointNumber = 0;
    bool airPassageIsNeed = false;
    int dz = 0;
    double v = 0;

    for(int i = 0; i < arguments.size(); i++)
    {
        switch(i)
        {
        case 0:
            destinationPointNumber = arguments[i].toUInt();
            break;
        case 1:
            airPassageIsNeed = arguments[i].toInt();
            break;
        case 2:
            dz = arguments[i].toInt();
            break;
        case 3:
            v = arguments[i].toDouble();
            break;
        default:
            break;
        }
    }


    cmd = std::shared_ptr<Command> (new TTLine(pointsManager, destinationPointNumber, airPassageIsNeed, dz, v));

    return cmd;
}

std::shared_ptr<Command> MainBridge::makeArcCommand(QStringList arguments)
{
    std::shared_ptr<Command> cmd;

    double r = 0;
    double al = 0;
    double fi = 0;
    double v = 0;

    for(int i = 0; i < arguments.size(); i++)
    {
        switch(i)
        {
        case 0:
            r = arguments[i].toDouble();
            break;
        case 1:
            al = arguments[i].toDouble();
            break;
        case 2:
            fi = arguments[i].toDouble();
            break;
        case 3:
            v = arguments[i].toDouble();
            break;
        default:
            break;
        }
    }

    cmd = std::shared_ptr<Command> (new CArc(r, al, fi, v));

    return cmd;
}



QList<QTreeWidgetItem *> MainBridge::commands(CommandsManager *commandsManager)
{
    QList<QTreeWidgetItem*> commands;

    size_t commandsCount = commandsManager->commandsCount();

    for(unsigned int i = 0; i < commandsCount; i++)
    {
        try
        {
            std::shared_ptr<Command> command = commandsManager->operator [](i);
            QTreeWidgetItem* item = new QTreeWidgetItem();
            item->setText(0, QString::number(i+1));
            item->setText(1, QString::fromStdString(command->getName()));
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
