#ifndef TTTLINEDIALOG_H
#define TTTLINEDIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "commandinterpreter.h"


namespace Ui {
class TTTLineDialog;
}

class TTTLineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TTTLineDialog(QWidget *parent = 0);
    ~TTTLineDialog();

private slots:
    void on_buttonBox_accepted();

    void on_TTTLineDialog_rejected();

private:
    Ui::TTTLineDialog *ui;
};

#endif // TTTLINEDIALOG_H
