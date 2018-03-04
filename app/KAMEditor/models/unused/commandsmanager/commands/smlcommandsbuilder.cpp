#include "smlcommandsbuilder.h"

SMLCommandsBuilder::SMLCommandsBuilder()
{

}

std::shared_ptr<SMLCommand> SMLCommandsBuilder::buildCommand(int id, QStringList arguments, PointsManager *pointsManager, DevicesManager *devicesManager)
{
    std::shared_ptr<SMLCommand> cmd;
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
    case CMD_VARIABLE:
    {
        cmd = buildSMLVariableCommand(arguments);
        break;
    }
    case CMD_TTTARC:
    {
        cmd = buildSMLTTTArcCommand(arguments, pointsManager);
        break;
    }
    default:
    {
        break;
    }
    }
    return cmd;
}

std::shared_ptr<SMLCommand> SMLCommandsBuilder::buildArcCommand(QStringList arguments)
{
    std::shared_ptr<SMLCommand> cmd;

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

    cmd = std::shared_ptr<SMLCommand> (new CArc(r, al, fi, v));

    return cmd;
}

std::shared_ptr<SMLCommand> SMLCommandsBuilder::buildCommentCommand(QStringList arguments)
{
    std::shared_ptr<SMLCommand> cmd;

    QString text = "";

    for(int i = 0; i < arguments.size(); i++)
    {
        switch (i)
        {
        case 0:
            text = arguments[i];
            break;
        default:
            break;
        }
    }

    cmd = std::shared_ptr<SMLCommand> (new SMLComment(text));

    return cmd;
}

std::shared_ptr<SMLCommand> SMLCommandsBuilder::buildLine(QStringList arguments)
{
    std::shared_ptr<SMLCommand> cmd;

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

    cmd = std::shared_ptr<SMLCommand> (new Line(dx, dy, dz, v));

    return cmd;
}

std::shared_ptr<SMLCommand> SMLCommandsBuilder::buildPauseCommand(QStringList arguments)
{
    std::shared_ptr<SMLCommand> cmd;

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

    cmd = std::shared_ptr<SMLCommand> (new SMLPause(pauseLength));

    return cmd;
}

std::shared_ptr<SMLCommand> SMLCommandsBuilder::buildSwitchOnCommand(QStringList arguments, DevicesManager *devicesManager)
{
    std::shared_ptr<SMLCommand> cmd;

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

    cmd = std::shared_ptr<SMLCommand> (new SMLSwitchOn(devicesManager, deviceName, parametrs));

    return cmd;
}

std::shared_ptr<SMLCommand> SMLCommandsBuilder::buildSwitchOffCommand(QStringList arguments, DevicesManager *devicesManager)
{
    std::shared_ptr<SMLCommand> cmd;

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

    cmd = std::shared_ptr<SMLCommand> (new SMLSwitchOff(devicesManager, deviceName));

    return  cmd;
}

std::shared_ptr<SMLCommand> SMLCommandsBuilder::buildSMLVariableCommand(QStringList arguments)
{
    std::shared_ptr<SMLCommand> cmd;
    QString key = "key";
    QString value = QString::number(0);
    for(int i = 0; i < arguments.size(); i++)
    {
        switch (i) {
        case 0:
            key = arguments[i];
            break;
        case 1:
            value = arguments[i];
            break;
        default:
            break;
        }
    }
    cmd = std::shared_ptr<SMLCommand> (new SMLVariable(key, value));
    return cmd;
}

std::shared_ptr<SMLCommand> SMLCommandsBuilder::buildSMLTTTArcCommand(QStringList arguments, PointsManager* pointsManager)
{
    std::shared_ptr<SMLCommand> cmd;

    QString middlePointNumber = QString::number(0);
    QString endPointNumber = QString::number(0);
    QString v = QString::number(0);

    for(int i = 0; i < arguments.size(); i++)
    {
        switch(i)
        {
        case 0:
            middlePointNumber = arguments[i];
            break;
        case 1:
            endPointNumber = arguments[i];
            break;
        case 2:
            v = arguments[i];
            break;
        default:
            break;
        }
    }

    cmd = std::shared_ptr<SMLCommand> (new SMLTTTArc(pointsManager, middlePointNumber, endPointNumber, v));
    return cmd;
}

std::shared_ptr<SMLCommand> SMLCommandsBuilder::buildTTLineCommand(QStringList arguments, PointsManager* pointsManager)
{
    std::shared_ptr<SMLCommand> cmd;
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
    cmd = std::shared_ptr<SMLCommand> (new SMLTTLine(pointsManager, destinationPointNumber, airPassageIsNeed, dz, v));
    return cmd;
}
