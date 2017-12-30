#ifndef TTLINEDIALOG_H
#define TTLINEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class SMLTTLineDialog;
}

class SMLTTLineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SMLTTLineDialog(MainWindowController* _controller, size_t _index, QWidget *parent = 0, bool _edit = false);
    ~SMLTTLineDialog();

private slots:
    void on_buttonBox_accepted();
    void on_airPassageCheckBox_clicked();

private:
    Ui::SMLTTLineDialog *ui;

    MainWindowController* controller;
    size_t index;
    bool edit;

    void updateDZ();

    void fillFields();
};

#endif // TTLINEDIALOG_H
