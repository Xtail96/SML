#include "programvisualizewidow.h"
#include "ui_programvisualizewidow.h"

ProgramVisualizeWidow::ProgramVisualizeWidow(QWidget *parent, bool _run) :
    QDialog(parent),
    ui(new Ui::ProgramVisualizeWidow),
    run(_run)
{
    ui->setupUi(this);
}

ProgramVisualizeWidow::~ProgramVisualizeWidow()
{
    delete ui;
}

void ProgramVisualizeWidow::on_zoomInPushButton_clicked()
{
    ui->programOpenGLWidget->scaling(1);
}

void ProgramVisualizeWidow::on_zoomOutPushButton_clicked()
{
    ui->programOpenGLWidget->scaling(-1);
}

void ProgramVisualizeWidow::on_topPushButton_clicked()
{
    // поворот в плоскость X0Y
    ui->programOpenGLWidget->setXAngle(180);
    ui->programOpenGLWidget->setYAngle(0);
    ui->programOpenGLWidget->setZAngle(0);
    ui->programOpenGLWidget->rotateField();
}

void ProgramVisualizeWidow::on_sidePushButton_clicked()
{
    // поворот в плоскость Y0Z
    ui->programOpenGLWidget->setXAngle(0);
    ui->programOpenGLWidget->setYAngle(90);
    ui->programOpenGLWidget->setZAngle(0);
    ui->programOpenGLWidget->rotateField();
}

void ProgramVisualizeWidow::on_frontPushButton_clicked()
{
    // поворот в плоскость X0Z
    ui->programOpenGLWidget->setXAngle(90);
    ui->programOpenGLWidget->setYAngle(180);
    ui->programOpenGLWidget->setZAngle(180);
    ui->programOpenGLWidget->rotateField();
}

void ProgramVisualizeWidow::on_centerPushButton_clicked()
{
    ui->programOpenGLWidget->setScale(0.1);
    ui->programOpenGLWidget->updateField();
}
