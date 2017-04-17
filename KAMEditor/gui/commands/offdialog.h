#ifndef OFFDIALOG_H
#define OFFDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"

namespace Ui {
class OffDialog;
}

class OffDialog : public QDialog, private CommandDialog
{
    Q_OBJECT

public:
    explicit OffDialog(QWidget *parent = 0);
    ~OffDialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::OffDialog *ui;

    void fillFields();
};

#endif // OFFDIALOG_H
