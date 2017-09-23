#ifndef LINEDIALOG_H
#define LINEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"
#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class LineDialog;
}

class LineDialog : public QDialog//, private CommandDialog
{
    Q_OBJECT

public:
    explicit LineDialog(MainWindowController* _controller, size_t _index, QWidget *parent = 0, bool _edit = false);
    ~LineDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::LineDialog *ui;
    MainWindowController* controller;
    size_t index;
    bool edit;

    void fillFields();
};

#endif // LINEDIALOG_H
