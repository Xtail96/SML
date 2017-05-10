#include "editpointdialog.h"
#include "ui_editpointdialog.h"

EditPointDialog::EditPointDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPointDialog)
{
    ui->setupUi(this);
    std::vector<Point> points = PointsManager::Instance().getPoints();
    PointsManager& point_table = PointsManager::Instance();
    unsigned int point_to_select = point_table.getSelectedPoint();


    double x = points[point_to_select]["X"];
    QString x_str = QString::number(x);

    double y = points[point_to_select]["Y"];
    QString y_str = QString::number(y);

    double z = points[point_to_select]["Z"];
    QString z_str = QString::number(z);

    double a = points[point_to_select]["A"];
    QString a_str = QString::number(a);

    double b = points[point_to_select]["B"];
    QString b_str = QString::number(b);

    ui->edit_point_lineEdit_axis_x->setText(x_str);

    ui->edit_point_lineEdit_axis_y->setText(y_str);

    ui->edit_point_lineEdit_axis_z->setText(z_str);

    ui->edit_point_lineEdit_axis_a->setText(a_str);

    ui->edit_point_lineEdit_axis_b->setText(b_str);
}

EditPointDialog::~EditPointDialog()
{
    delete ui;
}

void EditPointDialog::on_buttonBox_accepted()
{
    QString x_str = ui->edit_point_lineEdit_axis_x->text();
    double x = x_str.toDouble();

    QString y_str = ui->edit_point_lineEdit_axis_y->text();
    double y = y_str.toDouble();

    QString z_str = ui->edit_point_lineEdit_axis_z->text();
    double z = z_str.toDouble();

    QString a_str = ui->edit_point_lineEdit_axis_a->text();
    double a = a_str.toDouble();

    QString b_str = ui->edit_point_lineEdit_axis_b->text();
    double b = b_str.toDouble();

    PointsManager& point_table = PointsManager::Instance();
    unsigned int point_to_select = point_table.getSelectedPoint();

    std::vector<double> pointsOriginCoordinates =
    {
        x,
        y,
        z,
        a,
        b
    };

    point_table.setPoint(point_to_select, pointsOriginCoordinates);
}
