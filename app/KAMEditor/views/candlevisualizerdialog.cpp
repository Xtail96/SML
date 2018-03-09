#include "candlevisualizerdialog.h"
#include "ui_candlevisualizerdialog.h"

CandleVisualizerDialog::CandleVisualizerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CandleVisualizerDialog)
{
    ui->setupUi(this);
}

CandleVisualizerDialog::~CandleVisualizerDialog()
{
    delete ui;
}
