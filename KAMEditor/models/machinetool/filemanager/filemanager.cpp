#include "filemanager.h"

FileManager::FileManager(CommandsManager *_commandsManager, PointsManager *_pointsManager, size_t _axisesCount) :
    commandsManager(_commandsManager),
    pointsManager(_pointsManager),
    axisesCount(_axisesCount)
{
    if (commandsManager == nullptr)
    {
        throw std::invalid_argument("Commands manager is null");
    }

    if (pointsManager == nullptr)
    {
        throw std::invalid_argument("Points manager is null");
    }
}

void FileManager::createFile(const QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Файл по адресу " + path + "не удалось открыть при создании").exec();
    }
    else
    {
        file.close();
    }
}

void FileManager::save7KamFile()
{
    if(QFileInfo::exists(filePath))
    {
        QFile f(filePath);

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
    else
    {
        save7KamFileAs();
    }
}

void FileManager::save7KamFileAs()
{
    QString filename = QFileDialog::getSaveFileName(0, "Выберите место сохранения прогрммы", "", "*.7kam");
    if(filename.length() > 0)
    {
        createFile(filename);
        if(QFileInfo::exists(filename))
        {
            filePath = filename;
            save7KamFile();
            open7KamFile(filePath);
        }
        else
        {
            filePath = "";
            QMessageBox(QMessageBox::Warning, "Ошибка", "Файл не удалось создать").exec();
        }
    }
}

void FileManager::open7KamFile()
{
    /*QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Сохранение управляющей программы", "Сохранить открытый файл?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        saveFile();
    }*/
    QString path = QFileDialog::getOpenFileName(0, "Открыть", "", "*.7kam");
    open7KamFile(path);
}

void FileManager::open7KamFile(QString path)
{
    QString content = readFileInfo(path);
    if(content.size() > 0)
    {
        resetContainers();
        transferToSML(content);
    }
}

void FileManager::add7KamFile()
{
    QString originPath = filePath;
    QString path = QFileDialog::getOpenFileName(0, "Открыть", "", "*.7kam");
    QString content = readFileInfo(path);
    if(content.size() > 0)
    {
        transferToSML(content);
    }

    filePath = originPath;
}

void FileManager::new7KamFile()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Сохранение управляющей программы", "Сохранить открытый файл?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        save7KamFile();
    }
    resetContainers();
}

QString FileManager::readFileInfo(QString path)
{
    QString content = "";
    QFile inputFile(path);
    if(inputFile.open(QIODevice::ReadOnly))
    {
        filePath = path;
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
            commandsManager->addCommand(cmd);
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
            pointsManager->addPoint(point);
        }
    }
}

void FileManager::saveCommands(QFile &file)
{
    QString commandSHeader = QString(QString("[commands]") + QString('\n'));
    file.write(commandSHeader.toUtf8());
    size_t commandsCount = commandsManager->commandsCount();
    for (size_t idx = 0; idx < commandsCount; idx++)
    {
        std::shared_ptr<Command> command = commandsManager->operator [](idx);
        QString commandString = makeCommandString(command);
        file.write(commandString.toUtf8());
    }
}

void FileManager::savePoints(QFile &file)
{
    QString pointsHeader = QString(QString("[points]") + QString('\n'));
    file.write(pointsHeader.toUtf8());

    size_t pointsCount = pointsManager->pointCount();

    for (size_t idx = 0; idx < pointsCount; idx++)
    {
        std::shared_ptr<Point> point = pointsManager->operator [](idx);
        QString pointText = makePointString(point);
        file.write(pointText.toUtf8());
    }
}

void FileManager::resetContainers()
{
    resetCommands();
    resetPoints();
}

void FileManager::resetCommands()
{
    size_t commandsCount = commandsManager->commandsCount();
    commandsManager->deleteCommands(0, commandsCount);
}

void FileManager::resetPoints()
{
    size_t pointsCount = pointsManager->pointCount();
    pointsManager->deletePoints(0, pointsCount);
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
