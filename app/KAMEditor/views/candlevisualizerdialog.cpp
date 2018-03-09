#include "candlevisualizerdialog.h"
#include "ui_candlevisualizerdialog.h"

CandleVisualizerDialog::CandleVisualizerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CandleVisualizerDialog)
{
    ui->setupUi(this);

    /*m_heightMapMode = false;
    m_lastDrawnLineIndex = 0;
    m_fileProcessedCommandIndex = 0;
    m_cellChanged = false;
    m_programLoading = false;
    m_currentModel = &m_programModel;
    m_transferCompleted = true;*/

    m_originDrawer = new OriginDrawer();
    m_codeDrawer = new GcodeDrawer();
    m_codeDrawer->setViewParser(&m_viewParser);
    m_probeDrawer = new GcodeDrawer();
    m_probeDrawer->setViewParser(&m_probeParser);
    m_probeDrawer->setVisible(false);
    //m_heightMapGridDrawer.setModel(&m_heightMapModel);
    m_currentDrawer = m_codeDrawer;
    m_toolDrawer.setToolPosition(QVector3D(0, 0, 0));

    ui->glwVisualizer->addDrawable(m_originDrawer);
    ui->glwVisualizer->addDrawable(m_codeDrawer);
    ui->glwVisualizer->addDrawable(m_probeDrawer);
    ui->glwVisualizer->addDrawable(&m_toolDrawer);
    //ui->glwVisualizer->addDrawable(&m_heightMapBorderDrawer);
    //ui->glwVisualizer->addDrawable(&m_heightMapGridDrawer);
    //ui->glwVisualizer->addDrawable(&m_heightMapInterpolationDrawer);
    ui->glwVisualizer->addDrawable(&m_selectionDrawer);
    ui->glwVisualizer->fitDrawable();
}

CandleVisualizerDialog::~CandleVisualizerDialog()
{
    //delete m_probeDrawer;
    //delete m_codeDrawer;
    //delete m_probeDrawer;
    delete ui;
}
