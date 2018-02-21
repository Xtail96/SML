#include "smlconsoledialog.h"
#include "ui_smlconsoledialog.h"

SMLConsoleDialog::SMLConsoleDialog(MainWindowController *controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SMLConsoleDialog),
    m_controller(controller)
{
    ui->setupUi(this);
    setup();
}

SMLConsoleDialog::~SMLConsoleDialog()
{
    m_controller->setServerDebug(false);
    delete ui;
}

void SMLConsoleDialog::setup()
{
    connect(ui->consolePlainTextEdit, SIGNAL(onCommand(QString)), this, SLOT(handleCommang(QString)));
    connect(m_controller, SIGNAL(receivedDebugMessage(QString)), this, SLOT(printResult(QString)));
    connect(m_controller, SIGNAL(machineToolIsDisconnected(QString)), this, SLOT(handleMachineToolDisconnected(QString)));
}

void SMLConsoleDialog::sendCommang(QString cmd)
{
    m_controller->sendBinaryMessageToServer(cmd.toUtf8());
}

void SMLConsoleDialog::handleCommand(QString cmd)
{
    if(cmd == "debug")
    {
        m_controller->setServerDebug(true);
    }
    else
    {
        sendCommang(cmd);
    }
}

void SMLConsoleDialog::printResult(QString result)
{
    ui->consolePlainTextEdit->output(result);
}

void SMLConsoleDialog::handleMachineToolDisconnected(QString message)
{
    ui->consolePlainTextEdit->output(QString("Error: machineTool is disconnected with message:") + message);
}
