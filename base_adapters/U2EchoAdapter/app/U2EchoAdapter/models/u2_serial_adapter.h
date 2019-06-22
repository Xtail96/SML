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
    int m_lastErrorCode;
    int m_workflowState;
public:
    U2State(int errorCode, int workflowCode)
    {
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
};

class U2SerialAdapter : public QObject
{
    Q_OBJECT
public:
    explicit U2SerialAdapter(QString portName, QObject *parent = nullptr);
    ~U2SerialAdapter();

protected:
    SettingsManager m_settingsManager;
    WebSocketHandler *m_socketHandler;

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
