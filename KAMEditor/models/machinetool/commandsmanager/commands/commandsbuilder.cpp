#include "commandsbuilder.h"

CommandsBuilder::CommandsBuilder()
{

}

std::shared_ptr<Command> CommandsBuilder::buildCommand(int id, QStringList arguments, PointsManager *pointsManager, DevicesManager *devicesManager)
{
    std::shared_ptr<Command> cmd;
    switch (id)
    {
    case CMD_SWITCH_ON:
    {
        cmd = buildSwitchOnCommand(arguments, devicesManager);
        break;
    }
    case CMD_SWITCH_OFF:
    {
        cmd = buildSwitchOffCommand(arguments, devicesManager);
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
        cmd = buildTTLineCommand(arguments, pointsManager);
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

    QString r = QString::number(0);
    QString al = QString::number(0);
    QString fi = QString::number(0);
    QString v = QString::number(0);

    for(int i = 0; i < arguments.size(); i++)
    {
        switch(i)
        {
        case 0:
            r = arguments[i];
            break;
        case 1:
            al = arguments[i];
            break;
        case 2:
            fi = arguments[i];
            break;
        case 3:
            v = arguments[i];
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

    QString dx = QString::number(0);
    QString dy = QString::number(0);
    QString dz = QString::number(0);
    QString v = QString::number(0);

    for(int i = 0; i < arguments.size(); i++)
    {
        switch (i)
        {
        case 0:
            dx = arguments[i];
            break;
        case 1:
            dy = arguments[i];
            break;
        case 2:
            dz = arguments[i];
            break;
        case 3:
            v = arguments[i];
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

    QString pauseLength = 0;

    for(int i = 0; i < arguments.size(); i++)
    {
        switch (i)
        {
        case 0:
            pauseLength = arguments[i];
            break;
        default:
            break;
        }
    }

    cmd = std::shared_ptr<Command> (new Pause(pauseLength));

    return cmd;
}

std::shared_ptr<Command> CommandsBuilder::buildSwitchOnCommand(QStringList arguments, DevicesManager *devicesManager)
{
    std::shared_ptr<Command> cmd;

    QString deviceName = "Device";
    QString parametrs = "Parametrs";

    for(int i = 0; i < arguments.size(); i++)
    {
        switch (i)
        {
        case 0:
            deviceName = arguments[i];
            break;
        case 1:
            parametrs = arguments[i];
            break;
        default:
            break;
        }
    }

    cmd = std::shared_ptr<Command> (new SwitchOn(devicesManager, deviceName, parametrs));

    return cmd;
}

std::shared_ptr<Command> CommandsBuilder::buildSwitchOffCommand(QStringList arguments, DevicesManager *devicesManager)
{
    std::shared_ptr<Command> cmd;

    QString deviceName = "Device";

    for(int i = 0; i < arguments.size(); i++)
    {
        switch (i)
        {
        case 0:
            deviceName = arguments[i];
            break;
        default:
            break;
        }
    }

    cmd = std::shared_ptr<Command> (new SwitchOff(devicesManager, deviceName));

    return  cmd;
}

std::shared_ptr<Command> CommandsBuilder::buildTTLineCommand(QStringList arguments, PointsManager* pointsManager)
{
    std::shared_ptr<Command> cmd;
    QString destinationPointNumber = QString::number(0);
    bool airPassageIsNeed = false;
    QString dz = QString::number(0);
    QString v = QString::number(0);
    for(int i = 0; i < arguments.size(); i++)
    {
        switch(i)
        {
        case 0:
            destinationPointNumber = arguments[i];
            break;
        case 1:
            airPassageIsNeed = arguments[i].toInt();
            break;
        case 2:
            dz = arguments[i];
            break;
        case 3:
            v = arguments[i];
            break;
        default:
            break;
        }
    }
    cmd = std::shared_ptr<Command> (new TTLine(pointsManager, destinationPointNumber, airPassageIsNeed, dz, v));
    return cmd;
}
