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
    QString destinationPointNumber = ui->destinationPointLineEdit->text();
    QString dz = ui->dzLineEdit->text();
    QString v = ui->velocityLineEdit->text();

    if(destinationPointNumber.length() == 0)
    {
        destinationPointNumber = QString::number(0);
    }

    if(dz.length() == 0)
    {
        dz = QString::number(0);
    }

    if(v.length() == 0)
    {
        v = QString::number(0);
    }

    QStringList arguments =
    {
        destinationPointNumber,
        QString::number(ui->airPassageCheckBox->isChecked()),
        dz,
        v
    };

    if(!edit)
    {
        controller->insertCommand(CMD_TTLINE, arguments, index);
    }
    else
    {
        controller->updateCommand(arguments, index);
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
