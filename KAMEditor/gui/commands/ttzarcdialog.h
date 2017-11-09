#ifndef TTZARCDIALOG_H
#define TTZARCDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class TTZArcDialog;
}

class TTZArcDialog : public QDialog
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
