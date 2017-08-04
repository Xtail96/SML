#ifndef OFFDIALOG_H
#define OFFDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"
#include "models/machinetool/machinetool.h"
#include "models/machinetool/commandsmanager/commands/switchoff.h"

namespace Ui {
class OffDialog;
}

class OffDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OffDialog(MachineTool* _machineTool, QWidget *parent = 0);
    ~OffDialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::OffDialog *ui;
    MachineTool* machineTool;

    void fillFields();
};

#endif // OFFDIALOG_H
