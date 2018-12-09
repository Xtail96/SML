#include "gcodes_visualizer.h"

GCodesVisualizer::GCodesVisualizer(GLWidget *previewWidget, QObject *parent) :
    QObject(parent),
    m_previewWidget(previewWidget)
{
    m_originDrawer = new OriginDrawer();
    m_codeDrawer = new GcodeDrawer();
    m_codeDrawer->setViewParser(&m_viewParser);
    m_probeDrawer = new GcodeDrawer();
    m_probeDrawer->setViewParser(&m_probeParser);
    m_probeDrawer->setVisible(false);
    m_currentDrawer = m_codeDrawer;
    m_toolDrawer.setToolPosition(QVector3D(0, 0, 0));

    m_previewWidget->addDrawable(m_originDrawer);
    m_previewWidget->addDrawable(m_codeDrawer);
    m_previewWidget->addDrawable(m_probeDrawer);
    m_previewWidget->addDrawable(&m_selectionDrawer);
    m_previewWidget->fitDrawable();
}

GCodesVisualizer::~GCodesVisualizer()
{
    delete m_originDrawer;
    delete m_codeDrawer;
    delete m_probeDrawer;
}

void GCodesVisualizer::loadProgram(QStringList data)
{
    QTime time;
    //time.start();

    // Reset parsers
    m_viewParser.reset();
    m_probeParser.reset();

    // Reset code drawer
    m_currentDrawer = m_codeDrawer;
    m_codeDrawer->update();
    m_previewWidget->fitDrawable(m_codeDrawer);
    updateProgramEstimatedTime(QList<LineSegment*>());

    // Reset tableview
    //QByteArray headerState = ui->tblProgram->horizontalHeader()->saveState();
    //ui->tblProgram->setModel(NULL);

    // Prepare parser
    GcodeParser gp;
    if (m_codeDrawer->getIgnoreZ()) gp.reset(QVector3D(100, 100, 0));

    //qDebug() << "Prepared to load:" << time.elapsed();
    time.start();

    QString command;
    QString stripped;
    QString trimmed;
    QList<QString> args;
    GCodeItem item;

    // Prepare model
    m_programModel.data().clear();
    m_programModel.data().reserve(data.count());

    QProgressDialog progress(tr("Opening file..."), tr("Abort"), 0, data.count(), nullptr);
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
            //qApp->processEvents();
            if (progress.wasCanceled()) break;
        }
    }
    progress.close();

    m_programModel.insertRow(m_programModel.rowCount());

    //qDebug() << "model filled:" << time.elapsed();
    time.start();

    //updateProgramEstimatedTime(m_viewParser.getLinesFromParser(&gp, m_settings->arcPrecision(), m_settings->arcDegreeMode()));
    updateProgramEstimatedTime(m_viewParser.getLinesFromParser(&gp, 0.1, true));
    //qDebug() << "view parser filled:" << time.elapsed();

    //  Update code drawer
    m_codeDrawer->update();
    m_previewWidget->fitDrawable(m_codeDrawer);
}

QTime GCodesVisualizer::updateProgramEstimatedTime(QList<LineSegment *> lines)
{
    double time = 0;

    for (int i = 0; i < lines.count(); i++) {
        LineSegment *ls = lines[i];
    //    foreach (LineSegment *ls, lines) {
        double length = double((ls->getEnd() - ls->getStart()).length());

        if (!qIsNaN(length) && !qIsNaN(ls->getSpeed()) && ls->getSpeed() != 0.0) time +=
                length / (ls->getSpeed());
    }

    time *= 60;

    QTime t;

    t.setHMS(0, 0, 0);
    t = t.addSecs(int(time));

    m_previewWidget->setSpendTime(QTime(0, 0, 0));
    m_previewWidget->setEstimatedTime(t);

    return t;
}
