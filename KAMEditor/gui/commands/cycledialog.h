#ifndef CYCLEDIALOG_H
#define CYCLEDIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "commandinterpreter.h"


namespace Ui {
class CycleDialog;
}

class CycleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CycleDialog(QWidget *parent = 0);
    ~CycleDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CycleDialog *ui;
};

#endif // CYCLEDIALOG_H