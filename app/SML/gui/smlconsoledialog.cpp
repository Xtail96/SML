#include "smlconsoledialog.h"
#include "ui_smlconsoledialog.h"

SMLConsoleDialog::SMLConsoleDialog(MachineTool &machineTool, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SMLConsoleDialog),
    m_machineTool(machineTool)
{
    ui->setupUi(this);
    setup();
}

SMLConsoleDialog::~SMLConsoleDialog()
{
    disconnect(ui->consolePlainTextEdit, SIGNAL(onCommand(QString)), this, SLOT(onCommand(QString)));
    disconnect(&m_machineTool, SIGNAL(u1StateIsChanged()), this, SLOT(onU1StateChanged()));
    disconnect(&m_machineTool, SIGNAL(u1Connected()), this, SLOT(onU1Connected()));
    disconnect(&m_machineTool, SIGNAL(u1Disconnected()), this, SLOT(onU1Disconnected()));
    delete ui;
}

void SMLConsoleDialog::setup()
{
    connect(ui->consolePlainTextEdit, SIGNAL(onCommand(QString)), this, SLOT(onCommand(QString)));
    connect(&m_machineTool, SIGNAL(u1StateIsChanged()), this, SLOT(onU1StateChanged()));
    connect(&m_machineTool, SIGNAL(u1Connected()), this, SLOT(onU1Connected()));
    connect(&m_machineTool, SIGNAL(u1Disconnected()), this, SLOT(onU1Disconnected()));
}

void SMLConsoleDialog::sendCommang(QString cmd)
{
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

void SMLConsoleDialog::onU1StateChanged()
{
    QString u1State = "";

    QPair< QStringList, QList<QColor> > sensors;
    sensors.first = m_machineTool.getSensorsLabels();
    sensors.second = m_machineTool.getSensorsLeds();

    u1State.push_back(QStringLiteral("---Sensors---") + QStringLiteral("\n"));

    for(int i = 0; i < sensors.first.size(); i++)
    {
        QString tmp = sensors.first[i] + QStringLiteral(":") + QString::number(sensors.second[i].value()) + QStringLiteral("\n");
        u1State.push_back(tmp);
    }

    u1State.push_back(QStringLiteral("---Devices---") + QStringLiteral("\n"));

    QPair< QStringList, QList<bool> > devices;
    devices.first = m_machineTool.getOnScreenDevicesNames();
    devices.second = m_machineTool.getOnScreenDevicesStates();

    for(int i = 0; i < devices.first.size(); i++)
    {
        QString tmp = devices.first[i] + QStringLiteral(":") + QString::number(devices.second[i]) + QStringLiteral("\n");
        u1State.push_back(tmp);
    }

    showMachineToolState(u1State);
}
