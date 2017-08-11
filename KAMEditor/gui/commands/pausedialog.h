#ifndef PAUSEDIALOG_H
#define PAUSEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"
#include "models/machinetool/machinetool.h"
#include "models/machinetool/commandsmanager/commands/pause.h"

namespace Ui {
class PauseDialog;
}

class PauseDialog : public QDialog//, private CommandDialog
{
    Q_OBJECT

public:
    explicit PauseDialog(CommandsManager* _commandsManager, int _position, QWidget *parent = 0);
    ~PauseDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::PauseDialog *ui;
    CommandsManager* commandsManager;
    int position;
};

#endif // PAUSEDIALOG_H
