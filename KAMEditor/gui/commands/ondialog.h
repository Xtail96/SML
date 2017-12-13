#ifndef ONDIALOG_H
#define ONDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "models/machinetool/commandsmanager/commands/smlswitchon.h"
#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class OnDialog;
}

class OnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OnDialog(MainWindowController* _controller, size_t _index, QWidget *parent = 0, bool _edit = false);

    ~OnDialog();
private slots:
    void on_buttonBox_accepted();
private:
    Ui::OnDialog *ui;
    MainWindowController *controller;
    size_t index;

    bool edit;
    void fillFields();
};

#endif // ONDIALOG_H
