#ifndef PROCDIALOG_H
#define PROCDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class ProcDialog;
}

class ProcDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProcDialog(QWidget *parent = 0);
    ~ProcDialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::ProcDialog *ui;
};

#endif // PROCDIALOG_H
