#ifndef CANDLEVISUALIZERDIALOG_H
#define CANDLEVISUALIZERDIALOG_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QProgressDialog>
#include <QCloseEvent>

#include "libs/candle_visualizer/parser/gcodeviewparse.h"
#include "libs/candle_visualizer/drawers/origindrawer.h"
#include "libs/candle_visualizer/drawers/gcodedrawer.h"
#include "libs/candle_visualizer/drawers/tooldrawer.h"
#include "libs/candle_visualizer/drawers/heightmapborderdrawer.h"
#include "libs/candle_visualizer/drawers/heightmapgriddrawer.h"
#include "libs/candle_visualizer/drawers/heightmapinterpolationdrawer.h"
#include "libs/candle_visualizer/drawers/shaderdrawable.h"
#include "libs/candle_visualizer/drawers/selectiondrawer.h"
#include "libs/candle_visualizer/tables/gcodetablemodel.h"
#include "libs/candle_visualizer/tables/heightmaptablemodel.h"
#include "libs/candle_visualizer/utils/interpolation.h"

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

    void closeEvent(QCloseEvent *e);
};

#endif // CANDLEVISUALIZERDIALOG_H
