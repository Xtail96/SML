#ifndef CALLPROCDIALOG_H
#define CALLPROCDIALOG_H

#include <QDialog>
#include <QMessageBox>


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
private:
    Ui::CallProcDialog *ui;
};

#endif // CALLPROCDIALOG_H
