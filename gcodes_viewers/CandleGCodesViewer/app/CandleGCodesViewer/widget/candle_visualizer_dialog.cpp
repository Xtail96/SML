#include "candle_visualizer_dialog.h"
#include "ui_candle_visualizer_dialog.h"

CandleVisualizerDialog::CandleVisualizerDialog(QStringList program, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CandleVisualizerDialog)
{
    ui->setupUi(this);

    m_gcodesVisualizer = new GCodesVisualizer(ui->gcodesPreviewGLWidget, this);

    this->loadFile(program);
}

CandleVisualizerDialog::~CandleVisualizerDialog()
{
    delete m_gcodesVisualizer;
    delete ui;
}

void CandleVisualizerDialog::loadFile(QStringList data)
{
    m_gcodesVisualizer->loadProgram(data);
}

void CandleVisualizerDialog::on_topToolButton_clicked()
{
}

void CandleVisualizerDialog::on_frontToolButton_clicked()
{
}

void CandleVisualizerDialog::on_sideToolButton_clicked()
{
}

void CandleVisualizerDialog::on_isometricToolButton_clicked()
{
}

void CandleVisualizerDialog::closeEvent(QCloseEvent* e)
{
    qDebug() << "123";
    e->accept();
    //e->ignore();
    //this->accept();
}
