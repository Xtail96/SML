#include "sml_console_dialog.h"
#include "ui_sml_console_dialog.h"

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
    QObject::connect(&m_machineTool, SIGNAL(sensorStateChanged(QString,QColor)), this, SLOT(onSensorStateChanged(QString,QColor)));
    QObject::connect(&m_machineTool, SIGNAL(deviceAdapterConnected()), this, SLOT(onDeviceAdapterConnected()));
    QObject::connect(&m_machineTool, SIGNAL(deviceAdapterDisconnected()), this, SLOT(onDeviceAdapterDisconnected()));
}

void SMLConsoleDialog::reset()
{
    QObject::disconnect(ui->consolePlainTextEdit, SIGNAL(onCommand(QString)), this, SLOT(onCommand(QString)));
    QObject::disconnect(&m_machineTool, SIGNAL(sensorStateChanged(QString,QColor)), this, SLOT(onSensorStateChanged(QString,QColor)));
    QObject::disconnect(&m_machineTool, SIGNAL(deviceAdapterConnected()), this, SLOT(onDeviceAdapterConnected()));
    QObject::disconnect(&m_machineTool, SIGNAL(deviceAdapterDisconnected()), this, SLOT(onDeviceAdapterDisconnected()));
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

void SMLConsoleDialog::onDeviceAdapterConnected()
{
    showMachineToolState("Device Adapter Connected");
}

void SMLConsoleDialog::onDeviceAdapterDisconnected()
{
    showMachineToolState("Device Adapter Disconnected");
}

void SMLConsoleDialog::onSensorStateChanged(QString name, QColor led)
{
    QString state = name + QStringLiteral(":") + led.name();
    showMachineToolState(state);
}
