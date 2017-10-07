#include "filemanager.h"

FileManager::FileManager(CommandsManager *cm, PointsManager *pm, size_t _axisesCount) :
    cmd_mgr(cm),
    pnt_mgr(pm),
    axisesCount(_axisesCount)
{
    if (cmd_mgr == nullptr)
        throw std::invalid_argument("Commands manager is null");

    if (pnt_mgr == nullptr)
        throw std::invalid_argument("Points manager is null");
}

QFile FileManager::createFile()
{
    /*if (changed)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Сохранение изменений", "Файл был изменен. Сохранить файл?",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            saveFile();
        }
    }*/


}

void FileManager::saveFile()
{
    QFile f(filepath);
    f.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);

    saveCommands(f);
    savePoints(f);

    f.close();
}

void FileManager::openFile()
{
    /*QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Сохранение управляющей программы", "Сохранить открытый файл?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        saveFile();
    }*/
    QString path = QFileDialog::getOpenFileName(0, "Открыть", "", "*.7kam");
    QString content = readFileInfo(path);
    if(content.size() > 0)
    {
        resetContainers();
        transferToSML(content);
    }
}

void FileManager::addFile()
{
    QString path = QFileDialog::getOpenFileName(0, "Открыть", "", "*.7kam");
    QString content = readFileInfo(path);
    if(content.size() > 0)
    {
        transferToSML(content);
    }
}

QString FileManager::readFileInfo(QString path)
{
    QString content = "";
    QFile inputFile(path);
    if(inputFile.open(QIODevice::ReadOnly))
    {
        filepath = path;
        QTextStream in(&inputFile);
        content = in.readAll();
        inputFile.close();
    }
    return content;
}

void FileManager::transferToSML(QString content)
{
    QStringList splittedContent = content.split("[commands]")[1].split("[points]");

    for(int i = 0; i < splittedContent.size(); i++)
    {
        switch (i) {
        case 0:
        {
            QStringList commandsStrings = splittedContent[i].split('\n');
            transferToSMLCommands(commandsStrings);
            break;
        }
        case 1:
        {
            QStringList pointsStrings = splittedContent[1].split('\n');
            transferToSMLPoints(pointsStrings);
            break;
        }
        default:
            break;
        }
    }
}

std::shared_ptr<Command> FileManager::makeCommand(QString commandString)
{
    std::shared_ptr<Command> cmd;
    QStringList splittedCommandString = commandString.split(' ');
    int id = splittedCommandString[0].toInt();
    QStringList commandsArguments = splittedCommandString[1].split(',');
    cmd = CommandsBuilder::buildCommand(id, commandsArguments);
    return cmd;
}

Point* FileManager::makePoint(QString pointString)
{
    Point* point;
    QStringList pointCoordinates = pointString.split(',');
    point = PointsBuilder::buildPoint(pointCoordinates, axisesCount);
    return point;
}

void FileManager::transferToSMLCommands(QStringList commandsStrings)
{
    for(auto commandString : commandsStrings)
    {
        if(commandString.size() > 0)
        {
            std::shared_ptr<Command> cmd = makeCommand(commandString);
            cmd_mgr->addCommand(cmd);
        }
    }
}

void FileManager::transferToSMLPoints(QStringList pointsStrings)
{
    for(auto pointString : pointsStrings)
    {
        if(pointString.size() > 0)
        {
            Point* point = makePoint(pointString);
            pnt_mgr->addPoint(point);
        }
    }
}

void FileManager::saveCommands(QFile &f)
{
    f.write("[commands]");

    size_t commandsCount = cmd_mgr->commandsCount();

    QString commandsString;
    for (size_t idx = 0; idx < commandsCount; idx++)
    {
        std::shared_ptr<Command> cmd = cmd_mgr->operator [](idx);
        commandsString = makeCommandsString(cmd);
    }

    f.write(commandsString.toUtf8());
}

void FileManager::savePoints(QFile &f)
{
    /*f.write("[points]");

    size_t pointNumber = pnt_mgr->

    for (size_t idx = 0; idx < pointNumber; idx++)
    {
        std::shared_ptr<Command> point = pnt_mgr[idx];

        QString textcmd = point->getName() + " " + cmd->getArgumentsString();
        f.write(textcmd.toUtf8());
    }*/
}

void FileManager::resetContainers()
{
    resetCommands();
    resetPoints();
}

void FileManager::resetCommands()
{
    size_t commandsCount = cmd_mgr->commandsCount();
    cmd_mgr->deleteCommands(0, commandsCount);
}

void FileManager::resetPoints()
{
    size_t pointsCount = pnt_mgr->pointCount();
    pnt_mgr->deletePoints(0, pointsCount);
}

QString FileManager::makeCommandsString(std::shared_ptr<Command> cmd)
{
    QString commandsString;
    commandsString = QString::number(cmd->getId()) + QString(" ");

    QStringList commandsArguments =  cmd->getArguments();
    for(auto commandsArgument : commandsArguments)
    {
        commandsString += commandsArgument + ",";
    }
    return commandsString;
}
