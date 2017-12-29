#ifndef ARCDIALOG_H
#define ARCDIALOG_H

#include <QDialog>
#include <QTextStream>

#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class ArcDialog;
}

class ArcDialog : public QDialog//, private CommandDialog
{
    Q_OBJECT

public:
    explicit ArcDialog(MainWindowController* _controller, size_t _index, QWidget *parent = 0, bool _edit = false);
    ~ArcDialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::ArcDialog *ui;
    MainWindowController* controller;
    size_t index;
    bool edit;

    void fillFields();
};

#endif // ARCDIALOG_H
