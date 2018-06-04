#ifndef SMLCONSOLEDIALOG_H
#define SMLCONSOLEDIALOG_H

#include <QDialog>

#include "models/machinetool.h"

namespace Ui {
class SMLConsoleDialog;
}

class SMLConsoleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SMLConsoleDialog(MachineTool& machineTool, QWidget *parent = 0);
    ~SMLConsoleDialog();
protected:
    void setup();
    void reset();
    void setupWidgets();
private:
    Ui::SMLConsoleDialog *ui;
    MachineTool& m_machineTool;

protected slots:
    void sendCommang(QString cmd);
    void onCommand(QString cmd);
    void printResult(QString result);

    void showMachineToolState(QString state);

    void onU1Connected();
    void onU1Disconnected();
    void onU1StateChanged();
};

#endif // SMLCONSOLEDIALOG_H
