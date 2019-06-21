#include "program_processing_dialog.h"
#include "ui_programprocessingdialog.h"

ProgramProcessingDialog::ProgramProcessingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgramProcessingDialog)
{
    ui->setupUi(this);

    this->setupWidgets();
    this->setupConnections();

    MachineTool &machineTool = MachineTool::getInstance();

    ui->messagesTextEdit->appendPlainText("Start program processing");
    machineTool.executeProgram();
}

ProgramProcessingDialog::~ProgramProcessingDialog()
{
    this->resetConnections();
    delete ui;
}

void ProgramProcessingDialog::setupWidgets()
{
    MachineTool &machineTool = MachineTool::getInstance();
    ui->programProcessingProgressBar->setMinimum(0);
    auto queueSize = PrepareExecutionQueueInteractor::execute(machineTool.getRepository().getGCodesProgram()).size();
    qDebug() << queueSize;
    ui->programProcessingProgressBar->setMaximum(2 * queueSize);
    ui->programProcessingProgressBar->setValue(0);
}

void ProgramProcessingDialog::setupConnections()
{
    MachineTool& machineTool = MachineTool::getInstance();
    QObject::connect(&machineTool, SIGNAL(programCompletedSuccesfully()), this, SLOT(close()));
    QObject::connect(&machineTool, SIGNAL(workflowStateChanged(unsigned int, unsigned int)), this, SLOT(onMachineTool_WorkflowStateChanged(unsigned int, unsigned int)));

}

void ProgramProcessingDialog::resetConnections()
{
    MachineTool& machineTool = MachineTool::getInstance();
    QObject::disconnect(&machineTool, SIGNAL(programCompletedSuccesfully()), this, SLOT(close()));
    QObject::disconnect(&machineTool, SIGNAL(workflowStateChanged(unsigned int, unsigned int)), this, SLOT(onMachineTool_WorkflowStateChanged(unsigned int, unsigned int)));
}

void ProgramProcessingDialog::onMachineTool_WorkflowStateChanged(unsigned int u1State, unsigned int u2State)
{
    ui->messagesTextEdit->appendPlainText("WorkflowStateChanged. U1State = " + QString::number(u1State) + ", U2State = " + QString::number(u2State));
    int currentProgress = ui->programProcessingProgressBar->value();
    ui->programProcessingProgressBar->setValue(currentProgress + 1);
}
