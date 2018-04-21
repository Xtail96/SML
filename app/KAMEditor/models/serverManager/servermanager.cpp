#include "servermanager.h"

ServerManager::ServerManager(SettingsManager *settingsManager, QObject *parent) :
    QObject(parent),
    m_server(new SMLKAMEditorServer(settingsManager, this)),
    m_u1CurrentState(nullptr)
{
    if(settingsManager != nullptr)
    {
        setup(settingsManager);
    }
    else
    {
        SettingsManager* sm = new SettingsManager();
        setup(sm);
        delete sm;
    }
}

ServerManager::~ServerManager()
{
    delete m_u1CurrentState;
    delete m_server;
}

void ServerManager::setup(SettingsManager *settingsManager)
{
    try
    {
        size_t sensorsPackageSize = settingsManager->get("MachineToolInformation", "SensorsBufferSize").toUInt();
        size_t devicesPackageSize = settingsManager->get("MachineToolInformation", "DevicesBufferSize").toUInt();
        m_u1CurrentState = new U1State(sensorsPackageSize, devicesPackageSize);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Settings Error", e.what()).exec();
    }
    connect(m_server, SIGNAL(byteMessageReceived(QByteArray)), this, SLOT(onBinaryMessageReceived(QByteArray)));
    connect(m_server, SIGNAL(u1Connected()), this, SLOT(onU1Connected()));
    connect(m_server, SIGNAL(u1Disconnected()), this, SLOT(onU1Disconnected()));
    connect(m_server, SIGNAL(u2Connected()), this, SLOT(onU2Connected()));
    connect(m_server, SIGNAL(u2Disconnected()), this, SLOT(onU2Disconnected()));
}

void ServerManager::updateU1State(QList<QVariant> sensorsState, QList<QVariant> devicesState)
{
    byte_array currentSensorsState;
    for(auto group : sensorsState)
    {
        currentSensorsState.push_back(group.toUInt());
    }

    byte_array currentDevicesState;
    for(auto group : devicesState)
    {
        currentDevicesState.push_back(group.toUInt());
    }

    updateU1State(currentSensorsState, currentDevicesState);
}

void ServerManager::updateU1State(byte_array sensorsState, byte_array devicesState)
{
    m_u1CurrentState->setSensorsState(sensorsState);
    m_u1CurrentState->setDevicesState(devicesState);
    emit u1StateIsChanged();
}

void ServerManager::switchDevice(byte_array data)
{
    QtJson::JsonObject generalMessage;
    QtJson::JsonObject u1Message;
    QtJson::JsonArray u1Data;

    for(auto byte_unit : data)
    {
        u1Data.push_back(byte_unit);
    }
    u1Message["SwitchDevice"] = u1Data;
    generalMessage["MessageToU1"] = u1Message;

    bool ok = false;
    QByteArray message = QtJson::serialize(generalMessage, ok);
    qDebug() << "Try to switch device =" << message;
    if(ok)
    {
        m_server->sendMessageToU1(message);
    }
}

byte_array ServerManager::getSensorsState()
{
    return m_u1CurrentState->getSensorsState();
}

byte_array ServerManager::getDevicesState()
{
    return m_u1CurrentState->getDevicesState();
}

void ServerManager::startServer()
{
    m_server->start();
}

void ServerManager::stopServer()
{
    m_server->stop();
}

void ServerManager::onBinaryMessageReceived(QByteArray message)
{
    bool ok;
    QString json = QString::fromUtf8(message);
    QtJson::JsonObject result = QtJson::parse(json, ok).toMap();
    if(ok)
    {
        QtJson::JsonObject u1State = result["U1State"].toMap();
        if(!u1State.isEmpty())
        {
            QList<QVariant> sensorsState = u1State["SensorsState"].toList();
            //qDebug() << sensorsState;
            QList<QVariant> devicesState = u1State["DevicesState"].toList();
            //qDebug() << devicesState;
            updateU1State(sensorsState, devicesState);
        }

        //QtJson::JsonObject u2State = result["U2State"].toMap();
        //qDebug() << !(u2State.isEmpty());
    }
    else
    {
        qDebug() << "an error is occured during parsing json" << QString::fromUtf8(message);
    }
}

void ServerManager::onU1Connected()
{
    emit u1Connected();
}

void ServerManager::onU1Disconnected()
{
    emit u1Disconnected();
}

void ServerManager::onU2Connected()
{
    emit u2Connected();
}

void ServerManager::onU2Disconnected()
{
    emit u2Disconnected();
}
