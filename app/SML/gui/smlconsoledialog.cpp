#include "smlconsoledialog.h"
#include "ui_smlconsoledialog.h"

SMLConsoleDialog::SMLConsoleDialog(MachineTool &machineTool, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SMLConsoleDialog),
    m_machineTool(machineTool)
{
    ui->setupUi(this);
    setup();
    setupWidgets();
}

SMLConsoleDialog::~SMLConsoleDialog()
{
    reset();
    delete ui;
}

void SMLConsoleDialog::setup()
{
    QObject::connect(ui->consolePlainTextEdit, SIGNAL(onCommand(QString)), this, SLOT(onCommand(QString)));
    QObject::connect(&m_machineTool, SIGNAL(sensorStateChanged(QString,QColor)), this, SLOT(onU1SensorStateChanged(QString,QColor)));
    QObject::connect(&m_machineTool, SIGNAL(u1Connected()), this, SLOT(onU1Connected()));
    QObject::connect(&m_machineTool, SIGNAL(u1Disconnected()), this, SLOT(onU1Disconnected()));
}

void SMLConsoleDialog::reset()
{
    QObject::disconnect(ui->consolePlainTextEdit, SIGNAL(onCommand(QString)), this, SLOT(onCommand(QString)));
    QObject::disconnect(&m_machineTool, SIGNAL(sensorStateChanged(QString,QColor)), this, SLOT(onU1SensorStateChanged(QString,QColor)));
    QObject::disconnect(&m_machineTool, SIGNAL(u1Connected()), this, SLOT(onU1Connected()));
    QObject::disconnect(&m_machineTool, SIGNAL(u1Disconnected()), this, SLOT(onU1Disconnected()));
}

void SMLConsoleDialog::setupWidgets()
{
    QPalette p = palette();
    p.setColor(QPalette::Base, SmlColors::gray());
    p.setColor(QPalette::Text, SmlColors::lightGreen());
    ui->monitorPlainTextEdit->setPalette(p);
}

void SMLConsoleDialog::sendCommang(QString cmd)
{
    ui->monitorPlainTextEdit->setPlainText(cmd);
    //m_machineTool->sendBinaryMessageToServer(cmd.toUtf8());
}

void SMLConsoleDialog::onCommand(QString cmd)
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

void SMLConsoleDialog::showMachineToolState(QString state)
{
    qDebug() << "state" << state;
    ui->monitorPlainTextEdit->setPlainText(state);
}

void SMLConsoleDialog::onU1Connected()
{
    showMachineToolState("U1 Connected");
}

void SMLConsoleDialog::onU1Disconnected()
{
    showMachineToolState("U1 Disconnected");
}

void SMLConsoleDialog::onU1SensorStateChanged(QString name, QColor led)
{
    QString u1State = name + QStringLiteral(":") + led.name();
    showMachineToolState(u1State);
}
