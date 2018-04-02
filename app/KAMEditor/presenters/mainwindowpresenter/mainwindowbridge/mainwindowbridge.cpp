#include "mainwindowbridge.h"

MainWindowBridge::MainWindowBridge()
{

}

MainWindowBridge::~MainWindowBridge()
{

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

/*QList<QTreeWidgetItem *> MainWindowBridge::commands(CommandsManager *commandsManager)
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
}*/

/*std::vector<std::shared_ptr<SMLCommand> > MainWindowBridge::getAllCommandsInVector(CommandsManager *commandsManager)
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
}*/
