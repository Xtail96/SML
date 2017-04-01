#ifndef COMMENTDIALOG_H
#define COMMENTDIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "commanddialog.h"

namespace Ui {
class CommentDialog;
}

class CommentDialog : public QDialog, private CommandDialog
{
    Q_OBJECT

public:
    explicit CommentDialog(QWidget *parent = 0);
    ~CommentDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CommentDialog *ui;
};

#endif // COMMENTDIALOG_H
