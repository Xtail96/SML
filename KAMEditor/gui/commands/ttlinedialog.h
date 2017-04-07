#ifndef TTLINEDIALOG_H
#define TTLINEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"


namespace Ui {
class TTLineDialog;
}

class TTLineDialog : public QDialog, private CommandDialog
{
    Q_OBJECT

public:
    explicit TTLineDialog(QWidget *parent = 0);
    ~TTLineDialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::TTLineDialog *ui;
};

#endif // TTLINEDIALOG_H
