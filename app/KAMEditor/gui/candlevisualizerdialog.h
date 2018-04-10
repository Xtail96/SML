#ifndef CANDLEVISUALIZERDIALOG_H
#define CANDLEVISUALIZERDIALOG_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QProgressDialog>

#include "gui/candlevisualizer/parser/gcodeviewparse.h"

#include "gui/candlevisualizer/drawers/origindrawer.h"
#include "gui/candlevisualizer/drawers/gcodedrawer.h"
#include "gui/candlevisualizer/drawers/tooldrawer.h"
#include "gui/candlevisualizer/drawers/heightmapborderdrawer.h"
#include "gui/candlevisualizer/drawers/heightmapgriddrawer.h"
#include "gui/candlevisualizer/drawers/heightmapinterpolationdrawer.h"
#include "gui/candlevisualizer/drawers/shaderdrawable.h"
#include "gui/candlevisualizer/drawers/selectiondrawer.h"
#include "gui/candlevisualizer/tables/gcodetablemodel.h"
#include "gui/candlevisualizer/tables/heightmaptablemodel.h"
#include "gui/candlevisualizer/utils/interpolation.h"

namespace Ui {
class CandleVisualizerDialog;
}

class CandleVisualizerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CandleVisualizerDialog(QString fileName, QWidget *parent = 0);
    ~CandleVisualizerDialog();

    void loadFile(QStringList data);
    void loadFile(QString fileName);
    QTime updateProgramEstimatedTime(QList<LineSegment*> lines);

private slots:
    void on_topToolButton_clicked();

    void on_frontToolButton_clicked();

    void on_sideToolButton_clicked();

    void on_isometricToolButton_clicked();

private:
    Ui::CandleVisualizerDialog *ui;

    QString m_programFileName;
    GcodeViewParse m_viewParser;
    GcodeViewParse m_probeParser;
    OriginDrawer *m_originDrawer;
    GcodeDrawer *m_codeDrawer;
    GcodeDrawer *m_probeDrawer;
    GcodeDrawer *m_currentDrawer;

    ToolDrawer m_toolDrawer;
    SelectionDrawer m_selectionDrawer;

    GCodeTableModel m_programModel;
};

#endif // CANDLEVISUALIZERDIALOG_H
