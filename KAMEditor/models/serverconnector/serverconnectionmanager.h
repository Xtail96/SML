#ifndef SERVERCONNECTIONMANAGER_H
#define SERVERCONNECTIONMANAGER_H

#include <QtWebSockets>
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

#include "models/structs.h"
#include "models/machinetool/settingsmanager/settingsmanager.h"

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

struct SensorsStateList
{
private:
    byte_array sensorsState;
public:
    SensorsStateList(size_t count = 16)
    {
        sensorsState = byte_array(count, 0);
    }

    byte_array getSensorsState()
    {
        return sensorsState;
    }

    void setSensorsState(byte_array value)
    {
        if(value.size() == sensorsState.size())
        {
            sensorsState = value;
        }
        else
        {
            qDebug() << "Попытка установить состояние датчиков неправильной длины";
        }
    }
};

struct MachineToolState
{
    AxisesStateList axisesState;
    SensorsStateList sensorsState;

    MachineToolState(size_t axisesCount = 3, size_t sensorsCount = 16) :
        axisesState(axisesCount),
        sensorsState(sensorsCount){}
};

class ServerConnectionManager : public QObject
{
    Q_OBJECT
protected:
    MachineToolState *currentState;
    QWebSocket *m_webSocket;
    QUrl m_url;
    bool m_debug;
    QString serverApplicationLocation;

    void setup(SettingsManager *sm);
    void startServer();

public:
    ServerConnectionManager(SettingsManager *sm = nullptr, bool debug = false, QObject *parent = Q_NULLPTR);
    ~ServerConnectionManager();

    void openWebSocket();
    void stopServer();

    byte_array getSensorsState();
    void setSensorsState(byte_array value);

    std::map<std::string, double> getMachineToolCoordinates();

    void setDebug(bool debug);

signals:
    void machineToolStateIsChanged();
    void textMessageReceived(QString message);

protected slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);
    void onBinaryMessageReceived(QByteArray message);

public slots:
    void sendTextMessage(QString message);
    void sendBinaryMessage(QByteArray message);
};


#endif // SERVERCONNECTIONMANAGER_H
