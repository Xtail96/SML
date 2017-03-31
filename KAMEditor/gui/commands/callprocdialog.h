#ifndef CALLPROCDIALOG_H
#define CALLPROCDIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "commandinterpreter.h"


namespace Ui {
class CallProcDialog;
}

class CallProcDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CallProcDialog(QWidget *parent = 0);
    ~CallProcDialog();

private slots:
    void on_buttonBox_accepted();

    void on_CallProcDialog_rejected();

private:
    Ui::CallProcDialog *ui;
};

#endif // CALLPROCDIALOG_H
