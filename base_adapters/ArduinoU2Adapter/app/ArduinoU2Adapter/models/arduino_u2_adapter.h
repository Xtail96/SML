#ifndef U1SERIALADAPTER_H
#define U1SERIALADAPTER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#include "models/types/web_socket_handler/web_socket_handler.h"
#include "libs/jsonparser/json.h"

#include "models/types/axis/axis.h"

class ArduinoU2Adapter : public QObject
{
    Q_OBJECT
public:
    explicit ArduinoU2Adapter(QString portName, QObject *parent = nullptr);
    ~ArduinoU2Adapter();

private:
    SettingsManager m_settingsManager;

    QSerialPort *m_serial;
    QByteArray m_serialReadBuffer;

    WebSocketHandler *m_socketHandler;
    QList<Axis> m_axes;

    void loadSettings();

    void openPort(const QSerialPortInfo &info);
    void processMessageFromSerialPort(QString message);

signals:
    void portOpened();

private slots:

    void onQSerialPort_ReadyRead();
    void onWebSocketHandler_Connected();
    void onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode code, QString message);
    void onWebSocketHandler_BinaryMessageReceived(QByteArray message);

    void sendStateToServer();
};

#endif // U1SERIALADAPTER_H
