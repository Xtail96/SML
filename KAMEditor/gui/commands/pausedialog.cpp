#include "pausedialog.h"
#include "ui_pausedialog.h"

PauseDialog::PauseDialog(MainWindowController *_controller, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::PauseDialog),
    controller(_controller),
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
    QString pauseLength = ui->pauseValueLineEdit->text();

    if(pauseLength.length() == 0)
    {
        pauseLength = QString::number(0);
    }

    QStringList arguments =
    {
        pauseLength,
    };

    if(!edit)
    {
        controller->insertCommand(CMD_PAUSE, arguments, index);
    }
    else
    {
        controller->replaceCommand(CMD_PAUSE, arguments, index);
    }
}

void PauseDialog::fillFields()
{
    if(edit)
    {
        QStringList arguments = controller->getCommandArguments(index);
        QString pauseLength = arguments[0];
        ui->pauseValueLineEdit->setText(pauseLength);
    }
}
