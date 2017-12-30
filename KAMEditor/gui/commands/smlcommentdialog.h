#ifndef COMMENTDIALOG_H
#define COMMENTDIALOG_H

#include <QDialog>
#include <QMessageBox>


#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class SMLCommentDialog;
}

class SMLCommentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SMLCommentDialog(MainWindowController* _controller, size_t _index, QWidget *parent = 0, bool _edit = false);
    ~SMLCommentDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SMLCommentDialog *ui;
    MainWindowController* controller;
    size_t index;
    bool edit;

    void fillFields();
};

#endif // COMMENTDIALOG_H
