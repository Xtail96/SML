#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>

#include "libs/json_parser/json.h"

#include "./websocket_connection.h"

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketClient(QObject *parent = nullptr);
    ~WebSocketClient();

    void createConnection(QWebSocket* s, QtJson::JsonObject intialState);

    void clearConnections();

    bool isConnected() const;

    qint64 sendMessage(QByteArray message);

protected:
    QList<WebSocketConnection*> m_connections;

    virtual void onMessageReceived(QtJson::JsonObject msg) = 0;
    virtual void onClientConnected(QtJson::JsonObject initialState) = 0;

private:
    void parseTextMessage(QString message);
    void parseBinaryMessage(QByteArray message);

signals:
    void connected();
    void disconnected();
};

#endif // WEBSOCKETCLIENT_H
