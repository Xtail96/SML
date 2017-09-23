#ifndef TTLINEDIALOG_H
#define TTLINEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"
#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class TTLineDialog;
}

class TTLineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TTLineDialog(MainWindowController* _controller, size_t _index, QWidget *parent = 0, bool _edit = false);
    ~TTLineDialog();

private slots:
    void on_buttonBox_accepted();
    void on_airPassageCheckBox_clicked();

private:
    Ui::TTLineDialog *ui;

    MainWindowController* controller;
    size_t index;
    bool edit;

    void fillFields();
};

#endif // TTLINEDIALOG_H
