#ifndef ONDIALOG_H
#define ONDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "models/machinetool/commandsmanager/commands/smlswitchon.h"
#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class SMLSwitchOnDialog;
}

class SMLSwitchOnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SMLSwitchOnDialog(MainWindowController* _controller, size_t _index, QWidget *parent = 0, bool _edit = false);

    ~SMLSwitchOnDialog();
private slots:
    void on_buttonBox_accepted();
private:
    Ui::SMLSwitchOnDialog *ui;
    MainWindowController *controller;
    size_t index;

    bool edit;
    void fillFields();
};

#endif // ONDIALOG_H
