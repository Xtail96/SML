#include "arcdialog.h"
#include "ui_arcdialog.h"

ArcDialog::ArcDialog(CommandsManager *_commandsManager, size_t _position, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArcDialog),
    commandsManager(_commandsManager),
    position(_position)
{
    ui->setupUi(this);
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
    commandsManager->insertCommand(position, cmd);
}
