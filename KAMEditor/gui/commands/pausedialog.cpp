#include "pausedialog.h"
#include "ui_pausedialog.h"

PauseDialog::PauseDialog(CommandsManager *_commandsManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PauseDialog),
    commandsManager(_commandsManager)
{
    ui->setupUi(this);
}

PauseDialog::~PauseDialog()
{
    delete ui;
}

void PauseDialog::on_buttonBox_accepted()
{
    size_t pauseLength = ui->pauseValueLineEdit->text().toUInt();
    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new Pause(pauseLength));
    commandsManager->addCommand(cmd);
}
