#ifndef PROGRAMVISUALIZEWINDOW_H
#define PROGRAMVISUALIZEWINDOW_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>

#include "gui/widgets/oglwidget.h"
#include "controllers/programvisualizewindowcontroller/programvisualizewindowcontroller.h"

namespace Ui {
class ProgramVisualizeWindow;
}

class ProgramVisualizeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ProgramVisualizeWindow(MainWindowController* _controller, QWidget *parent = 0, bool _run = false);
    ~ProgramVisualizeWindow();

private slots:
    void setupWidgets();

    void on_zoomInPushButton_clicked();

    void on_zoomOutPushButton_clicked();

    void on_topPushButton_clicked();

    void on_sidePushButton_clicked();

    void on_frontPushButton_clicked();

    void on_centerPushButton_clicked();

    void on_acceptOptionsPushButton_clicked();

    void showOffsets();

    void on_printPushButton_clicked();

private:
    Ui::ProgramVisualizeWindow *ui;

    ProgramVisualizeWindowController* programVisualizeController;

    void setupOGLWidget();
    void setupProgramVisualizeController(MainWindowController *controller);

    void showCommands();
    QTableWidgetItem *fillCommandsTable(unsigned int row, unsigned int column);

    bool run;
    unsigned int minimalGridSize = 1;
};

#endif // PROGRAMVISUALIZEWINDOW_H
