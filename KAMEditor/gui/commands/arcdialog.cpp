#include "arcdialog.h"
#include "ui_arcdialog.h"

ArcDialog::ArcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArcDialog)
{
    ui->setupUi(this);
    QFile description("./description/arc.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->arc_textEdit_description->setHtml(content);
    description.close();
}

ArcDialog::~ArcDialog()
{
    delete ui;
}

void ArcDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_ARC;

    cmd.commandColor = "#333";

    double r = ui->arc_lineEdit_r->text().toDouble();
    double al = ui->arc_lineEdit_al->text().toDouble();
    double fi = ui->arc_lineEdit_fi->text().toDouble();
    int velocity = ui->arc_lineEdit_velocity->text().toInt();

    cmd.args = {
     std::to_string(r),
     std::to_string(al),
     std::to_string(fi),
     std::to_string(velocity),
    };

    CommandInterpreter& instance = CommandInterpreter::Instance();
    unsigned int selected_command = instance.getSelectedCommand();
    instance.addCommand(cmd, selected_command);
}
