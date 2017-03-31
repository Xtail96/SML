#ifndef ARC2DIALOG_H
#define ARC2DIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "commandinterpreter.h"

namespace Ui {
class Arc2Dialog;
}

class Arc2Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Arc2Dialog(QWidget *parent = 0);
    ~Arc2Dialog();

private slots:
    void on_buttonBox_accepted();

    void on_Arc2Dialog_rejected();

private:
    Ui::Arc2Dialog *ui;
};

#endif // ARC2DIALOG_H
