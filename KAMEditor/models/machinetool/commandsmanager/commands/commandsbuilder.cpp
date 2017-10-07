#include "commandsbuilder.h"

CommandsBuilder::CommandsBuilder()
{

}

std::shared_ptr<Command> CommandsBuilder::buildCommand(int id, QStringList arguments)
{
    std::shared_ptr<Command> cmd;
    switch (id)
    {
    case CMD_SWITCH_ON:
    {
        //cmd = makeSwitchOnCommand(arguments, machineTool->getDevicesManager());
        break;
    }
    case CMD_SWITCH_OFF:
    {
        //cmd = makeSwitchOffCommand(arguments, machineTool->getDevicesManager());
        break;
    }
    case CMD_COMMENT:
    {
        cmd = buildCommentCommand(arguments);
        break;
    }
    case CMD_PAUSE:
    {
        cmd = buildPauseCommand(arguments);
        break;
    }
    case CMD_LINE:
    {
        cmd = buildLine(arguments);
        break;
    }
    case CMD_TTLINE:
    {
        //cmd = makeTTLineCommand(arguments, machineTool->getPointsManager());
        break;
    }
    case CMD_ARC:
    {
        cmd = buildArcCommand(arguments);
        break;
    }
    default:
    {
        break;
    }
    }
    return cmd;
}

std::shared_ptr<Command> CommandsBuilder::buildArcCommand(QStringList arguments)
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

std::shared_ptr<Command> CommandsBuilder::buildCommentCommand(QStringList arguments)
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

std::shared_ptr<Command> CommandsBuilder::buildLine(QStringList arguments)
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

std::shared_ptr<Command> CommandsBuilder::buildPauseCommand(QStringList arguments)
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

/*std::shared_ptr<Command> MainWindowBridge::makeSwitchOnCommand(QStringList arguments, DevicesManager *deviceManager)
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

std::shared_ptr<Command> MainWindowBridge::makeSwitchOffCommand(QStringList arguments, DevicesManager *deviceManager)
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
}*/



/*std::shared_ptr<Command> MainWindowBridge::makeTTLineCommand(QStringList arguments, PointsManager* pointsManager)
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
}*/
