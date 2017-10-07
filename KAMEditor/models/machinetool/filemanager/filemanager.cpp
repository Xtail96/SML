#include "filemanager.h"

FileManager::FileManager(CommandsManager *cm, PointsManager *pm) :
    cmd_mgr(cm), pnt_mgr(pm)
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
            saveFile();
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
    QString path = QFileDialog::getOpenFileName(0, "Открыть", "", "*.txt");
    readFileInfo(path);
}

void FileManager::saveCommands(QFile &f)
{
   /* f.write("[commands]");

    size_t commandNumber = cmd_mgr->getCommandsCount();

    QString textcmd;
    for (size_t idx = 0; idx < commandNumber; idx++)
    {
        std::shared_ptr<Command> cmd = cmd_mgr[idx];

        textcmd += cmd->getName() + " ";


    }

    f.write(textcmd.toUtf8());*/
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

void FileManager::readFileInfo(QString path)
{
    QFile inputFile(path);
    if(inputFile.open(QIODevice::ReadOnly))
    {
        filepath = path;
        QTextStream in(&inputFile);
        QString content = in.readAll();
        inputFile.close();
        transferToSML(content);
    }
    else
    {
        filepath = "";
    }
}

void FileManager::transferToSML(QString content)
{
    QStringList commandsStrings = content.split('\n');
    for(auto commandString : commandsStrings)
    {
        std::shared_ptr<Command> cmd = makeCommand(commandString);
        cmd_mgr->addCommand(cmd);
    }
}

std::shared_ptr<Command> FileManager::makeCommand(QString commandString)
{
    std::shared_ptr<Command> cmd;
    QStringList splittedCommandString = commandString.split(':');
    int id = splittedCommandString[0].toInt();
    QStringList commandsArguments = splittedCommandString[1].split(", ");
    qDebug() << commandsArguments;
    cmd = CommandsBuilder::buildCommand(id, commandsArguments);
    return cmd;
}
