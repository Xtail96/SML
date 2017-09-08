#include "ttlinedialog.h"
#include "ui_ttlinedialog.h"

TTLineDialog::TTLineDialog(CommandsManager *_commandsManager, PointsManager *_pointsManager, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::TTLineDialog),
    commandsManager(_commandsManager),
    pointsManager(_pointsManager),
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
    unsigned int destinationPointNumber = ui->destinationPointLineEdit->text().toUInt();

    //std::shared_ptr<Point> destination = pointsManager->operator [](destinationPointNumber - 1);

    bool airPassageIsNeed = ui->airPassageCheckBox->isChecked();
    double dz = 0;
    if(airPassageIsNeed)
    {
        dz = ui->dzLineEdit->text().toDouble();
    }
    double velocity = ui->velocityLineEdit->text().toDouble();

    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new TTLine(pointsManager, destinationPointNumber, airPassageIsNeed, dz, velocity));
    if(edit)
    {
        commandsManager->operator [](index) = cmd;
    }
    else
    {
        commandsManager->insertCommand(index, cmd);
    }
    /*catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }*/
}

void TTLineDialog::fillFields()
{
    if(edit)
    {
        std::shared_ptr<Command> currentCommand = commandsManager->operator [](index);
        QStringList arguments = currentCommand->getArguments();

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
        ui->airPassageCheckBox->setChecked(true);
        if(ui->airPassageCheckBox->isChecked())
        {
            ui->dzLineEdit->setEnabled(true);
            ui->dzLineEdit->setText(dzString);
        }
        else
        {
            ui->dzLineEdit->setEnabled(false);
        }
        ui->velocityLineEdit->setText(vString);
    }
}

void TTLineDialog::on_airPassageCheckBox_clicked()
{
    if(ui->airPassageCheckBox->isChecked())
    {
        ui->dzLineEdit->setEnabled(true);
    }
    else
    {
        ui->dzLineEdit->setEnabled(false);
    }
}
