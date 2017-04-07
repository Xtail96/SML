#ifndef PAUSEDIALOG_H
#define PAUSEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"

namespace Ui {
class PauseDialog;
}

class PauseDialog : public QDialog, private CommandDialog
{
    Q_OBJECT

public:
    explicit PauseDialog(QWidget *parent = 0);
    ~PauseDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::PauseDialog *ui;
};

#endif // PAUSEDIALOG_H
