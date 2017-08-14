#include "pausedialog.h"
#include "ui_pausedialog.h"

PauseDialog::PauseDialog(CommandsManager *_commandsManager, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::PauseDialog),
    commandsManager(_commandsManager),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);
    fillFields();
}

PauseDialog::~PauseDialog()
{
    delete ui;
}

void PauseDialog::on_buttonBox_accepted()
{
    size_t pauseLength = ui->pauseValueLineEdit->text().toUInt();
    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new Pause(pauseLength));

    if(edit)
    {
        commandsManager->operator [](index) = cmd;
    }
    else
    {
        commandsManager->insertCommand(index, cmd);
    }
}

void PauseDialog::fillFields()
{
    if(edit)
    {
        std::shared_ptr<Command> currentCommand = commandsManager->operator [](index);
        QStringList arguments = currentCommand->getArguments();
        QString pauseLength = arguments[0];
        ui->pauseValueLineEdit->setText(pauseLength);
    }
}
