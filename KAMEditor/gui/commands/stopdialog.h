#ifndef STOPDIALOG_H
#define STOPDIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "commanddialog.h"

namespace Ui {
class StopDialog;
}

class StopDialog : public QDialog, private CommandDialog
{
    Q_OBJECT

public:
    explicit StopDialog(QWidget *parent = 0);
    ~StopDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::StopDialog *ui;
};

#endif // STOPDIALOG_H
