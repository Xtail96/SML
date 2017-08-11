#ifndef PROGRAMVISUALIZEWIDOW_H
#define PROGRAMVISUALIZEWIDOW_H

#include <QDialog>
#include <QTableWidgetItem>

#include "gui/oglwidget.h"
#include "models/machinetool/machinetool.h"

namespace Ui {
class ProgramVisualizeWidow;
}

class ProgramVisualizeWidow : public QDialog
{
    Q_OBJECT

public:
    explicit ProgramVisualizeWidow(std::vector<std::shared_ptr<Command> > _commands, PointsManager _pointsManager, QWidget *parent = 0, bool _run = false);
    ~ProgramVisualizeWidow();

private slots:
    void on_zoomInPushButton_clicked();

    void on_zoomOutPushButton_clicked();

    void on_topPushButton_clicked();

    void on_sidePushButton_clicked();

    void on_frontPushButton_clicked();

    void on_centerPushButton_clicked();

    void on_rotatePushButton_clicked();

    void on_movePushButton_clicked();

    void on_pointsCheckBox_clicked();

private:
    Ui::ProgramVisualizeWidow *ui;

    void showCommands();
    QTableWidgetItem *fillCommandsTable(unsigned int row, unsigned int column);

    std::vector< std::shared_ptr<Command> > commands;

    bool run;
};

#endif // PROGRAMVISUALIZEWIDOW_H
