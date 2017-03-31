#include "commanddialog.h"

CommandDialog::CommandDialog()
{

}
CommandDialog::~CommandDialog()
{
    CommandInterpreter &instance = CommandInterpreter::Instance();
    if(instance.getSelectedCommandEditSignal())
    {
        instance.setSelectedCommandEditSignal(false);
    }
}
