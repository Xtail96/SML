#ifndef SMLSERVER_H
#define SMLSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

#include "libs/jsonparser/json.h"

#include "models/types/structs.h"
#include "models/types/server/u1state.h"

class SMLServer : public QObject
{
    Q_OBJECT
public:
    explicit SMLServer(size_t port, QObject *parent = nullptr);
    ~SMLServer();

    enum Type {Undefined, U1Adapter, U2Adapter};

protected:
    QScopedPointer<QWebSocketServer> m_server;
    qint16 m_port;

    QList< QWebSocket* > m_u1Connections;
    QList< QWebSocket* > m_u2Connections;
    QList< QWebSocket* > m_unregistered;

    bool m_debug;
signals:
    void newConnection();

    void u1Connected();
    void u1Disconnected();
    void u1StateChanged(QList<QVariant> sensors, QList<QVariant> devices, int error);

    void u2Connected();
    void u2Disconnected();

    void byteMessageReceived(QByteArray message);

public slots:
    void start();
    void stop();
    void sendMessageToU1(QByteArray message);

    QStringList currentAdapters();
    size_t port() const;

protected slots:
    void setupConnections();
    void resetConnections();

    void onServerClosed();
    void onNewConnection();
    void onTextMessage(QString message);
    void onBinaryMessage(QByteArray message);

    U1State parseU1BinaryMessage(QByteArray message);

    void socketDisconnected();
    void registerConnection(QWebSocket *connection, int type);
};

#endif // SMLRSERVER_H
