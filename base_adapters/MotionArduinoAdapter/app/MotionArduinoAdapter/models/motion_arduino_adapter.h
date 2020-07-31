#ifndef MOTIONARDUINOADAPTER_H
#define MOTIONARDUINOADAPTER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#include "models/web_socket_handler/web_socket_handler.h"
#include "models/repository/repository.h"

class MotionArduinoAdapter : public QObject
{
    Q_OBJECT
public:
    static MotionArduinoAdapter& getInstance();
    ~MotionArduinoAdapter();

    Repository& getRepository();

private:
    explicit MotionArduinoAdapter(QObject *parent = nullptr);

    QSerialPort *m_serial;
    WebSocketHandler *m_socketHandler;
    Repository m_repository;

    void openSerialPort(const QSerialPortInfo &info);
    void processMessageFromSerialPort(QString message);

signals:
    void serialPortOpened();

private slots:
    void onQSerialPort_ReadyRead();

    void onWebSocketHandler_Connected();
    void onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode code, QString message);
    void onWebSocketHandler_BinaryMessageReceived(QByteArray message);

    void sendStateToServer();
};

#endif // MOTIONARDUINOADAPTER_H
