#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QtWebSockets>
#include <QObject>

#include "models/structs.h"
#include "models/settings_manager/settings_manager.h"

class WebSocketHandler : public QObject
{
    Q_OBJECT
protected:
    QUrl m_url; // QUrl(QStringLiteral("ws://localhost:1234"));
    QWebSocket *m_webSocket;
    bool m_debug;
    QTimer *m_timer;

    void loadSettings(const QString &settingsFileName);

public:
    WebSocketHandler(const QString& settingsFileName = "", QObject *parent = Q_NULLPTR);
    ~WebSocketHandler();

    void setDebug(bool debug);

signals:
    void machineToolStateIsChanged();
    void textMessageReceived(QString message);
    void binaryMessageReceived(QByteArray message);
    void connected();
    void disconnected(QWebSocketProtocol::CloseCode code, QString message = "Socket is disconnected from SML Server");

protected slots:
    void onQWebSocket_Connected();
    void onQWebSocket_Disconnected();
    void onQWebSocket_TextMessageReceived(QString message);
    void onQWebSocket_BinaryMessageReceived(QByteArray message);

public slots:
    void openWebSocket();
    void closeWebSocket();
    bool sendTextMessage(QString message);
    bool sendBinaryMessage(QByteArray message);
};


#endif // WEBSOCKETHANDLER_H
