#include "addpointdialog.h"
#include "ui_addpointdialog.h"

AddPointDialog::AddPointDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPointDialog)
{
    ui->setupUi(this);
}

AddPointDialog::~AddPointDialog()
{
    delete ui;
}

void AddPointDialog::on_buttonBox_accepted()
{
    QString x_str = ui->add_point_lineEdit_axis_x->text();
    double x = x_str.toDouble();

    QString y_str = ui->add_point_lineEdit_axis_y->text();
    double y = y_str.toDouble();

    QString z_str = ui->add_point_lineEdit_axis_z->text();
    double z = z_str.toDouble();

    QString a_str = ui->add_point_lineEdit_axis_a->text();
    double a = a_str.toDouble();

    QString b_str = ui->add_point_lineEdit_axis_b->text();
    double b = b_str.toDouble();

    std::vector<double> pointOriginCoordinates =
    {
        x,
        y,
        z,
        a,
        b
    };

    //PointsManager::Instance().addPoint(pointOriginCoordinates);
}
