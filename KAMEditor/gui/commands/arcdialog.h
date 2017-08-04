#ifndef ARCDIALOG_H
#define ARCDIALOG_H

#include <QDialog>
#include <QTextStream>

#include "commanddialog.h"
#include "models/machinetool/machinetool.h"
#include "models/machinetool/commandsmanager/commands/arc.h"

namespace Ui {
class ArcDialog;
}

class ArcDialog : public QDialog//, private CommandDialog
{
    Q_OBJECT

public:
    explicit ArcDialog(MachineTool* _machineTool, QWidget *parent = 0);
    ~ArcDialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::ArcDialog *ui;
    MachineTool* machineTool;
};

#endif // ARCDIALOG_H
