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
    explicit LineDialog(CommandsManager* _commandsManager, size_t _index, QWidget *parent = 0, bool _edit = false);
    ~LineDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::LineDialog *ui;
    CommandsManager* commandsManager;
    size_t index;
    bool edit;

    void fillFields();
};

#endif // LINEDIALOG_H
