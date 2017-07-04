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
    /*QString point_number_str = ui->mouse_to_point_lineEdit->text();
    unsigned int point_number = point_number_str.toUInt() - 1;

    if (!PointsManager::Instance().setSelectedPoint(point_number))
    {
        QMessageBox(QMessageBox::Information, "Сообщение", QString("Точка с таким номером отстутсвует в таблице")).exec();
    }*/
}
