#ifndef U1SERIALADAPTER_H
#define U1SERIALADAPTER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#include "models/web_socket_handler/web_socket_handler.h"
#include "models/repository/repository.h"

class ArduinoU2Adapter : public QObject
{
    Q_OBJECT
public:
    static ArduinoU2Adapter& getInstance();
    ~ArduinoU2Adapter();

    Repository& getRepository();

private:
    explicit ArduinoU2Adapter(QObject *parent = nullptr);

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

#endif // U1SERIALADAPTER_H
