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
    double dx = ui->xAxisLineEdit->text().toDouble();
    double dy = ui->yAxisLineEdit->text().toDouble();
    double dz = ui->zAxisLineEdit->text().toDouble();
    double velocity = ui->velocityLineEdit->text().toDouble();
    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new Line(dx, dy, dz, velocity));
    machineTool->getCommandsManager()->addCommand(cmd);
}
