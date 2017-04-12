#ifndef SPLINEDIALOG_H
#define SPLINEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"

namespace Ui {
class SplineDialog;
}

class SplineDialog : public QDialog, private CommandDialog
{
    Q_OBJECT

public:
    explicit SplineDialog(QWidget *parent = 0);
    ~SplineDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SplineDialog *ui;
};

#endif // SPLINEDIALOG_H
