#ifndef PROGRAM_PROCESSING_DIALOG_H
#define PROGRAM_PROCESSING_DIALOG_H

#include <QDialog>

#include "models/machine_tool.h"
#include "models/services/program/prepare_execution_queue_interactor.h"

namespace Ui {
class ProgramProcessingDialog;
}

class ProgramProcessingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgramProcessingDialog(QWidget *parent = nullptr);
    ~ProgramProcessingDialog();

private:
    Ui::ProgramProcessingDialog *ui;

    void setupWidgets();
    void setupConnections();
    void resetConnections();

private slots:
    void onMachineTool_WorkflowStateChanged(unsigned int u1State, unsigned int u2State);
};

#endif // PROGRAM_PROCESSING_DIALOG_H
