#include "linedialog.h"
#include "ui_linedialog.h"

LineDialog::LineDialog(CommandsManager *_commandsManager, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::LineDialog),
    commandsManager(_commandsManager),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);
    fillFields();
}
LineDialog::~LineDialog()
{
    delete ui;
}
void LineDialog::on_buttonBox_accepted()
{
    double dx = ui->dxLineEdit->text().toDouble();
    double dy = ui->dyLineEdit->text().toDouble();
    double dz = ui->dzLineEdit->text().toDouble();
    double velocity = ui->velocityLineEdit->text().toDouble();
    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new Line(dx, dy, dz, velocity));

    if(edit)
    {
        commandsManager->operator [](index) = cmd;
    }
    else
    {
        commandsManager->insertCommand(index, cmd);
    }
}

void LineDialog::fillFields()
{
    if(edit)
    {
        std::shared_ptr<Command> currentCommand = commandsManager->operator [](index);
        QStringList arguments = currentCommand->getArguments();

        QString dxString = "";
        QString dyString = "";
        QString dzString = "";
        QString vString = "";
        for(int i = 0; i < arguments.size(); i++)
        {
            switch (i) {
            case 0:
                dxString = arguments[i];
                break;
            case 1:
                dyString = arguments[i];
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
        ui->dxLineEdit->setText(dxString);
        ui->dyLineEdit->setText(dyString);
        ui->dzLineEdit->setText(dzString);
        ui->velocityLineEdit->setText(vString);
    }
}
