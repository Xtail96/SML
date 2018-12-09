#ifndef GCODESVISUALIZER_H
#define GCODESVISUALIZER_H

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>

#include "libs/candle_visualizer/glwidget.h"
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

class GCodesVisualizer : public QObject
{
    Q_OBJECT

public:
    GCodesVisualizer(GLWidget* previewWidget, QObject *parent);
    ~GCodesVisualizer();

    void loadProgram(QStringList data);
    QTime updateProgramEstimatedTime(QList<LineSegment*> lines);

private:

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

    // display
    GLWidget* m_previewWidget;
};

#endif // GCODESVISUALIZER_H
