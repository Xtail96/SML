#ifndef ONDIALOG_H
#define ONDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"

namespace Ui {
class OnDialog;
}

class OnDialog : public QDialog, private CommandDialog
{
    Q_OBJECT

public:
    explicit OnDialog(QWidget *parent = 0);
    ~OnDialog();
private slots:
    void on_buttonBox_accepted();
private:
    Ui::OnDialog *ui;

    void fillFields();
};

#endif // ONDIALOG_H
