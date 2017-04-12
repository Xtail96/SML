#include "ttzarcdialog.h"
#include "ui_ttzarcdialog.h"

TTZArcDialog::TTZArcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TTZArcDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
        ui->ttz_arc_start_point_lineEdit,
        ui->ttz_arc_finish_point_lineEdit,
        ui->ttz_arc_radius_lineEdit,
        ui->ttz_arc_dz_lineEdit,
        ui->ttz_arc_a_axis_lineEdit,
        ui->ttz_arc_velocity_lineEdit
    };
    fillFields(fields);
}

TTZArcDialog::~TTZArcDialog()
{
    delete ui;
}

void TTZArcDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_TTZARC;

    int startPoint = ui->ttz_arc_start_point_lineEdit->text().toInt();
    int finishPoint = ui->ttz_arc_finish_point_lineEdit->text().toInt();
    double radius = ui->ttz_arc_radius_lineEdit->text().toDouble();
    double dz = ui->ttz_arc_dz_lineEdit->text().toDouble();
    double angle = ui->ttz_arc_a_axis_lineEdit->text().toDouble();
    int velocity = ui->ttz_arc_velocity_lineEdit->text().toInt();

    cmd.commandColor = "#333";

    cmd.args = {
        std::to_string(startPoint),
        std::to_string(finishPoint),
        std::to_string(radius),
        std::to_string(dz),
        std::to_string(angle),
        std::to_string(velocity),
    };

    CommandInterpreter& instance = CommandInterpreter::Instance();
    unsigned int selected_command = instance.getSelectedCommand();

    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
       instance.editCommandsArguments(cmd.args, selected_command);
       instance.setSelectedCommandEditSignal(false);
    }
    else
    {
        instance.addCommand(cmd, selected_command);
    }
}
