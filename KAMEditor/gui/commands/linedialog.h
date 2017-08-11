#ifndef LINEDIALOG_H
#define LINEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"
#include "models/machinetool/machinetool.h"
#include "models/machinetool/commandsmanager/commands/line.h"

namespace Ui {
class LineDialog;
}

class LineDialog : public QDialog//, private CommandDialog
{
    Q_OBJECT

public:
    explicit LineDialog(CommandsManager* _commandsManager, int _position, QWidget *parent = 0);
    ~LineDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::LineDialog *ui;
    CommandsManager* commandsManager;
    int position;
};

#endif // LINEDIALOG_H
