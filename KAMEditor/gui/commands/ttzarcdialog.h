#ifndef TTZARCDIALOG_H
#define TTZARCDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"

namespace Ui {
class TTZArcDialog;
}

class TTZArcDialog : public QDialog, private CommandDialog
{
    Q_OBJECT

public:
    explicit TTZArcDialog(QWidget *parent = 0);
    ~TTZArcDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::TTZArcDialog *ui;
};

#endif // TTZARCDIALOG_H
