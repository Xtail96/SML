#include "smlconsoledialog.h"
#include "ui_smlconsoledialog.h"

SMLConsoleDialog::SMLConsoleDialog(MainWindowPresenter *controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SMLConsoleDialog),
    m_controller(controller)
{
    ui->setupUi(this);
    setup();
}

SMLConsoleDialog::~SMLConsoleDialog()
{
    delete ui;
}

void SMLConsoleDialog::setup()
{
    connect(ui->consolePlainTextEdit, SIGNAL(onCommand(QString)), this, SLOT(handleCommand(QString)));
    connect(m_controller, SIGNAL(receivedMessage(QString)), this, SLOT(printResult(QString)));
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
