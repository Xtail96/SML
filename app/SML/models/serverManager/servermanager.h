#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QObject>

#include "libs/jsonparser/json.h"

#include "models/structs.h"
#include "models/serverManager/smlkameditorserver/smlserver.h"
#include "models/settingsmanager/settingsmanager.h"

struct U1State
{
private:
    byte_array m_sensorsState;
    byte_array m_devicesState;
    int m_lastError;
public:
    U1State(size_t sensorsPackageSize = 18, size_t devicesPackageSize = 1, int lastError = 0)
    {
        m_sensorsState = byte_array(sensorsPackageSize, 0);
        m_devicesState = byte_array(devicesPackageSize, 0);
        m_lastError = lastError;
    }

    ~U1State()
    {

    }

    byte_array getSensorsState()
    {
        return m_sensorsState;
    }

    void setSensorsState(byte_array value)
    {
        if(value.size() >= m_sensorsState.size())
        {
            for(size_t i = 0; i < m_sensorsState.size(); i++)
            {
                m_sensorsState.operator [](i) = value.operator [](i);
            }
        }
        else
        {
            qDebug() << "Попытка установить состояние датчиков неправильной длины" << value.size() << m_sensorsState.size();
        }
    }

    byte_array getDevicesState()
    {
        return m_devicesState;
    }

    void setDevicesState(byte_array value)
    {
        if(value.size() == m_devicesState.size())
        {
            for(size_t i = 0; i < m_devicesState.size(); i++)
            {
                m_devicesState.operator [](i) = value.operator [](i);
            }
        }
        else
        {
            qDebug() << "Попытка установить состояние устройств неправильной длины";
        }
    }

    int getLastError()
    {
        return m_lastError;
    }

    void setLastEror(int lastError)
    {
        m_lastError = lastError;
    }
};


class ServerManager : public QObject
{
    Q_OBJECT
public:
    explicit ServerManager(const SettingsManager &settingsManager = SettingsManager(), QObject *parent = nullptr);
    ~ServerManager();

protected:
    QScopedPointer<SMLServer> m_server;
    U1State m_u1CurrentState;
    void setup(const SettingsManager& settingsManager);

    void updateU1State(QList<QVariant> sensorsState, QList<QVariant> devicesState, int lastError);
    void updateU1State(byte_array sensorsState, byte_array devicesState, int lastError);

signals:
    void u1Connected();
    void u1Disconnected();
    void u2Connected();
    void u2Disconnected();

    void u1StateIsChanged();
    void u1ErrorIsOccured(int errorCode);

public slots:
    void switchDevice(byte_array data);
    byte_array getSensorsState();
    byte_array getDevicesState();
    void startServer();
    void stopServer();
    QStringList getCurrentConnections();
    size_t getServerPort();
    size_t getSensorsBufferSize();
    size_t getDevicesBufferSize();

protected slots:
    void onBinaryMessageReceived(QByteArray message);

    void onU1Connected();
    void onU1Disconnected();
    void onU2Connected();
    void onU2Disconnected();
};

#endif // SERVERMANAGER_H
