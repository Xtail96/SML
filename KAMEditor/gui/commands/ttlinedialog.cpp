#include "ttlinedialog.h"
#include "ui_ttlinedialog.h"

TTLineDialog::TTLineDialog(MainWindowController *_controller, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::TTLineDialog),
    controller(_controller),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);

    fillFields();
}

TTLineDialog::~TTLineDialog()
{
    delete ui;
}

void TTLineDialog::on_buttonBox_accepted()
{
    QStringList arguments =
    {
        ui->destinationPointLineEdit->text(),
        QString::number(ui->airPassageCheckBox->isChecked()),
        ui->dzLineEdit->text(),
        ui->velocityLineEdit->text()
    };

    if(!edit)
    {
        controller->insertCommand(CMD_TTLINE, arguments, index);
    }
    else
    {
        controller->replaceCommand(CMD_TTLINE, arguments, index);
    }
}

void TTLineDialog::fillFields()
{
    if(edit)
    {
        QStringList arguments = controller->getCommandArguments(index);

        QString destinationPointNumberString = "";
        QString airPassageIsNeed = "";
        QString dzString = "";
        QString vString = "";
        for(int i = 0; i < arguments.size(); i++)
        {
            switch (i) {
            case 0:
                destinationPointNumberString = arguments[i];
                break;
            case 1:
                airPassageIsNeed = arguments[i];
                break;
            case 2:
                dzString = arguments[i];
                break;
            case 3:
                vString = arguments[i];
                break;
            default:
                break;
            }
        }
        ui->destinationPointLineEdit->setText(destinationPointNumberString);
        ui->airPassageCheckBox->setChecked(airPassageIsNeed.toUInt());
        updateDZ();
        ui->dzLineEdit->setText(dzString);
        ui->velocityLineEdit->setText(vString);
    }
    else
    {
        updateDZ();
    }
}

void TTLineDialog::on_airPassageCheckBox_clicked()
{
    updateDZ();
}

void TTLineDialog::updateDZ()
{
    if(ui->airPassageCheckBox->isChecked())
    {
        ui->dzLabel->setEnabled(true);
        ui->dzLineEdit->setEnabled(true);
    }
    else
    {
        ui->dzLabel->setEnabled(false);
        ui->dzLineEdit->setEnabled(false);
    }
}
