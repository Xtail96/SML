#include "smlpausedialog.h"
#include "ui_smlpausedialog.h"

SMLPauseDialog::SMLPauseDialog(MainWindowController *_controller, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::SMLPauseDialog),
    controller(_controller),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);
    fillFields();
}

SMLPauseDialog::~SMLPauseDialog()
{
    delete ui;
}

void SMLPauseDialog::on_buttonBox_accepted()
{
    QString pauseLength = QString::number(ui->pauseValueLineEdit->text().toUInt());

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
        controller->updateCommand(arguments, index);
    }
}

void SMLPauseDialog::fillFields()
{
    if(edit)
    {
        QStringList arguments = controller->getCommandArguments(index);
        QString pauseLength = arguments[0];
        ui->pauseValueLineEdit->setText(pauseLength);
    }
}
