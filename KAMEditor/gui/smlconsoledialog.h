#ifndef SMLCONSOLEDIALOG_H
#define SMLCONSOLEDIALOG_H

#include <QDialog>

#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class SMLConsoleDialog;
}

class SMLConsoleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SMLConsoleDialog(MainWindowController* controller, QWidget *parent = 0);
    ~SMLConsoleDialog();
protected:
    void setup();
private:
    Ui::SMLConsoleDialog *ui;
    MainWindowController *m_controller;

protected slots:
    void sendCommang(QString cmd);
    void printResult(QJsonArray result);
};

#endif // SMLCONSOLEDIALOG_H
