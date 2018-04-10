#ifndef CANDLEVISUALIZERDIALOG_H
#define CANDLEVISUALIZERDIALOG_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QProgressDialog>

#include "libs/candlevisualizer/parser/gcodeviewparse.h"
#include "libs/candlevisualizer/drawers/origindrawer.h"
#include "libs/candlevisualizer/drawers/gcodedrawer.h"
#include "libs/candlevisualizer/drawers/tooldrawer.h"
#include "libs/candlevisualizer/drawers/heightmapborderdrawer.h"
#include "libs/candlevisualizer/drawers/heightmapgriddrawer.h"
#include "libs/candlevisualizer/drawers/heightmapinterpolationdrawer.h"
#include "libs/candlevisualizer/drawers/shaderdrawable.h"
#include "libs/candlevisualizer/drawers/selectiondrawer.h"
#include "libs/candlevisualizer/tables/gcodetablemodel.h"
#include "libs/candlevisualizer/tables/heightmaptablemodel.h"
#include "libs/candlevisualizer/utils/interpolation.h"

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
