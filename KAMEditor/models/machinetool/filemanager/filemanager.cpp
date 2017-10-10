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
    qDebug() << filepath;
    QFile f(filepath);

    if(!f.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Файл не открыт").exec();
    }
    else
    {
        saveCommands(f);
        savePoints(f);
        f.close();
    }
}

void FileManager::saveFileAs()
{

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

void FileManager::newFile()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Сохранение управляющей программы", "Сохранить открытый файл?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        if(filepath.length() > 0)
        {
            saveFile();
        }
        else
        {
            saveFileAs();
        }
    }
    resetContainers();
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
    QString commandSHeader = QString(QString("[commands]") + QString('\n'));
    f.write(commandSHeader.toUtf8());
    size_t commandsCount = cmd_mgr->commandsCount();
    for (size_t idx = 0; idx < commandsCount; idx++)
    {
        std::shared_ptr<Command> command = cmd_mgr->operator [](idx);
        QString commandString = makeCommandString(command);
        f.write(commandString.toUtf8());
    }
}

void FileManager::savePoints(QFile &f)
{
    QString pointsHeader = QString(QString("[points]") + QString('\n'));
    f.write(pointsHeader.toUtf8());

    size_t pointsCount = pnt_mgr->pointCount();

    for (size_t idx = 0; idx < pointsCount; idx++)
    {
        std::shared_ptr<Point> point = pnt_mgr->operator [](idx);
        QString pointText = makePointString(point);
        f.write(pointText.toUtf8());
    }
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

QString FileManager::makeCommandString(std::shared_ptr<Command> commmand)
{
    QString commandString = QString::number(commmand->getId()) + QString(" ");
    QStringList commandsArguments =  commmand->getArguments();
    size_t lastArgumentNumber = commandsArguments.size() - 1;

    for(size_t i = 0; i < lastArgumentNumber; i++)
    {
        commandString += commandsArguments[i] + ",";
    }
    commandString += QString(commandsArguments[lastArgumentNumber] + QString('\n'));

    return commandString;
}

QString FileManager::makePointString(std::shared_ptr<Point> point)
{
    QString pointString;
    size_t pointDimension = point->size();
    size_t lastArgumentNumber = pointDimension - 1;
    for(size_t i = 0; i < lastArgumentNumber; i++)
    {
        pointString += QString(QString::number(point->get(i)) + QString(","));
    }
    pointString += QString(QString::number(point->get(lastArgumentNumber)) + QString('\n'));
    return pointString;
}
