#ifndef SMLKAMEDITORSERVER_H
#define SMLKAMEDITORSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

#include "models/structs.h"
#include "models/settingsmanager/settingsmanager.h"

enum Role {U1Adapter, U2Adapter};

struct Adapter
{
protected:
    Role m_name;
    QWebSocket* m_socket;

public:
    explicit Adapter(Role name, QWebSocket* socket) : m_name(name), m_socket(socket){}
    ~Adapter() {}

    Role name() const
    {
        return m_name;
    }

    QWebSocket* socket() const
    {
        return m_socket;
    }
};

class SMLKAMEditorServer : public QObject
{
    Q_OBJECT
public:
    explicit SMLKAMEditorServer(SettingsManager *settingsManager = nullptr, QObject *parent = nullptr);
    ~SMLKAMEditorServer();

protected:
    QWebSocketServer *m_server;
    qint16 m_port;

    QList<Adapter *> m_adapters;
    QList<QWebSocket *> m_unregisteredConnections;
    bool m_debug;
signals:
    void newConnection();

    void u1Connected();
    void u1Disconnected();
    void u2Connected();
    void u2Disconnected();

    void byteMessageReceived(QByteArray message);

public slots:
    void start();
    void stop();
    void sendMessageToU1(QByteArray message);

    QStringList currentAdapters();

protected slots:
    void setup(SettingsManager* sm);
    void onServerClosed();
    void onNewConnection();
    void onTextMessage(QString message);
    void onBinaryMessage(QByteArray message);
    void socketDisconnected();
    void registerConnection(QWebSocket *connection, Role role);

};

#endif // SMLKAMEDITORSERVER_H
