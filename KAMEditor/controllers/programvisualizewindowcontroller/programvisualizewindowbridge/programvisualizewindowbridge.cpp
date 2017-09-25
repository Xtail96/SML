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

QList<QTableWidgetItem *> ProgramVisualizeWindowBridge::commandsNames(CommandsInterpreter *interpreter)
{
    QList<QTableWidgetItem*> commandsNamesItems;
    unsigned int commandsCount = interpreter->commandsCount();
    for(unsigned int i = 0; i < commandsCount; i++)
    {
        try
        {
            QTableWidgetItem* item = new QTableWidgetItem();
            std::shared_ptr<Command> currentCommand = interpreter->operator [](i);
            item->setText(QString::fromStdString(currentCommand->getName()));
            commandsNamesItems.push_back(item);
        }
        catch(std::out_of_range e)
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
            break;
        }
    }
    return commandsNamesItems;
}

QList<QTableWidgetItem *> ProgramVisualizeWindowBridge::commandsArguments(CommandsInterpreter *interpreter)
{
    QList<QTableWidgetItem*> commandsArgumentsItems;
    unsigned int commandsCount = interpreter->commandsCount();
    for(unsigned int i = 0; i < commandsCount; i++)
    {
        try
        {
            QTableWidgetItem* item = new QTableWidgetItem();
            std::shared_ptr<Command> currentCommand = interpreter->operator [](i);
            item->setText(currentCommand->getArgumentsString());
            commandsArgumentsItems.push_back(item);
        }
        catch(std::out_of_range e)
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
            break;
        }
    }
    return commandsArgumentsItems;
}
