#ifndef SMLKAMEDITORSERVER_H
#define SMLKAMEDITORSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

#include "models/structs.h"
#include "models/settingsmanager/settingsmanager.h"

class SMLKAMEditorServer : public QObject
{
    Q_OBJECT
public:
    explicit SMLKAMEditorServer(const SettingsManager &settingsManager = SettingsManager(), QObject *parent = nullptr);
    ~SMLKAMEditorServer();

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
    void setup(const SettingsManager &sm);
    void onServerClosed();
    void onNewConnection();
    void onTextMessage(QString message);
    void onBinaryMessage(QByteArray message);
    void socketDisconnected();
    void registerConnection(std::shared_ptr<QWebSocket> connection, int type);
};

#endif // SMLKAMEDITORSERVER_H
