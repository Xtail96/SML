#include "visualizebridge.h"

VisualizeBridge::VisualizeBridge()
{

}

QStringList VisualizeBridge::commandsHeaders()
{
    QStringList headers =
    {
        "Команда",
        "Аргументы"
    };
    return headers;
}

QStringList VisualizeBridge::commandsNumbers(unsigned int commandsCount)
{
    QStringList numbers;
    for(unsigned int i = 0; i < commandsCount; i++)
    {
        numbers.push_back(QString::number(i+1));
    }
    return numbers;
}

QList<QTableWidgetItem *> VisualizeBridge::commands(CommandsInterpreter *interpreter)
{
    QList<QTableWidgetItem*> commandsItems;

    unsigned int commandsCount = interpreter->commandsCount();
    for(unsigned int i = 0; i < commandsCount; i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        std::shared_ptr<Command> currentCommand = interpreter->operator [](i);
        item->setText(QString::fromStdString(currentCommand->getName()));
        commandsItems.push_back(item);
    }
    return commandsItems;
}
