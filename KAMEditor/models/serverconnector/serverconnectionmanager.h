#ifndef SERVERCONNECTIONMANAGER_H
#define SERVERCONNECTIONMANAGER_H

#include <QtWebSockets>
#include <QObject>

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
public:
    ServerConnectionManager();
    ~ServerConnectionManager();

    byte_array getSensorsState();
    void setSensorsState(byte_array value);

    std::map<std::string, double> getMachineToolCoordinates();
signals:
    void machineToolStateIsChanged();
private:
    MachineToolState* currentState;

};


#endif // SERVERCONNECTIONMANAGER_H
