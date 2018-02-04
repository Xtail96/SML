#include "smlconsoledialog.h"
#include "ui_smlconsoledialog.h"

SMLConsoleDialog::SMLConsoleDialog(MainWindowController *controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SMLConsoleDialog),
    m_controller(controller)
{
    ui->setupUi(this);
    m_controller->setServerDebug(true);
    setup();
}

SMLConsoleDialog::~SMLConsoleDialog()
{
    m_controller->setServerDebug(false);
    delete ui;
}

void SMLConsoleDialog::setup()
{
    connect(ui->consolePlainTextEdit, SIGNAL(onCommand(QString)), this, SLOT(sendCommang(QString)));
    connect(m_controller, SIGNAL(newDebugMessage(QString)), this, SLOT(printResult(QString)));
}

void SMLConsoleDialog::sendCommang(QString cmd)
{
    //m_controller->sendTextMessgeToServer(cmd);

    QByteArray array = cmd.toUtf8();
    m_controller->sendBinaryMessageToServer(array);

    //qDebug() << "test convert" << QByteArray(cmd, cmd.size());
}

void SMLConsoleDialog::printResult(QString result)
{
    ui->consolePlainTextEdit->output(result);
}
