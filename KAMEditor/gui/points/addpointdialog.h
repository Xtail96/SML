#ifndef ADDPOINTDIALOG_H
#define ADDPOINTDIALOG_H

#include <QDialog>
#include "machinetool/machinetool.h"
#include "machinetool/components/pointsManager/pointsManager/pointsmanager.h"
#include "machinetool/components/pointsManager/point/point.h"

namespace Ui {
class AddPointDialog;
}

class AddPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPointDialog(MachineTool *_machineTool, QWidget *parent = 0);
    ~AddPointDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddPointDialog *ui;
    bool isEdit;
    MachineTool* machineTool;
    std::vector< std::shared_ptr<Axis> > axises;
};

#endif // ADDPOINTDIALOG_H
