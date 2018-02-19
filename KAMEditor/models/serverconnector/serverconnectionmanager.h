#ifndef SERVERCONNECTIONMANAGER_H
#define SERVERCONNECTIONMANAGER_H

#include <QtWebSockets>
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QProcess>

#include "models/structs.h"
#include "models/machinetool/settingsmanager/settingsmanager.h"
#include "jsonparser/json.h"

struct AxisesStateList
{
private:
    std::map<std::string, double> axisesState;
public:
    AxisesStateList(size_t count = 3)
    {
        for(size_t i = 0; i < count; i++)
        {
            std::string name = axisesNames.getNameByKey(i);
            axisesState.insert(std::make_pair(name, 0));
        }
    }

    std::map<std::string, double> getAxisesCoordinates()
    {
        return axisesState;
    }
};

struct U1State
{
private:
    byte_array *sensorsState;
    byte_array *devicesState;
public:
    U1State(size_t sensorsPackageSize = 16, size_t devicesPackageSize = 1)
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
        if(value.size() == sensorsState->size())
        {
            for(size_t i = 0; i < sensorsState->size(); i++)
            {
                sensorsState->operator [](i) = value.operator [](i);
            }
        }
        else
        {
            qDebug() << "Попытка установить состояние датчиков неправильной длины";
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
            qDebug() << "Попытка установить состояние датчиков неправильной длины";
        }
    }
};

class ServerConnectionManager : public QObject
{
    Q_OBJECT

protected:
    QUrl m_url;
    U1State *m_u1CurrentState;
    QWebSocket *m_webSocket;
    bool m_debug;

    void setup(SettingsManager *sm);

public:
    ServerConnectionManager(SettingsManager *sm = nullptr, bool debug = false, QObject *parent = Q_NULLPTR);
    ~ServerConnectionManager();

    byte_array getSensorsState();
    void setU1CurrentState(byte_array sensorsState, byte_array devicesState);
    void setU1CurrentState(QList<QVariant> sensorsState, QList<QVariant> devicesState);

    std::map<std::string, double> getMachineToolCoordinates();

    void setDebug(bool debug);

signals:
    void u1StateIsChanged();
    void textMessageReceived(QString message);
    void binaryMessageReceived(QByteArray message);
    void serverIsConnected();
    void serverIsDisconnected(QString message = "Server is disconnected");

protected slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);
    void onBinaryMessageReceived(QByteArray message);

public slots:
    void openWebSocket();
    void closeWebSocket();
    bool sendTextMessage(QString message);
    bool sendBinaryMessage(QByteArray message);
};


#endif // SERVERCONNECTIONMANAGER_H
