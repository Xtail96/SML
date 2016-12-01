#include "mousetoselectionpointdialog.h"
#include "ui_mousetoselectionpointdialog.h"

MouseToSelectionPointDialog::MouseToSelectionPointDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MouseToSelectionPointDialog)
{
    ui->setupUi(this);
}

MouseToSelectionPointDialog::~MouseToSelectionPointDialog()
{
    delete ui;
}

void MouseToSelectionPointDialog::on_buttonBox_accepted()
{
    std::vector<Point> points = CommandInterpreter::Instance().getPoints();
    QString point_number_str = ui->mouse_to_point_lineEdit->text();
    int point_number = point_number_str.toInt();
    if(point_number>0 && point_number<=points.size())
    {
        point_number-=1;
        CommandInterpreter::Instance().setPointToSelect(point_number);
    }
    else
    {
        QMessageBox(QMessageBox::Information, "Сообщение", QString("Точка с таким номером отстутсвует в таблице")).exec();
    }
}
