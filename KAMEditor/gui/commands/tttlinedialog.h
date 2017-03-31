#ifndef TTTLINEDIALOG_H
#define TTTLINEDIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "commanddialog.h"


namespace Ui {
class TTTLineDialog;
}

class TTTLineDialog : public QDialog, private CommandDialog
{
    Q_OBJECT

public:
    explicit TTTLineDialog(QWidget *parent = 0);
    ~TTTLineDialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::TTTLineDialog *ui;
};

#endif // TTTLINEDIALOG_H
