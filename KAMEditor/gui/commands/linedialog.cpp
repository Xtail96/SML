#include "linedialog.h"
#include "ui_linedialog.h"

LineDialog::LineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineDialog)
{
    ui->setupUi(this);

   std::vector<QLineEdit*> fields =
   {
        ui->line_lineEdit_axis_x,
        ui->line_lineEdit_axis_y,
        ui->line_lineEdit_axis_z,
        ui->line_lineEdit_axis_a,
        ui->line_lineEdit_axis_b,
        ui->line_lineEdit_velocity
   };
   fillFields(fields);

}
LineDialog::~LineDialog()
{
    delete ui;
}
void LineDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_LINE;

    cmd.commandColor = "#333";
    std::vector<std::string> v =
    {
        ui->line_lineEdit_axis_x->text().toStdString(),
        ui->line_lineEdit_axis_y->text().toStdString(),
        ui->line_lineEdit_axis_z->text().toStdString(),
        ui->line_lineEdit_axis_a->text().toStdString(),
        ui->line_lineEdit_axis_b->text().toStdString(),
        ui->line_lineEdit_velocity->text().toStdString()
    };
    for(auto it : v)
    {
        cmd.args.push_back(it);
    }
    setCommandArguments(cmd);
}
