#ifndef MOTIONECHOADAPTER_H
#define MOTIONECHOADAPTER_H

#include <iostream>

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QThread>

#include "./task_worker.h"
#include "models/types/websockethandler/websockethandler.h"

class MotionEchoAdapter : public QObject
{
    Q_OBJECT
public:
    explicit MotionEchoAdapter(QObject *parent = nullptr);
    ~MotionEchoAdapter();

private:
    bool m_debugMode;
    SettingsManager m_settingsManager;
    WebSocketHandler *m_socketHandler;

    MotionControllerState m_currentState;
    bool m_processingTask;

    void loadSettings();
    void openPort(const QSerialPortInfo &info);

    void startInThread(QtJson::JsonObject message, bool debugMode = false, bool printState = false);
    void stopThreads();

    void sendCurrentStateToServer(MotionControllerState state);
    void printState(MotionControllerState state);
    void debugMessage(QString msg);

signals:
    void stopExecution(); //остановка всех потоков

protected slots:

    void onWebSocketHandler_Connected();
    void onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode code, QString message);
    void onWebSocketHandler_BinaryMessageReceived(QByteArray message);
};

#endif // MOTIONECHOADAPTER_H
