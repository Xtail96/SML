#include "programvisualizewidow.h"
#include "ui_programvisualizewidow.h"

ProgramVisualizeWidow::ProgramVisualizeWidow(std::vector< std::shared_ptr<Command> > _commands, QWidget *parent, bool _run) :
    QDialog(parent),
    ui(new Ui::ProgramVisualizeWidow),
    run(_run)
{
    ui->setupUi(this);
    ui->rotatePushButton->setEnabled(false);
    ui->programOpenGLWidget->setCommands(_commands);
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
    ui->programOpenGLWidget->rotate();
}

void ProgramVisualizeWidow::on_sidePushButton_clicked()
{
    // поворот в плоскость Y0Z
    ui->programOpenGLWidget->setXAngle(-90);
    ui->programOpenGLWidget->setYAngle(0);
    ui->programOpenGLWidget->setZAngle(90);
    ui->programOpenGLWidget->rotate();
}

void ProgramVisualizeWidow::on_frontPushButton_clicked()
{
    // поворот в плоскость X0Z
    ui->programOpenGLWidget->setXAngle(90);
    ui->programOpenGLWidget->setYAngle(180);
    ui->programOpenGLWidget->setZAngle(180);
    ui->programOpenGLWidget->rotate();
}

void ProgramVisualizeWidow::on_centerPushButton_clicked()
{
    ui->programOpenGLWidget->setScale(0.1);
    ui->programOpenGLWidget->update();
}

void ProgramVisualizeWidow::on_rotatePushButton_clicked()
{
    ui->movePushButton->setEnabled(true);
    ui->rotatePushButton->setEnabled(false);
    ui->programOpenGLWidget->setMouseMoveAction(1);
}

void ProgramVisualizeWidow::on_movePushButton_clicked()
{
    ui->rotatePushButton->setEnabled(true);
    ui->movePushButton->setEnabled(false);
    ui->programOpenGLWidget->setMouseMoveAction(0);
}
