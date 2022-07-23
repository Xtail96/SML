#ifndef WEBSOCKETADAPTER_H
#define WEBSOCKETADAPTER_H

#include <QObject>

#include "libs/json_parser/json.h"

#include "./websocket_client.h"

class WebSocketAdapter : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketAdapter(QObject *parent = nullptr);
    ~WebSocketAdapter();

    void addClient(QWebSocket* s, QtJson::JsonObject intialState);

    void clearClients();

    bool isConnected() const;

    qint64 sendMessage(QByteArray message);

protected:
    QList<WebSocketClient*> m_clients;

    virtual void newMessageHandler(QtJson::JsonObject msg) = 0;
    virtual void onClientConnected(QtJson::JsonObject initialState) = 0;

private:
    void parseTextMessage(QString message);
    void parseBinaryMessage(QByteArray message);

signals:
    void connected();
    void disconnected();
};

#endif // WEBSOCKETADAPTER_H
