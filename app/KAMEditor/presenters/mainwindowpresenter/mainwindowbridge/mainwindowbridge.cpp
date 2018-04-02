#include "mainwindowbridge.h"

MainWindowBridge::MainWindowBridge()
{

}

MainWindowBridge::~MainWindowBridge()
{

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
