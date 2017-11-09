#ifndef TTTARCDIALOG_H
#define TTTARCDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class TTTArcDialog;
}

class TTTArcDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TTTArcDialog(QWidget *parent = 0);
    ~TTTArcDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::TTTArcDialog *ui;
};

#endif // TTTARCDIALOG_H
