#ifndef TTTLINEDIALOG_H
#define TTTLINEDIALOG_H

#include <QDialog>
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

private:
    Ui::TTTLineDialog *ui;
};

#endif // TTTLINEDIALOG_H
