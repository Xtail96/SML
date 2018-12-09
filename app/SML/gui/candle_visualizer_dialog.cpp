#include "candle_visualizer_dialog.h"
#include "ui_candle_visualizer_dialog.h"

#define UNKNOWN 0
#define IDLE 1
#define ALARM 2
#define RUN 3
#define HOME 4
#define HOLD 5
#define QUEUE 6
#define CHECK 7
#define DOOR 8

#define PROGRESSMINLINES 10000
#define PROGRESSSTEP     1000

CandleVisualizerDialog::CandleVisualizerDialog(QStringList program, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CandleVisualizerDialog)
{
    ui->setupUi(this);

    m_originDrawer = new OriginDrawer();
    m_codeDrawer = new GcodeDrawer();
    m_codeDrawer->setViewParser(&m_viewParser);
    m_probeDrawer = new GcodeDrawer();
    m_probeDrawer->setViewParser(&m_probeParser);
    m_probeDrawer->setVisible(false);
    m_currentDrawer = m_codeDrawer;
    m_toolDrawer.setToolPosition(QVector3D(0, 0, 0));

    ui->glwVisualizer->addDrawable(m_originDrawer);
    ui->glwVisualizer->addDrawable(m_codeDrawer);
    ui->glwVisualizer->addDrawable(m_probeDrawer);
    ui->glwVisualizer->addDrawable(&m_selectionDrawer);
    ui->glwVisualizer->fitDrawable();

    loadFile(program);
}

CandleVisualizerDialog::~CandleVisualizerDialog()
{
    //delete m_probeDrawer;
    //delete m_codeDrawer;
    //delete m_probeDrawer;
    delete ui;
}

void CandleVisualizerDialog::loadFile(QStringList data)
{
    QTime time;
    time.start();

    // Reset parsers
    m_viewParser.reset();
    m_probeParser.reset();

    // Reset code drawer
    m_currentDrawer = m_codeDrawer;
    m_codeDrawer->update();
    ui->glwVisualizer->fitDrawable(m_codeDrawer);
    updateProgramEstimatedTime(QList<LineSegment*>());

    // Reset tableview
    QByteArray headerState = ui->tblProgram->horizontalHeader()->saveState();
    ui->tblProgram->setModel(nullptr);

    // Prepare parser
    GcodeParser gp;
    //gp.setTraverseSpeed(m_settings->rapidSpeed());
    if (m_codeDrawer->getIgnoreZ()) gp.reset(QVector3D(100, 100, 0));

    qDebug() << "Prepared to load:" << time.elapsed();
    time.start();

    QString command;
    QString stripped;
    QString trimmed;
    QList<QString> args;
    GCodeItem item;

    // Prepare model
    m_programModel.data().clear();
    m_programModel.data().reserve(data.count());

    QProgressDialog progress(tr("Opening file..."), tr("Abort"), 0, data.count(), this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setFixedSize(progress.sizeHint());
    if (data.count() > PROGRESSMINLINES) {
        progress.show();
        progress.setStyleSheet("QProgressBar {text-align: center; qproperty-format: \"\"}");
    }

    while (!data.isEmpty())
    {
        command = data.takeFirst();

        // Trim command
        trimmed = command.trimmed();

        if (!trimmed.isEmpty()) {
            // Split command
            stripped = GcodePreprocessorUtils::removeComment(command);
            args = GcodePreprocessorUtils::splitCommand(stripped);

            gp.addCommand(args);

            item.command = trimmed;
            item.state = GCodeItem::InQueue;
            item.line = gp.getCommandNumber();
            item.args = args;

            m_programModel.data().append(item);
        }

        if (progress.isVisible() && (data.count() % PROGRESSSTEP == 0)) {
            progress.setValue(progress.maximum() - data.count());
            qApp->processEvents();
            if (progress.wasCanceled()) break;
        }
    }
    progress.close();

    m_programModel.insertRow(m_programModel.rowCount());

    qDebug() << "model filled:" << time.elapsed();
    time.start();

    //updateProgramEstimatedTime(m_viewParser.getLinesFromParser(&gp, m_settings->arcPrecision(), m_settings->arcDegreeMode()));
    updateProgramEstimatedTime(m_viewParser.getLinesFromParser(&gp, 0.1, true));
    qDebug() << "view parser filled:" << time.elapsed();

    // Set table model
    ui->tblProgram->setModel(&m_programModel);
    ui->tblProgram->horizontalHeader()->restoreState(headerState);

    // Update tableview
    //connect(ui->tblProgram->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(onTableCurrentChanged(QModelIndex,QModelIndex)));
    ui->tblProgram->selectRow(0);

    //  Update code drawer
    m_codeDrawer->update();
    ui->glwVisualizer->fitDrawable(m_codeDrawer);

    //resetHeightmap();
    //updateControlsState();
}

QTime CandleVisualizerDialog::updateProgramEstimatedTime(QList<LineSegment *> lines)
{
    double time = 0;

    for (int i = 0; i < lines.count(); i++) {
        LineSegment *ls = lines[i];
    //    foreach (LineSegment *ls, lines) {
        double length = (ls->getEnd() - ls->getStart()).length();

        if (!qIsNaN(length) && !qIsNaN(ls->getSpeed()) && ls->getSpeed() != 0) time +=
                length / (ls->getSpeed());
    }

    time *= 60;

    QTime t;

    t.setHMS(0, 0, 0);
    t = t.addSecs(time);

    ui->glwVisualizer->setSpendTime(QTime(0, 0, 0));
    ui->glwVisualizer->setEstimatedTime(t);

    return t;
}

void CandleVisualizerDialog::on_topToolButton_clicked()
{
    ui->glwVisualizer->setTopView();
    ui->glwVisualizer->update();
}

void CandleVisualizerDialog::on_frontToolButton_clicked()
{
    ui->glwVisualizer->setFrontView();
    ui->glwVisualizer->update();
}

void CandleVisualizerDialog::on_sideToolButton_clicked()
{
    ui->glwVisualizer->setLeftView();
    ui->glwVisualizer->update();
}

void CandleVisualizerDialog::on_isometricToolButton_clicked()
{
    ui->glwVisualizer->setIsometricView();
    ui->glwVisualizer->update();
}

void CandleVisualizerDialog::closeEvent(QCloseEvent* e)
{
    e->ignore();
    this->accept();
}
