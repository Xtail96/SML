#ifndef SMLSERVER_H
#define SMLSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

#include "libs/json_parser/json.h"

#include "models/types/exceptions/exceptions.h"

#include "models/types/structs.h"
#include "models/server/u1_state.h"

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

    void setupConnections();
    void resetConnections();

    void registerConnection(QWebSocket *connection, int type);

    void byteMessageReceived(QByteArray message);

    U1State parseU1BinaryMessage(QByteArray message);

signals:
    void newConnection();

    void u1Connected();
    void u1Disconnected();
    void u1StateChanged(QList<QVariant> sensors, QList<QVariant> devices, unsigned int workflowState, int lastError);

    void u2Connected();
    void u2Disconnected();

    void errorOccured(int code);

public slots:
    void start();
    void stop();
    void sendMessageToU1(QByteArray message);

    QStringList currentAdapters();
    size_t port() const;

protected slots:

    void onQWebSocketServer_Closed();
    void onQWebSocketServer_NewConnection();

    void onQWebSocket_TextMessageReceived(QString message);
    void onQWebSocket_BinaryMessageReceived(QByteArray message);
    void onQWebSocket_Disconnected();
};

#endif // SMLRSERVER_H
