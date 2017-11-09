#ifndef SMLVARIABLEDIALOG_H
#define SMLVARIABLEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class SMLVariableDialog;
}

class SMLVariableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SMLVariableDialog(MainWindowController* _controller, size_t _index, QWidget *parent = 0, bool _edit = false);
    ~SMLVariableDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SMLVariableDialog *ui;

    MainWindowController* controller;
    size_t index;
    bool edit;

    void fillFields();
};

#endif // SMLVARIABLEDIALOG_H
