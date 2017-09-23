#ifndef COMMENTDIALOG_H
#define COMMENTDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"
#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class CommentDialog;
}

class CommentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CommentDialog(MainWindowController* _controller, size_t _index, QWidget *parent = 0, bool _edit = false);
    ~CommentDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CommentDialog *ui;
    MainWindowController* controller;
    size_t index;
    bool edit;

    void fillFields();
};

#endif // COMMENTDIALOG_H
