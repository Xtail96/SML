#ifndef TTTARCDIALOG_H
#define TTTARCDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"

namespace Ui {
class TTTArcDialog;
}

class TTTArcDialog : public QDialog, private CommandDialog
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
