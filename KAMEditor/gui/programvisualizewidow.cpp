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
