#ifndef TOSELECTIONPOINTDIALOG_H
#define TOSELECTIONPOINTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "models/machinetool/pointsmanager/pointsmanager.h"
#include "models/machinetool/movementshandler/movementshandler.h"

#include "gui/points/addpointdialog.h"

namespace Ui {
class ToSelectionPointDialog;
}

class ToSelectionPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ToSelectionPointDialog(MovementsHandler *_movementsHandler, PointsManager* _pointsManager, QWidget *parent = 0);
    ~ToSelectionPointDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ToSelectionPointDialog *ui;
    MovementsHandler* movementsHandler;
    PointsManager* pointsManager;
};

#endif // MOUSETOSELECTIONPOINTDIALOG_H
