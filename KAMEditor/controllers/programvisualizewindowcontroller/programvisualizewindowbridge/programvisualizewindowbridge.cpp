#include "programvisualizewindowbridge.h"

ProgramVisualizeWindowBridge::ProgramVisualizeWindowBridge()
{

}

QStringList ProgramVisualizeWindowBridge::commandsHeaders()
{
    QStringList headers =
    {
        "Команда",
        "Аргументы"
    };
    return headers;
}

QStringList ProgramVisualizeWindowBridge::commandsNumbers(unsigned int commandsCount)
{
    QStringList numbers;
    for(unsigned int i = 0; i < commandsCount; i++)
    {
        numbers.push_back(QString::number(i+1));
    }
    return numbers;
}

QList<QTableWidgetItem *> ProgramVisualizeWindowBridge::commandsNames(std::vector<std::shared_ptr<SMLCommand> > commands)
{
    QList<QTableWidgetItem*> commandsNamesItems;
    unsigned int commandsCount = commands.size();
    for(unsigned int i = 0; i < commandsCount; i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        std::shared_ptr<SMLCommand> currentCommand = commands[i];
        item->setText(currentCommand->getName());
        commandsNamesItems.push_back(item);
    }
    return commandsNamesItems;
}

QList<QTableWidgetItem *> ProgramVisualizeWindowBridge::commandsArguments(std::vector< std::shared_ptr<SMLCommand> > commands)
{
    QList<QTableWidgetItem*> commandsArgumentsItems;
    unsigned int commandsCount = commands.size();
    for(unsigned int i = 0; i < commandsCount; i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        std::shared_ptr<SMLCommand> currentCommand = commands[i];
        item->setText(currentCommand->getArgumentsString());
        commandsArgumentsItems.push_back(item);
    }
    return commandsArgumentsItems;
}
