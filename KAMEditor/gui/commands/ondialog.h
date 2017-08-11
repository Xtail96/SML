#ifndef ONDIALOG_H
#define ONDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"
#include "models/machinetool/machinetool.h"
#include "models/machinetool/commandsmanager/commands/switchon.h"

namespace Ui {
class OnDialog;
}

class OnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OnDialog(DevicesManager* _devicesManager, CommandsManager* _commandsManager, size_t _position, QWidget *parent = 0);
    ~OnDialog();
private slots:
    void on_buttonBox_accepted();
private:
    Ui::OnDialog *ui;
    DevicesManager* devicesManager;
    CommandsManager* commandsManager;
    size_t position;

    void fillFields();
};

#endif // ONDIALOG_H
