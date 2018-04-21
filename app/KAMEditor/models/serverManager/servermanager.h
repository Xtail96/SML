#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QObject>

#include "libs/jsonparser/json.h"

#include "models/structs.h"
#include "models/serverManager/smlkameditorserver/smlkameditorserver.h"
#include "models/settingsmanager/settingsmanager.h"

struct U1State
{
private:
    byte_array *sensorsState;
    byte_array *devicesState;
public:
    U1State(size_t sensorsPackageSize = 18, size_t devicesPackageSize = 1)
    {
        sensorsState = new byte_array(sensorsPackageSize, 0);
        devicesState = new byte_array(devicesPackageSize, 0);
    }

    ~U1State()
    {
        delete sensorsState;
        delete devicesState;
    }

    byte_array getSensorsState()
    {
        return *sensorsState;
    }

    void setSensorsState(byte_array value)
    {
        if(value.size() >= sensorsState->size())
        {
            for(size_t i = 0; i < sensorsState->size(); i++)
            {
                sensorsState->operator [](i) = value.operator [](i);
            }
        }
        else
        {
            qDebug() << "Попытка установить состояние датчиков неправильной длины" << value.size() << sensorsState->size();
        }
    }

    byte_array getDevicesState()
    {
        return *devicesState;
    }

    void setDevicesState(byte_array value)
    {
        if(value.size() == devicesState->size())
        {
            for(size_t i = 0; i < devicesState->size(); i++)
            {
                devicesState->operator [](i) = value.operator [](i);
            }
        }
        else
        {
            qDebug() << "Попытка установить состояние устройств неправильной длины";
        }
    }
};


class ServerManager : public QObject
{
    Q_OBJECT
public:
    explicit ServerManager(SettingsManager *settingsManager = nullptr, QObject *parent = nullptr);
    ~ServerManager();

protected:
    SMLKAMEditorServer *m_server;
    U1State *m_u1CurrentState;
    void setup(SettingsManager* settingsManager);

    void updateU1State(QList<QVariant> sensorsState, QList<QVariant> devicesState);
    void updateU1State(byte_array sensorsState, byte_array devicesState);

signals:
    void u1Connected();
    void u1Disconnected();
    void u2Connected();
    void u2Disconnected();

    void u1StateIsChanged();

public slots:
    void switchDevice(byte_array data);
    byte_array getSensorsState();
    byte_array getDevicesState();
    void startServer();
    void stopServer();
    QStringList getCurrentConnections();

protected slots:
    void onBinaryMessageReceived(QByteArray message);

    void onU1Connected();
    void onU1Disconnected();
    void onU2Connected();
    void onU2Disconnected();
};

#endif // SERVERMANAGER_H
