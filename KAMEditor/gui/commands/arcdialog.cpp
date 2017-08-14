#include "arcdialog.h"
#include "ui_arcdialog.h"

ArcDialog::ArcDialog(CommandsManager *_commandsManager, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::ArcDialog),
    commandsManager(_commandsManager),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);
    fillFields();
}

ArcDialog::~ArcDialog()
{
    delete ui;
}

void ArcDialog::on_buttonBox_accepted()
{
    double r = ui->rLineEdit->text().toDouble();
    double al = ui->alLineEdit->text().toDouble();
    double fi = ui->fiLneEdit->text().toDouble();
    double velocity = ui->velocityLineEdit->text().toDouble();
    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new CArc(r, al, fi, velocity));

    if(edit)
    {
        commandsManager->operator [](index) = cmd;
    }
    else
    {
        commandsManager->insertCommand(index, cmd);
    }
}

void ArcDialog::fillFields()
{
    if(edit)
    {
        std::shared_ptr<Command> currentCommand = commandsManager->operator [](index);
        QStringList arguments = currentCommand->getArguments();


        QString rString = "";
        QString alString = "";
        QString fiString = "";
        QString vString = "";
        for(int i = 0; i < arguments.size(); i++)
        {
            switch (i) {
            case 0:
                rString = arguments[i];
                break;
            case 1:
                alString = arguments[i];
                break;
            case 2:
                fiString = arguments[i];
                break;
            case 3:
                vString = arguments[i];
                break;
            default:
                break;
            }
        }

        ui->rLineEdit->setText(rString);
        ui->alLineEdit->setText(alString);
        ui->fiLneEdit->setText(fiString);
        ui->velocityLineEdit->setText(vString);
    }
}
