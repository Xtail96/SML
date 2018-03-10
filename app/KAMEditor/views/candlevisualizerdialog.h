#ifndef CANDLEVISUALIZERDIALOG_H
#define CANDLEVISUALIZERDIALOG_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QProgressDialog>

#include "views/candlevisualizer/parser/gcodeviewparse.h"

#include "views/candlevisualizer/drawers/origindrawer.h"
#include "views/candlevisualizer/drawers/gcodedrawer.h"
#include "views/candlevisualizer/drawers/tooldrawer.h"
#include "views/candlevisualizer/drawers/heightmapborderdrawer.h"
#include "views/candlevisualizer/drawers/heightmapgriddrawer.h"
#include "views/candlevisualizer/drawers/heightmapinterpolationdrawer.h"
#include "views/candlevisualizer/drawers/shaderdrawable.h"
#include "views/candlevisualizer/drawers/selectiondrawer.h"
#include "views/candlevisualizer/tables/gcodetablemodel.h"
#include "views/candlevisualizer/tables/heightmaptablemodel.h"

#include "views/candlevisualizer/utils/interpolation.h"

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
    HeightMapBorderDrawer m_heightMapBorderDrawer;
    HeightMapGridDrawer m_heightMapGridDrawer;
    HeightMapInterpolationDrawer m_heightMapInterpolationDrawer;
    SelectionDrawer m_selectionDrawer;

    GCodeTableModel m_programModel;
    GCodeTableModel m_probeModel;
    GCodeTableModel m_programHeightmapModel;

    HeightMapTableModel m_heightMapModel;

    bool m_programLoading;
};

#endif // CANDLEVISUALIZERDIALOG_H
