#ifndef TTTTSPLINEDIALOG_H
#define TTTTSPLINEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"

namespace Ui {
class TTTTSplineDialog;
}

class TTTTSplineDialog : public QDialog, private CommandDialog
{
    Q_OBJECT

public:
    explicit TTTTSplineDialog(QWidget *parent = 0);
    ~TTTTSplineDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::TTTTSplineDialog *ui;
};

#endif // TTTTSPLINEDIALOG_H
