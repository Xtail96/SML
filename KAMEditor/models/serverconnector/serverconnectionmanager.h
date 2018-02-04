#ifndef SERVERCONNECTIONMANAGER_H
#define SERVERCONNECTIONMANAGER_H

#include <QtWebSockets>
#include <QObject>
#include <QJsonArray>

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

    void setup(SettingsManager *sm);
    void setupWebSocket(const QUrl &url, bool debug = false);
signals:
    void machineToolStateIsChanged();

public:
    ServerConnectionManager(const QUrl &url, SettingsManager *sm = nullptr, bool debug = false, QObject *parent = Q_NULLPTR);
    ~ServerConnectionManager();

    byte_array getSensorsState();
    void setSensorsState(byte_array value);

    std::map<std::string, double> getMachineToolCoordinates();

protected slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);
    void sendTextMessage(QString message);
};


#endif // SERVERCONNECTIONMANAGER_H
