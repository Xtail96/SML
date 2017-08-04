#include "programvisualizewidow.h"
#include "ui_programvisualizewidow.h"

ProgramVisualizeWidow::ProgramVisualizeWidow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgramVisualizeWidow)
{
    ui->setupUi(this);
}

ProgramVisualizeWidow::~ProgramVisualizeWidow()
{
    delete ui;
}
