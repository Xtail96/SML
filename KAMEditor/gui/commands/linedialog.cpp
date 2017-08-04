#include "linedialog.h"
#include "ui_linedialog.h"

LineDialog::LineDialog(MachineTool *_machineTool, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineDialog),
    machineTool(_machineTool)
{
    ui->setupUi(this);
}
LineDialog::~LineDialog()
{
    delete ui;
}
void LineDialog::on_buttonBox_accepted()
{
    double dx = ui->lineAxisXLineEdit->text().toDouble();
    double dy = ui->lineAxisYLineEdit->text().toDouble();
    double dz = ui->lineAxisZLineEdit->text().toDouble();
    double velocity = ui->lineVelocityLineEdit->text().toDouble();
    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new Line(dx, dy, dz, velocity));
    machineTool->getCommandsManager()->addCommand(cmd);
}
