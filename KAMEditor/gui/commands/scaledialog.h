#ifndef SCALEDIALOG_H
#define SCALEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"

namespace Ui {
class ScaleDialog;
}

class ScaleDialog : public QDialog, private CommandDialog
{
    Q_OBJECT

public:
    explicit ScaleDialog(QWidget *parent = 0);
    ~ScaleDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ScaleDialog *ui;
};

#endif // SCALEDIALOG_H
