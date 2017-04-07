#ifndef CALLPROCDIALOG_H
#define CALLPROCDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"


namespace Ui {
class CallProcDialog;
}

class CallProcDialog : public QDialog, private CommandDialog
{
    Q_OBJECT

public:
    explicit CallProcDialog(QWidget *parent = 0);
    ~CallProcDialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::CallProcDialog *ui;
};

#endif // CALLPROCDIALOG_H
