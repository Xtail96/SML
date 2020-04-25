#ifndef U1SERIALADAPTER_H
#define U1SERIALADAPTER_H

#include <iostream>

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QThread>

#include "models/types/websockethandler/websockethandler.h"
#include "libs/jsonparser/json.h"

struct U2State
{
private:
    QMap<QString, double> m_positions;
    int m_lastErrorCode;
    int m_workflowState;
public:
    U2State(int errorCode, int workflowCode)
    {
        m_positions = {};
        m_lastErrorCode = errorCode;
        m_workflowState = workflowCode;
    }

    ~U2State() {}

    byte getLastError()
    {
        return m_lastErrorCode;
    }

    void setLastError(byte value)
    {
        m_lastErrorCode = value;
    }

    int getWorkflowState()
    {
        return m_workflowState;
    }

    void setWorkflowState(int value)
    {
        m_workflowState = value;
    }

    int getAxesCount()
    {
        return m_positions.size();
    }

    QStringList getAxisesKeys()
    {
        return m_positions.keys();
    }

    double getAxisPosition(QString key)
    {
        if(!m_positions.contains(key))
            throw std::invalid_argument("Unknown axis name " + key.toStdString());

        return m_positions[key];
    }

    void setAxisPosition(QString key, double value)
    {
        if(!m_positions.contains(key))
            throw std::invalid_argument("Unknown axis name " + key.toStdString());

        this->removeAxisPosition(key);
        this->addAxisPosition(key, value);
    }

    void addAxisPosition(QString key, double value)
    {
        m_positions.insert(key, value);
    }

    void removeAxisPosition(QString key)
    {
        if(!m_positions.contains(key))
            throw std::invalid_argument("Unknown axis name " + key.toStdString());

        m_positions.remove(key);
    }
};

class U2SerialAdapter : public QObject
{
    Q_OBJECT
public:
    explicit U2SerialAdapter(QObject *parent = nullptr);
    ~U2SerialAdapter();

private:
    SettingsManager m_settingsManager;
    WebSocketHandler *m_socketHandler;

    U2State m_currentState;

    void loadSettings();

    void openPort(const QSerialPortInfo &info);
    void printState(U2State state);

signals:

protected slots:

    void onWebSocketHandler_Connected();
    void onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode code, QString message);
    void onWebSocketHandler_BinaryMessageReceived(QByteArray message);

    void sendCurrentStateToServer(U2State state);

    void sendTestPackageToServer();
};

#endif // U1SERIALADAPTER_H
