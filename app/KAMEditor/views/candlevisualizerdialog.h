#ifndef CANDLEVISUALIZERDIALOG_H
#define CANDLEVISUALIZERDIALOG_H

#include <QDialog>

#include "views/candlevisualizer/parser/gcodeviewparse.h"

#include "views/candlevisualizer/drawers/origindrawer.h"
#include "views/candlevisualizer/drawers/gcodedrawer.h"
#include "views/candlevisualizer/drawers/tooldrawer.h"
#include "views/candlevisualizer/drawers/heightmapborderdrawer.h"
#include "views/candlevisualizer/drawers/heightmapgriddrawer.h"
#include "views/candlevisualizer/drawers/heightmapinterpolationdrawer.h"
#include "views/candlevisualizer/drawers/shaderdrawable.h"
#include "views/candlevisualizer/drawers/selectiondrawer.h"

#include "views/candlevisualizer/utils/interpolation.h"

namespace Ui {
class CandleVisualizerDialog;
}

class CandleVisualizerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CandleVisualizerDialog(QWidget *parent = 0);
    ~CandleVisualizerDialog();

private:
    Ui::CandleVisualizerDialog *ui;

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
};

#endif // CANDLEVISUALIZERDIALOG_H
