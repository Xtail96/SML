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
    delete ui;
}

void SMLConsoleDialog::setup()
{
    connect(ui->consolePlainTextEdit, SIGNAL(onCommand(QString)), this, SLOT(sendCommang(QString)));
    connect(m_controller, SIGNAL(newDebugMessage(QJsonArray)), this, SLOT(printResult(QJsonArray)));
}

void SMLConsoleDialog::sendCommang(QString cmd)
{
    m_controller->sendTextMessgeToServer(cmd);
}

void SMLConsoleDialog::printResult(QJsonArray result)
{
    for(auto i : result)
    {
        ui->consolePlainTextEdit->output(i.toString());
    }
}
