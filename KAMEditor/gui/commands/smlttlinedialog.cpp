#include "smlttlinedialog.h"
#include "ui_smlttlinedialog.h"

SMLTTLineDialog::SMLTTLineDialog(MainWindowController *_controller, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::SMLTTLineDialog),
    controller(_controller),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);

    fillFields();
}

SMLTTLineDialog::~SMLTTLineDialog()
{
    delete ui;
}

void SMLTTLineDialog::on_buttonBox_accepted()
{
    QString destinationPointNumber = QString::number(ui->destinationPointLineEdit->text().toUInt());
    QString dz = QString::number(ui->dzLineEdit->text().toDouble());
    QString v = QString::number(ui->velocityLineEdit->text().toDouble());

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

void SMLTTLineDialog::fillFields()
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

void SMLTTLineDialog::on_airPassageCheckBox_clicked()
{
    updateDZ();
}

void SMLTTLineDialog::updateDZ()
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
