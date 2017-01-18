#include "rotatedialog.h"
#include "ui_rotatedialog.h"

RotateDialog::RotateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RotateDialog)
{
    ui->setupUi(this);
    QFile description("./description/rotate.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->rotate_textEdit_description->setHtml(content);
    description.close();
}

RotateDialog::~RotateDialog()
{
    delete ui;
}

void RotateDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_ROTATE;

    cmd.commandColor = "#770077";

    std::string axis;
    if(ui->rotate_radioButton_axis_x->isChecked())
    {
        axis = "Вокруг оси X";
        cmd.args.push_back(axis);
        axis = "";
    }
    if(ui->rotate_radioButton_axis_y->isChecked())
    {
        axis = "Вокруг оси Y";
        cmd.args.push_back(axis);
        axis = "";
    }
    if(ui->rotate_radioButton_axis_z->isChecked())
    {
        axis = "Вокруг оси Z";
        cmd.args.push_back(axis);
        axis = "";
    }
    if(ui->rotate_radioButton_axis_a->isChecked())
    {
        axis = "Вокруг оси A";
        cmd.args.push_back(axis);
        axis = "";
    }
    if(ui->rotate_radioButton_axis_b->isChecked())
    {
        axis = "Вокруг оси B";
        cmd.args.push_back(axis);
        axis = "";
    }

    std::string angle = ui->rotate_angle_lineEdit->text().toStdString();
    cmd.args.push_back(angle);

    if(ui->rotate_relative_checkBox->isChecked())
    {
        std::string relative;
        relative = "Относительный";
        cmd.args.push_back(relative);
        relative = "";
    }

    CommandInterpreter& instance = CommandInterpreter::Instance();
    unsigned int selected_command = instance.getSelectedCommand();
    instance.addCommand(cmd, selected_command);
}
