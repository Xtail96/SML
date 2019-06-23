#ifndef U1SERIALADAPTER_H
#define U1SERIALADAPTER_H

#include <iostream>

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#include "models/types/websockethandler/websockethandler.h"
#include "libs/jsonparser/json.h"

const char SWITCH_DEVICE_OFF = 0x00;
const char SWITCH_DEVICE_ON = 0x01;

struct U1State
{
private:
    byte_array *m_sensorsState;
    byte_array *m_devicesState;
    byte m_lastErrorCode;
public:
    U1State(size_t sensorsPackageSize = 2, size_t devicesPackageSize = 3)
    {
        m_sensorsState = new byte_array(sensorsPackageSize, 0xff);
        m_devicesState = new byte_array(devicesPackageSize, 0x00);
        m_lastErrorCode = 0x00;
    }

    ~U1State()
    {
        delete m_sensorsState;
        delete m_devicesState;
    }

    byte_array getSensorsState()
    {
        return *m_sensorsState;
    }

    void setSensorsState(byte_array value)
    {
        if(value.size() == m_sensorsState->size())
        {
            for(size_t i = 0; i < m_sensorsState->size(); i++)
            {
                m_sensorsState->operator [](i) = value.operator [](i);
            }
        }
        else
        {
            qDebug() << "Попытка установить состояние датчиков неправильной длины."
                     << "Исходная длина = " << m_sensorsState->size() << "."
                     << "Новая длина = " << value.size();
        }
    }

    byte_array getDevicesState()
    {
        return *m_devicesState;
    }

    void setDevicesState(byte_array value)
    {
        if(value.size() == m_devicesState->size())
        {
            for(size_t i = 0; i < m_devicesState->size(); i++)
            {
                m_devicesState->operator [](i) = value.operator [](i);
            }
        }
        else
        {
            qDebug() << "Попытка установить состояние устройств неправильной длины."
                     << "Исходная длина = " << m_devicesState->size() << "."
                     << "Новая длина = " << value.size();
        }
    }

    byte getLastError()
    {
        return m_lastErrorCode;
    }

    void setLastError(byte value)
    {
        m_lastErrorCode = value;
    }
};

class U1SerialAdapter : public QObject
{
    Q_OBJECT
public:
    explicit U1SerialAdapter(QString portName, QObject *parent = nullptr);
    ~U1SerialAdapter();

protected:
    SettingsManager m_settingsManager;

    QSerialPort *m_serial;
    WebSocketHandler *m_socketHandler;
    U1State *m_currentState;
    U1State *m_previousState;

    void loadSettings();

    void openPort(const QSerialPortInfo &info);
    bool isStateChanged();
    void printState();

signals:
    void portOpened();
    void readFromPort(QByteArray state);

protected slots:

    void onQSerialPort_ReadyRead();
    void onQSerialPort_ReadFromPort(QByteArray received);
    void switchDevice(byte_array data);
    void switchDevice(size_t index, QString target, QString type);


    void onWebSocketHandler_Connected();
    void onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode code, QString message);
    void onWebSocketHandler_BinaryMessageReceived(QByteArray message);

    void sendStateToServer(U1State *state);

    void sendTestPackageToServer();
};

#endif // U1SERIALADAPTER_H
